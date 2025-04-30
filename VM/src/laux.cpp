// This file is part of the Luau programming language and is licensed under MIT License; see LICENSE.txt for details
// This code is based on Lua 5.x implementation licensed under MIT License; see lua_LICENSE.txt for details
#include "lualib.h"

#include "lobject.h"
#include "lstate.h"
#include "lstring.h"
#include "lapi.h"
#include "lgc.h"
#include "lnumutils.h"

#include <string.h>

LUAU_FASTFLAGVARIABLE(LuauLibWhereErrorAutoreserve, true)
