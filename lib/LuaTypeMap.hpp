//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Lua plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_ZLUA_LUA_TYPE_MAP_HPP_INCLUDED
#define ZEN_ZLUA_LUA_TYPE_MAP_HPP_INCLUDED

extern "C" {
#include <lauxlib.h>
#include <lualib.h>
}


#include <vector>
#include <map>

#include <boost/any.hpp>
#include <boost/function.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace ZLua {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

/// Map from any type to boost::any with support for creating parameter lists
class LuaTypeMap
{
    /// @name Types
    /// @{
public:
    //typedef boost::function<void (std::vector<boost::any>&, PyObject*)> function_type;
    //typedef std::map<_typeobject *, function_type>                      map_type;
    /// @}

    /// @name LuaTypeMap implementation
    /// @{
public:
    /// Convert and push_back a PyObject onto a parameter list.
    //bool push_back(std::vector<boost::any>& _parms, PyObject* _pObject);
    /// @}

    /// @name 'Structors
    /// @{
public:
             LuaTypeMap();
    virtual ~LuaTypeMap();
    /// @}

    /// @name Member Variables
    /// @{
private:
    //map_type    m_map;
    /// @}

};  // class LuaTypeMap
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace ZLua
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_ZLUA_LUA_TYPE_MAP_HPP_INCLUDED

