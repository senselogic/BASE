#pragma once

// == LOCAL

// -- IMPORTS

#include "uint_32.hpp"

// == GLOBAL

// -- TYPES

typedef UINT_32
    COUNTED_BLOCK_STATE;

// -- CONSTANTS

enum
{
    COUNTED_BLOCK_STATE_Deallocated,
    COUNTED_BLOCK_STATE_Allocated,
    COUNTED_BLOCK_STATE_Destructed,
    COUNTED_BLOCK_STATE_Count
};
