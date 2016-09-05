//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Lua plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#include "../LuaType.hpp"
#include "../LuaMethod.hpp"

#include <boost/preprocessor/iteration/local.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace ZLua {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#define METHOD_MAX_SIZE 200

// Create the hundred C methods

#define METHOD_LOOP(n) \
static LuaMethod* sm_pMethod##n; \
static int cfunc##n(lua_State* L) \
{ \
    return (*sm_pMethod##n)(L); \
}

#define BOOST_PP_LOCAL_MACRO(n)     METHOD_LOOP(n)
#define BOOST_PP_LOCAL_LIMITS       (0, METHOD_MAX_SIZE - 1)
#include BOOST_PP_LOCAL_ITERATE()

// Create the hundred entries in the method table

#define METHOD_TABLE_LOOP(n) cfunc##n, &sm_pMethod##n,

#define BOOST_PP_LOCAL_MACRO(n)     METHOD_TABLE_LOOP(n)
#define BOOST_PP_LOCAL_LIMITS       (0, METHOD_MAX_SIZE - 1)

static unsigned int sm_methodItem = 0;
struct
{
    lua_CFunction     m_cFunction;
    LuaMethod**  m_ppMethod;
} static sm_methodTable[METHOD_MAX_SIZE] =
{
#include BOOST_PP_LOCAL_ITERATE()
};

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
LuaType::addMethod(const std::string& _name, const std::string& _docString, Scripting::I_ScriptType::void_function_args_type _function)
{
    unsigned item = sm_methodItem++;

    (*sm_methodTable[item].m_ppMethod) = new LuaMethod(this, _name, _docString, _function, sm_methodTable[item].m_cFunction);

    m_methods.push_back(*sm_methodTable[item].m_ppMethod);
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace ZLua
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
