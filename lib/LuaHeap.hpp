//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Lua plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
// Copyright (C)        2008 Matthew Alan Gray
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ZLUA_LUA_HEAP_HPP_INCLUDED
#define ZEN_ZLUA_LUA_HEAP_HPP_INCLUDED

#include <Zen/Core/Memory/managed_ptr.hpp>
#include <Zen/Core/Scripting/I_ObjectHeap.hpp>
#include <Zen/Core/Scripting/I_ScriptEngine.hpp>
#include <Zen/Core/Scripting/I_ObjectReference.hpp>

#include <map>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace ZLua {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class LuaEngine;

class LuaHeap
:   public Scripting::I_ObjectHeap
{
    /// @name Types
    /// @{
public:
    typedef Zen::Memory::managed_ptr<Scripting::I_ScriptEngine>     pScriptEngine_type;
    typedef Zen::Memory::managed_ptr<Scripting::I_ObjectReference>  pObjectReference_type;
    typedef std::map<unsigned, pObjectReference_type>               heap_index_type;
    /// @}

    /// @name I_ObjectHeap implementation
    /// @{
public:
    virtual void createObject(pObjectReference_type _pObject);
    virtual pObjectReference_type getGlobalReference(Scripting::I_ObjectReference& _object);
    /// @}

    /// @name 'Structors
    /// @{
public:
             LuaHeap(LuaEngine* _pEngine);
    virtual ~LuaHeap();
    /// @}

    /// @name Member Variables
    /// @{
private:
    LuaEngine*  m_pEngine;
    heap_index_type     m_heap;
    /// @}

};  // class LuaEngine

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace ZLua
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ZLUA_LUA_HEAP_HPP_INCLUDED
