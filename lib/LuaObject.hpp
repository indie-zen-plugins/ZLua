//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Lua plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
// Copyright (C)        2008 Matthew Alan Gray
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ZLUA_LUA_OBJECT_HPP_INCLUDED
#define ZEN_ZLUA_LUA_OBJECT_HPP_INCLUDED

extern "C" {
#include <lauxlib.h>
#include <lualib.h>
}


#include <Zen/Core/Scripting/I_ScriptObject.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace ZLua {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class LuaObject
:   public Scripting::I_ScriptObject
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_ScriptObject implementation
    /// @{
public:
    /// @}

    /// @name LuaObject implementation
    /// @{
public:
    //PyObject* get();
    /// @}

    /// @name 'Structors
    /// @{
public:
             //LuaObject(PyObject* _pObj);
    virtual ~LuaObject();
    /// @}

    /// @name Member Variables
    /// @{
private:
    //PyObject*   m_pObj;
    /// @}

};  // class LuaObject

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace ZLua
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ZLUA_LUA_OBJECT_HPP_INCLUDED
