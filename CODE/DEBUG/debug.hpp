#pragma once

// == LOCAL

// -- IMPORTS

#include "native.hpp"

// == GLOBAL

// -- CONSTANTS

#if defined( NDEBUG )
    #define DEBUG_Mode    0
#else
    #define DEBUG_Mode    1
#endif

// -- FUNCTIONS

#if DEBUG_Mode
    #define DEBUG_Print( _expression_ ) \
        \
        NATIVE_Print( _expression_ )

    // ~~

    #define DEBUG_Check    NATIVE_Check
#else
    #define DEBUG_Print( _expression_ )

    // ~~

    #define DEBUG_Check( _expression )
#endif
