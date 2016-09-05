//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Lua plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ZLUA_LUA_ENGINE_FACTORY_HPP_INCLUDED
#define ZEN_ZLUA_LUA_ENGINE_FACTORY_HPP_INCLUDED

#include <Zen/Core/Scripting/I_ScriptEngineFactory.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace ZLua {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class LuaEngineFactory
:   public Scripting::I_ScriptEngineFactory
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_ScriptEngineFactory implementation
    /// @{
public:
    virtual pScriptEngine_type create(const std::string& _name);
    /// @}

    /// @name LuaEngineFactory implementation
    /// @{
public:
    void onDestroy(wpScriptEngine_type _pScriptEngine);
    /// @}

    /// @name Static methods
    /// @{
public:
    static LuaEngineFactory& getSingleton();
    /// @}

    /// @name 'Structors
    /// @{
public:
             LuaEngineFactory();
    virtual ~LuaEngineFactory();
    /// @}

    /// @name Member variables
    /// @{
private:
    /// @}

};  // class LuaEngineFactory


//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace ZLua
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ZLUA_LUA_ENGINE_FACTORY_HPP_INCLUDED
