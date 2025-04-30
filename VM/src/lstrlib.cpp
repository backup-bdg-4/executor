// This file is part of the Luau programming language and is licensed under MIT License; see LICENSE.txt for details
// This code is based on Lua 5.x implementation licensed under MIT License; see lua_LICENSE.txt for details
#include "lualib.h"

#include "lstring.h"
#include "Luau/Macros.h" // Added for macro definitions

#include <ctype.h>
#include <string.h>
#include <stdio.h>

LUAU_DYNAMIC_FASTFLAGVARIABLE(LuauStringFormatFixC, false)
