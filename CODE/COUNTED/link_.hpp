#pragma once

// == LOCAL

// -- IMPORTS

#include "counted_block.hpp"
#include "counted_block_state.hpp"
#include "debug.hpp"
#include "void.hpp"

// == GLOBAL

// -- TYPES

template <typename _TYPE_>
struct LINK_
{
    // == PUBLIC

    // -- ATTRIBUTES

    _TYPE_
        * Address;

    // -- CONSTRUCTORS

    LINK_(
        ) :
        Address( 0 )
    {
    }

    // ~~

    LINK_(
        const LINK_ & link
        ) :
        Address( 0 )
    {
        SetAddress( link.Address );
    }

    // ~~

    LINK_(
        _TYPE_ * address
        ) :
        Address( 0 )
    {
        SetAddress( address );
    }

    // ~~

    ~LINK_(
        )
    {
        SetNull();
    }

    // -- OPERATORS

    VOID operator=(
        const LINK_ & link
        )
    {
        SetAddress( link.Address );
    }

    // ~~

    VOID operator=(
        const _TYPE_ * address
        )
    {
        SetAddress( address );
    }

    // ~~

    operator _TYPE_ *(
        VOID
        ) const
    {
        return Address;
    }

    // ~~

    _TYPE_ & operator*(
        VOID
        ) const
    {
        DEBUG_Check( Address != 0 );

        return *Address;
    }

    // ~~

    _TYPE_ * operator->(
        VOID
        ) const
    {
        DEBUG_Check( Address != 0 );

        return Address;
    }

    // -- OPERATIONS

    VOID SetNull(
        VOID
        )
    {
        _TYPE_
            * address;
        COUNTED_BLOCK
            * block;

        if ( Address != 0 )
        {
            address = Address;
            Address = 0;
            block = COUNTED_BLOCK_GetFromByteArray( address );
            DEBUG_Check( block->LinkCount != 0 );
            --block->LinkCount;

            if ( block->LinkCount == 0
                 && block->State == COUNTED_BLOCK_STATE_Destructed )
            {
                block->FreeByteArray();
            }
        }
    }

    // ~~

    VOID SetAddress(
        const _TYPE_ * address
        )
    {
        _TYPE_
            * non_const_address;
        COUNTED_BLOCK
            * block;

        if ( Address != address )
        {
            if ( address == 0 )
            {
                non_const_address = 0;
            }
            else
            {
                non_const_address = ( _TYPE_ * )address;
                block = COUNTED_BLOCK_GetFromByteArray( non_const_address );
                DEBUG_Check( block->State == COUNTED_BLOCK_STATE_Allocated );
                ++block->LinkCount;
                DEBUG_Check( block->RefCount != 0 );
            }

            SetNull();
            Address = non_const_address;
        }
    }
};
