#pragma once

#include <unordered_map>
#include <mutex>

// DobbyWrapper namespace - provides a C++ wrapper around the Dobby hooking library
namespace DobbyWrapper {
    // Hook a function
    void* Hook(void* targetAddr, void* hookAddr);
    
    // Get the original function for a hooked address
    void* GetOriginalFunction(void* targetAddr);
    
    // Unhook a function
    bool Unhook(void* targetAddr);
    
    // Unhook all functions
    void UnhookAll();
}

