// == LOCAL

// -- IMPORTS

#include "bool_8.hpp"
#include "counted.hpp"
#include "counted_block.hpp"
#include "debug.hpp"
#include "uint_64.hpp"
#include "void.hpp"

// ~~

#include <stdlib.h>

// == GLOBAL

// -- FUNCTIONS

VOID * COUNTED_MakeByteArray(
    const UINT_64 byte_count,
    const BOOL_8 it_is_array
    )
{
    COUNTED_BLOCK
        * block;

    block = ( COUNTED_BLOCK * )malloc( sizeof( COUNTED_BLOCK ) + byte_count );
    DEBUG_Check( block != 0 );

    block->SetAllocated( byte_count, it_is_array );

    return block + 1;
}

// ~~

VOID COUNTED_FreeByteArray(
    VOID * byte_array,
    const BOOL_8 it_is_array
    )
{
    COUNTED_BLOCK
        * block;

    DEBUG_Check( byte_array != 0 );

    block = COUNTED_BLOCK_GetFromByteArray( byte_array );
    DEBUG_Check( block->ItIsArray == it_is_array );

    block->SetDeallocated();

    free( block );
}

// ~~

VOID * operator new(
    const UINT_64 byte_count
    )
{
    return COUNTED_MakeByteArray( byte_count, false );
}

// ~~

VOID * operator new[](
    const UINT_64 byte_count
    )
{
    return COUNTED_MakeByteArray( byte_count, true );
}

// ~~

VOID operator delete(
    VOID * byte_array
    ) noexcept
{
    return COUNTED_FreeByteArray( byte_array, false );
}

// ~~

VOID operator delete[](
    VOID * byte_array
    ) noexcept
{
    return COUNTED_FreeByteArray( byte_array, true );
}
