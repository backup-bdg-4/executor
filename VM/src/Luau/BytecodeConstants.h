// BytecodeConstants.h - Definitions for Luau bytecode constants
#pragma once

// Bytecode version constants
#define LBC_VERSION_MIN 1
#define LBC_VERSION_MAX 4

// Type version constants
#define LBC_TYPE_VERSION_MIN 1
#define LBC_TYPE_VERSION_MAX 3

// Type constants
#define LBC_TYPE_FUNCTION 0
#define LBC_TYPE_USERDATA 7
#define LBC_TYPE_TAGGED_USERDATA_BASE 128
#define LBC_TYPE_TAGGED_USERDATA_END 192

// Constant type identifiers
#define LBC_CONSTANT_NIL 0
#define LBC_CONSTANT_BOOLEAN 1
#define LBC_CONSTANT_NUMBER 2
#define LBC_CONSTANT_STRING 3
#define LBC_CONSTANT_IMPORT 4
#define LBC_CONSTANT_TABLE 5
#define LBC_CONSTANT_CLOSURE 6
#define LBC_CONSTANT_VECTOR 7

