//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Lua plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#include <Zen/Plugins/Utilities.hpp>

#include "LuaEngineFactory.hpp"

// Don't normally do this.  Just here because it's convenient.
using namespace Zen::ZLua;

IMPLEMENT_SINGLE_ZEN_PLUGIN(ZLuaModule, ZLuaPlugin)

BEGIN_ZEN_EXTENSION_MAP(ZLuaPlugin)
    ZEN_EXTENSION("Zen::Scripting::Engine", &LuaEngineFactory::getSingleton())
END_ZEN_EXTENSION_MAP()
