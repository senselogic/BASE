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
struct REF_
{
    // == PUBLIC

    // -- ATTRIBUTES

    _TYPE_
        * Address;

    // -- CONSTRUCTORS

    REF_(
        ) :
        Address( 0 )
    {
    }

    // ~~

    REF_(
        const REF_ & ref
        ) :
        Address( 0 )
    {
        SetAddress( ref.Address );
    }

    // ~~

    REF_(
        _TYPE_ * address
        ) :
        Address( 0 )
    {
        SetAddress( address );
    }

    // ~~

    ~REF_(
        )
    {
        SetNull();
    }

    // -- OPERATORS

    VOID operator=(
        const REF_ & ref
        )
    {
        SetAddress( ref.Address );
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
            DEBUG_Check( block->State == COUNTED_BLOCK_STATE_Allocated );
            DEBUG_Check( block->RefCount != 0 );
            --block->RefCount;

            if ( block->RefCount == 0 )
            {
                address-> ~_TYPE_();

                if ( block->LinkCount == 0 )
                {
                    block->FreeByteArray();
                }
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

                if ( block->State == COUNTED_BLOCK_STATE_Destructed )
                {
                    non_const_address = 0;
                }
                else
                {
                    ++block->RefCount;
                    DEBUG_Check( block->RefCount != 0 );
                }
            }

            SetNull();
            Address = non_const_address;
        }
    }
};
