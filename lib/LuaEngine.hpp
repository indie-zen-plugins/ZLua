//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Lua plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ZLUA_LUA_ENGINE_HPP_INCLUDED
#define ZEN_ZLUA_LUA_ENGINE_HPP_INCLUDED

#include "../I_LuaScriptEngine.hpp"

#include <Zen/Core/Memory/managed_self_ref.hpp>

#include <Zen/Core/Scripting/I_ScriptType.hpp>

#include <Zen/Core/Utility/runtime_exception.hpp>

#include "LuaHeap.hpp"
#include "LuaTypeMap.hpp"

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace ZLua {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class LuaObject;

class LuaEngine
:   public I_LuaScriptEngine
,   public Memory::managed_self_ref<Scripting::I_ScriptEngine>
{
    /// @name Types
    /// @{
public:
    typedef Zen::Memory::managed_ptr<Scripting::I_ObjectHeap>           pObjectHeap_type;
    typedef Zen::Memory::managed_weak_ptr<Scripting::I_ObjectHeap>      wpObjectHeap_type;

    typedef Zen::Memory::managed_ptr<Scripting::I_ScriptModule>         pScriptModule_type;
    typedef Zen::Memory::managed_weak_ptr<Scripting::I_ScriptModule>    wpScriptModule_type;

    typedef Scripting::I_ObjectReference*                               pObjectReference_type;

    //typedef std::map<PyObject*, pObjectReference_type>                  object_map_type;
    typedef Zen::Memory::managed_ptr<Scripting::I_ScriptType>           pScriptType_type;
    /// @}

    /// @name I_ScriptEngine implementation
    /// @{
public:
    virtual Scripting::I_ObjectHeap& heap();
    virtual bool executeScript(const std::string& _fileName);
    virtual void executeMethod(boost::any& _object, boost::any& _method, std::vector<boost::any>& _parms);
    virtual pScriptModule_type createScriptModule(const std::string& _moduleName, const std::string& _docString);
    /// @}

    /// @name I_LuaScriptEngine implementation
    /// @{
public:
    virtual lua_State* getState() const { return m_pLua; }
    /// @}

    /// @name LuaEngine implementation
    /// @{
public:
    LuaTypeMap& getTypeMap();

    void registerModules();
    /// @}

    /// @name Event handlers
    /// @{
public:
    void onDestroyObjectHeap(wpObjectHeap_type _pObjectHeap);
    void onDestroyScriptModule(wpScriptModule_type _pScriptModule);
    /// @}

    /// @name 'Structors
    /// @{
public:
             LuaEngine();
    virtual ~LuaEngine();
    /// @}

    /// @name Member Variables
    /// @{
private:
    LuaHeap*         m_pHeap;
    LuaTypeMap       m_typeMap;

    lua_State*          m_pLua;

    pScriptModule_type  m_pMathModule;
    pScriptType_type    m_pMathType;
    /// @}

};  // class LuaEngine

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace ZLua
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ZLUA_LUA_ENGINE_HPP_INCLUDED
