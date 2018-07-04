#pragma once

// == LOCAL

// -- IMPORTS

#include "bool_8.hpp"
#include "counted.hpp"
#include "counted_block_state.hpp"
#include "debug.hpp"
#include "uint_32.hpp"
#include "uint_64.hpp"
#include "void.hpp"

// == GLOBAL

// -- TYPES

struct COUNTED_BLOCK
{
    // == PUBLIC

    // -- ATTRIBUTES

    UINT_64
        ByteCount : 61,
        ItIsArray : 1,
        State : 2;
    UINT_32
        RefCount;
    UINT_32
        LinkCount;

    // -- OPERATIONS

    VOID SetAllocated(
        const UINT_64 byte_count,
        const BOOL_8 it_is_array
        )
    {
        ByteCount - byte_count;
        ItIsArray = it_is_array;
        State = COUNTED_BLOCK_STATE_Allocated;
        RefCount = 0;
        LinkCount = 0;
    }

    // ~~

    VOID SetDestructed(
        VOID
        )
    {
        DEBUG_Check( RefCount == 0 );
        DEBUG_Check( State == COUNTED_BLOCK_STATE_Allocated );

        State = COUNTED_BLOCK_STATE_Destructed;
    }

    // ~~

    VOID SetDeallocated(
        VOID
        )
    {
        DEBUG_Check( RefCount == 0 );
        DEBUG_Check( LinkCount == 0 );
        DEBUG_Check(
            State == COUNTED_BLOCK_STATE_Allocated
            || State == COUNTED_BLOCK_STATE_Destructed
            );

        State = COUNTED_BLOCK_STATE_Deallocated;
    }

    // ~~

    VOID FreeByteArray(
        const BOOL_8 it_is_array = false
        )
    {
        DEBUG_Check( it_is_array == ItIsArray );
        DEBUG_Check(
            State == COUNTED_BLOCK_STATE_Allocated
            || State == COUNTED_BLOCK_STATE_Destructed
            );

        COUNTED_FreeByteArray( this + 1, false );
    }
};

// -- FUNCTIONS

#define COUNTED_BLOCK_GetFromByteArray( _byte_array_ ) \
    \
    ( ( COUNTED_BLOCK * )( _byte_array_ ) - 1 )
