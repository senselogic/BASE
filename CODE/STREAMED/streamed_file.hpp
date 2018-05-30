#pragma once

// == LOCAL

// -- IMPORTS

#include "bool_8.hpp"
#include "char_8.hpp"
#include "debug.hpp"
#include "int_64.hpp"
#include "string_8.hpp"
#include "uint_64.hpp"
#include "void.hpp"

// ~~

#include <fstream>
#include <iostream>

// -- GLOBAL

// -- TYPES

struct STREAMED_FILE
{
    // == PUBLIC

    // -- TYPES

    enum TYPE
    {
        TYPE_Input,
        TYPE_Output,
        TYPE_None
    };

    // -- ATTRIBUTES

    std::fstream
        File;
    TYPE
        Type;
    UINT_64
        ByteCount;

    // -- CONSTRUCTORS

    STREAMED_FILE(
        ) :
        File(),
        Type( TYPE_None ),
        ByteCount( 0 )
    {
    }

    // -- DESTRUCTOR

    ~STREAMED_FILE(
        )
    {
        if ( Type != TYPE_None )
        {
            Close();
        }
    }

    // -- OPERATORS

    template <typename _VALUE_>
    STREAMED_FILE & operator<<(
        const _VALUE_ & value
        )
    {
        DEBUG_Check( Type == TYPE_Output );

        File << value;

        return *this;
    }

    // -- OPERATIONS

    const BOOL_8 OpenInput(
        const STRING_8 & file_path
        )
    {
        DEBUG_Check( Type == TYPE_None );
        DEBUG_Check( !File.is_open() );

        File.open( file_path.c_str(), std::ios::in | std::ios::binary );

        if ( File.is_open() )
        {
            Type = TYPE_Input;

            File.seekg( 0, std::ios::end );
            ByteCount = File.tellg();
            File.seekg( 0, std::ios::beg );

            return true;
        }
        else
        {
            return false;
        }
    }

    // ~~

    const BOOL_8 OpenOutput(
        const STRING_8 & file_path
        )
    {
        DEBUG_Check( Type == TYPE_None );
        DEBUG_Check( !File.is_open() );

        File.open( file_path.c_str(), std::ios::out | std::ios::binary );

        if ( File.is_open() )
        {
            Type = TYPE_Output;

            ByteCount = 0;

            return true;
        }
        else
        {
            return false;
        }
    }

    // ~~

    const BOOL_8 ReadByteArray(
        VOID * byte_array,
        const UINT_64 byte_count
        )
    {
        DEBUG_Check( Type == TYPE_Input );

        File.read( ( CHAR_8 * )byte_array, byte_count );

        return File.good();
    }

    // ~~

    const BOOL_8 WriteByteArray(
        const VOID * byte_array,
        const UINT_64 byte_count
        )
    {
        DEBUG_Check( Type == TYPE_Output );

        File.write( ( const CHAR_8 * )byte_array, byte_count );

        return File.good();
    }

    // ~~

    const BOOL_8 Close(
        )
    {
        DEBUG_Check( Type != TYPE_None );

        File.close();

        Type = TYPE_None;

        return true;
    }

    // ~~

    UINT_64 GetByteIndex(
        )
    {
        DEBUG_Check( Type == TYPE_Input );

        return File.tellg();
    }

    // ~~

    VOID SetByteIndex(
        const UINT_64 byte_index
        )
    {
        DEBUG_Check( Type == TYPE_Input );

        File.seekg( byte_index, std::ios::beg );
    }

    // ~~

    VOID SetByteOffset(
        const INT_64 byte_offset
        )
    {
        DEBUG_Check( Type == TYPE_Input );

        File.seekg( byte_offset, std::ios::cur );
    }

    // ~~

    VOID SetPostByteIndex(
        const UINT_64 byte_index = 0
        )
    {
        DEBUG_Check( Type == TYPE_Input );

        File.seekg( byte_index, std::ios::end );
    }

    // ~~

    const BOOL_8 ReadText(
        STRING_8 & text
        )
    {
        UINT_64
            byte_count;
        CHAR_8
            * character_array;
        BOOL_8
            text_is_read;

        DEBUG_Check( Type == TYPE_Input );

        byte_count = ByteCount - GetByteIndex();

        character_array = new CHAR_8[ byte_count + 1 ];
        character_array[ byte_count ] = 0;

        text_is_read = ReadByteArray( character_array, byte_count );

        text = character_array;
        delete[] character_array;

        return text_is_read;
    }
};
