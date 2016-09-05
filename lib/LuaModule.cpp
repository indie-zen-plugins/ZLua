//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Lua plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#include "LuaModule.hpp"
#include "LuaType.hpp"
#include "LuaObject.hpp"
#include "LuaEngine.hpp"

#include <Zen/Core/Scripting/I_ObjectReference.hpp>

#include <stddef.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace ZLua {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#if 0
static PyMethodDef module_methods[] = 
{
    {NULL}  /* Sentinel */
};
#endif

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
LuaModule::LuaModule(LuaEngine* _pEngine, const std::string& _name, const std::string& _docString)
:   m_pEngine(_pEngine)
,   m_name(_name)
,   m_docString(_docString)
{
#if 0
    m_pModule = Py_InitModule3(m_name.c_str(), module_methods, m_docString.c_str());
    m_pModuleDict = PyModule_GetDict(m_pModule);
#endif 
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
LuaModule::~LuaModule()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
LuaModule::pScriptType_type
LuaModule::createScriptType(const std::string& _typeName, const std::string& _docString, unsigned long _rawSize)
{
    // Make sure the script type doesn't already exist.  If it does, return it
    // instead of creating a new one.
    type_collection_type::iterator iter = m_types.find(_typeName);

    if (iter != m_types.end())
    {
        return iter->second;
    }

	// The type doesn't exist so create it.
    LuaType* const pLuaType = new LuaType(this, _typeName, _docString, _rawSize);

    pScriptType_type const pType(pLuaType,
        boost::bind(&LuaModule::onDestroyScriptType,this,_1));

    m_types[_typeName] = pType;

    return pType;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
LuaModule::pScriptType_type
LuaModule::getScriptType(const std::string& _typeName)
{
    return m_types[_typeName];
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
LuaModule::activate()
{
    // To activate this module, just activate each sub type
    for(type_collection_type::iterator iter = m_types.begin(); iter != m_types.end(); iter++)
    {
        iter->second->activate();
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
LuaModule::createObject(pScriptType_type _pType, pObjectReference_type _pObject)
{
    lua_State* const L = getEngine().getState();

    // Get the top of the stack so we can ensure we don't push or pop too much
    const int top = lua_gettop(L);

    // Create a new table T
    lua_newtable(L);
    const int table = lua_gettop(L);

    // Duplicate the table and save a reference to it
    lua_pushvalue(L, -1);
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);

    // Create the user data, which is an object pointer pointer
    pObjectReference_type* pObj = (pObjectReference_type*)lua_newuserdata(L, sizeof(pObjectReference_type));

    // Set the user data
    *pObj = _pObject;
    _pObject->setScriptUserData((void*)ref);

    const int userdata = lua_gettop(L);

    // T["__zen_userdata"] = UD
    lua_pushvalue(L, userdata);
    lua_setfield(L, table, "__zen_userdata");

    // Get the meta table for this class type and set it for this object
    luaL_getmetatable(L, dynamic_cast<LuaType*>(_pType.get())->getFullName().c_str());
    assert(lua_type(L, -1) != LUA_TNIL);
    lua_setmetatable(L, table);

    // Get the meta table for this class type and set it for the user data
    luaL_getmetatable(L, dynamic_cast<LuaType*>(_pType.get())->getFullName().c_str());
    assert(lua_type(L, -1) != LUA_TNIL);
    lua_setmetatable(L, userdata);

    // Pop global, __zen_heap, the user data and the table
    lua_pop(L, 2);

    assert(top == lua_gettop(L));
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
LuaModule::createGlobalObject(const std::string& _name, pScriptType_type _pType, pObjectReference_type _pObject)
{
    lua_State* const L = getEngine().getState();

    // Get the top of the stack so we can ensure we don't push or pop too much
    const int top = lua_gettop(L);

    // Create a new table T
    lua_newtable(L);
    const int table = lua_gettop(L);

    // Duplicate the table and save a reference to it
    lua_pushvalue(L, -1);
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);

    // Create the user data, which is an object pointer pointer
    pObjectReference_type* pObj = (pObjectReference_type*)lua_newuserdata(L, sizeof(pObjectReference_type));

    // Set the user data
    *pObj = _pObject;
    _pObject->setScriptUserData((void*)ref);

    const int userdata = lua_gettop(L);

    // T["__zen_userdata"] = UD
    lua_pushvalue(L, userdata);
    lua_setfield(L, table, "__zen_userdata");

    // Get the meta table for this class type and set it for this object
    luaL_getmetatable(L, dynamic_cast<LuaType*>(_pType.get())->getFullName().c_str());
    assert(lua_type(L, -1) != LUA_TNIL);
    lua_setmetatable(L, table);

    // Get the meta table for this class type and set it for the user data
    luaL_getmetatable(L, dynamic_cast<LuaType*>(_pType.get())->getFullName().c_str());
    assert(lua_type(L, -1) != LUA_TNIL);
    lua_setmetatable(L, userdata);

    // Pop the user data
    lua_pop(L, 1);

    // Register the table as a global name
    lua_setglobal(L, _name.c_str());

    assert(top == lua_gettop(L));
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
LuaModule::pScriptEngine_type
LuaModule::getScriptEngine()
{
    return getEngine().getSelfReference().lock();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#if 0
PyObject*
LuaModule::newObject(pScriptType_type _pType, pObjectReference_type _pObject)
{
    // Convert the type
    LuaType* const pType = dynamic_cast<LuaType*>(_pType.get());

    if(pType == NULL)
    {
        // TODO Error, wrong I_ScriptType
        return NULL;
    }

    //PyObject* const pObject = pType->getRawType()->tp_new(pType->getRawType(), NULL, NULL);

    // Associate the I_ObjectReference with the PyObject
    //m_pEngine->setObject(pObject, _pObject);

    // Create a new LuaObject from the new PyObject
    pScriptObject_type pScriptObject(new LuaObject(pObject),
        boost::bind(&LuaModule::onDestroyScriptObject,this,_1));

    // Associate the new PyObject with the I_ObjectReference
    _pObject->setScriptObject(pScriptObject);

    return pObject;
}
#endif 

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
LuaEngine&
LuaModule::getEngine()
{
    return *m_pEngine;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
const std::string&
LuaModule::getName() const
{
    return m_name;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
LuaModule::onDestroyScriptType(wpScriptType_type _pScriptType)
{
    /// Fire the ScriptType onDestroyEvent
    _pScriptType->onDestroyEvent(_pScriptType);

    /// Delete the ScriptType
    LuaType* pScriptType = dynamic_cast<LuaType*>(_pScriptType.get());

    if( pScriptType )
    {
        delete pScriptType;
    }
    else
    {
        throw Utility::runtime_exception("Zen::ZLua::LuaModule::onDestroyScriptType() : _pScriptType is an invalid LuaType.");
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
LuaModule::onDestroyScriptObject(wpScriptObject_type _pScriptObject)
{
    /// Fire the ScriptObject onDestroyEvent
    _pScriptObject->onDestroyEvent(_pScriptObject);

    /// Delete the ScriptObject
    LuaObject* pScriptObject = dynamic_cast<LuaObject*>(_pScriptObject.get());

    if( pScriptObject )
    {
        delete pScriptObject;
    }
    else
    {
        throw Utility::runtime_exception("Zen::ZLua::LuaModule::onDestroyScriptObject() : _pScriptObject is an invalid LuaObject.");
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace ZLua
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
