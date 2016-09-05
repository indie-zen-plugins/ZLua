//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Lua plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ZLUA_LUA_TYPE_HPP_INCLUDED
#define ZEN_ZLUA_LUA_TYPE_HPP_INCLUDED

extern "C" {
#include <lauxlib.h>
#include <lualib.h>
}

#include <Zen/Scripting/I_ScriptType.hpp>

#include <string>
#include <list>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace ZLua {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class LuaModule;
class LuaMethod;

class LuaType
:   public Scripting::I_ScriptType
{
    /// @name Types
    /// @{
public:
    typedef std::list<LuaMethod*>    methods_type;
    /// @}

    /// @name I_ScriptType implementation
    /// @{
public:
    virtual pScriptModule_type getScriptModule();
    virtual const std::string& getTypeName();
    virtual const std::string& getDocumentation();

    virtual void addMethod(const std::string& _name, const std::string& _docString, void_function_no_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, void_function_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, object_function_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, object_function_no_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, string_function_no_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, string_function_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, bool_function_no_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, bool_function_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, int_function_no_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, int_function_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, Scripting::I_ScriptMethod* _function);

    virtual void activate();
    /// @}

    /// @name Additional Implementation
    /// @{
public:
    //PyTypeObject*   getRawType();
    const std::string& getName() const;
    const std::string& getFullName() const;
    LuaModule&   getModule();
    int gc(lua_State* L);

private:
    void openlib(lua_State *L, const char *libname, int nup);
    /// @}

    /// @name 'Structors
    /// @{
public:
             LuaType(LuaModule* _pModule, const std::string& _name, const std::string& _docString, unsigned long _rawSize);
    virtual ~LuaType();
    /// @}

    /// @name Member Variables
    /// @{
private:
    LuaModule*              m_pModule;      ///< Module
    std::string             m_name;         ///< Class Name
    std::string             m_docString;    ///< Document String
    std::string             m_fullName;     ///< Full Class Name including module

    //PyTypeObject            m_type;
    //PyObject*               m_pClass;
    //PyObject*               m_pClassDict;

    methods_type            m_methods;
    /// @}

};  // class LuaModule

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#if 0
inline
PyTypeObject*
LuaType::getRawType()
{ 
    return &m_type; 
}
#endif

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#if 0
inline
PyObject*
LuaType::getRawClass()
{ 
    return m_pClass; 
}
#endif

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
inline
const std::string&
LuaType::getName() const
{
    return m_name;
}


//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
inline
const std::string&
LuaType::getFullName() const
{
    return m_fullName;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
inline
LuaModule&
LuaType::getModule()
{
    return *m_pModule;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace ZLua
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ZLUA_LUA_TYPE_HPP_INCLUDED
