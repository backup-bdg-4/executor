#pragma once

// Constants for bytecode loading and execution

namespace BytecodeConstants {
    // Bytecode format version
    constexpr int BYTECODE_VERSION = 3;
    
    // Magic number for bytecode files
    constexpr unsigned char BYTECODE_MAGIC[4] = {0x1B, 0x4C, 0x75, 0x61}; // "\x1BLua"
    
    // Bytecode header size
    constexpr int HEADER_SIZE = 12;
    
    // Instruction types
    enum InstructionType {
        INST_NOP = 0,
        INST_LOAD = 1,
        INST_STORE = 2,
        INST_CALL = 3,
        INST_JUMP = 4,
        INST_RETURN = 5,
        INST_ARITHMETIC = 6,
        INST_COMPARISON = 7,
        INST_TABLE = 8,
        INST_STRING = 9,
        INST_CLOSURE = 10,
        INST_UPVALUE = 11,
        INST_SPECIAL = 12
    };
    
    // Operand types
    enum OperandType {
        OPERAND_NONE = 0,
        OPERAND_REGISTER = 1,
        OPERAND_CONSTANT = 2,
        OPERAND_NUMBER = 3,
        OPERAND_STRING = 4,
        OPERAND_UPVALUE = 5,
        OPERAND_JUMP = 6,
        OPERAND_TABLE = 7
    };
    
    // Value types
    enum ValueType {
        TYPE_NIL = 0,
        TYPE_BOOLEAN = 1,
        TYPE_NUMBER = 2,
        TYPE_STRING = 3,
        TYPE_TABLE = 4,
        TYPE_FUNCTION = 5,
        TYPE_USERDATA = 6,
        TYPE_THREAD = 7,
        TYPE_BUFFER = 8
    };
    
    // Flags for function prototypes
    enum FunctionFlags {
        FUNC_VARARG = 1,
        FUNC_MAIN = 2,
        FUNC_STRIPPED = 4,
        FUNC_DEBUGINFO = 8
    };
    
    // Maximum stack size
    constexpr int MAX_STACK = 250;
    
    // Maximum number of upvalues
    constexpr int MAX_UPVALUES = 200;
    
    // Maximum number of local variables
    constexpr int MAX_LOCALS = 200;
    
    // Maximum number of constants
    constexpr int MAX_CONSTANTS = 2000000;
    
    // Maximum number of nested functions
    constexpr int MAX_NESTED_FUNCTIONS = 10000;
}

