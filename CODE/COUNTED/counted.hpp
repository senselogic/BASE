#pragma once

// == LOCAL

// -- IMPORTS

#include "bool_8.hpp"
#include "uint_64.hpp"
#include "void.hpp"

// == GLOBAL

// -- FUNCTIONS

VOID * COUNTED_MakeByteArray(
    const UINT_64 byte_count,
    const BOOL_8 it_is_array = true
    );

// ~~

VOID COUNTED_FreeByteArray(
    VOID * byte_array,
    const BOOL_8 it_is_array = true
    );

// ~~

VOID * operator new(
    const UINT_64 byte_count
    );

// ~~

VOID * operator new[](
    const UINT_64 byte_count
    );

// ~~

VOID operator delete(
    VOID * byte_array
    ) noexcept;

// ~~

VOID operator delete[](
    VOID * byte_array
    ) noexcept;
