#pragma once

// == LOCAL

// -- IMPORTS

#include "bool_8.hpp"
#include "char_8.hpp"
#include "debug.hpp"
#include "int_64.hpp"
#include "real_64.hpp"
#include "uint_64.hpp"
#include "vector_.hpp"
#include "void.hpp"

// ~~

#include <iomanip>
#include <sstream>
#include <string>

// == GLOBAL

// -- TYPES

typedef std::string
    STRING_8;

// -- CONSTANTS

#define STRING_8_NotFound std::string::npos

// -- FUNCTIONS

inline REAL_64 STRING_8_GetReal(
    const STRING_8 & text
    )
{
    return std::stod( text );
}

// ~~

inline STRING_8 STRING_8_Get(
    const REAL_64 value,
    const INT_64 minimum_fractional_digit_count = 1,
    const INT_64 maximum_fractional_digit_count = 10
    )
{
    std::stringstream
        text_stream;
    STRING_8
        text;
    UINT_64
        character_count,
        character_index,
        dot_character_index;

    DEBUG_Check( minimum_fractional_digit_count >= 1 );
    DEBUG_Check( maximum_fractional_digit_count <= 15 );
    DEBUG_Check( minimum_fractional_digit_count <= maximum_fractional_digit_count );

    text_stream
        << std::fixed
        << std::setprecision( maximum_fractional_digit_count )
        << value;

    text = text_stream.str();

    if ( minimum_fractional_digit_count < maximum_fractional_digit_count )
    {
        dot_character_index = text.find( '.' );

        if ( dot_character_index != STRING_8_NotFound )
        {
            character_count = text.size();

            for ( character_index = text.size() - 1;
                  character_index > dot_character_index + minimum_fractional_digit_count;
                  --character_index )
            {
                if ( text[ character_index ] == '0' )
                {
                    --character_count;
                }
                else
                {
                    break;
                }
            }

            text.resize( character_count );

            if ( REAL_64_IsRoughlyZero( value )
                 && text[ 0 ] == '-'
                 && text == STRING_8( "-0.000000000000000" ).substr( 0, character_count ) )
            {
                text = text.substr( 1 );
            }
        }
    }

    return text;
}

// ~~

inline VOID STRING_8_Split(
    const STRING_8 & text,
    const CHAR_8 separator_character,
    VECTOR_<STRING_8> & part_vector
    )
{
    UINT_64
        character_index,
        next_character_index;

    part_vector.resize( 0 );

    character_index = 0;
    next_character_index = text.find( separator_character );

    while ( next_character_index != STRING_8_NotFound )
    {
        part_vector.push_back(
            text.substr( character_index, next_character_index -character_index )
            );

        character_index = ++next_character_index;

        next_character_index = text.find( separator_character, next_character_index );

        if ( next_character_index == STRING_8_NotFound )
        {
            part_vector.push_back(
                text.substr( character_index, text.length() )
                );
        }
    }
}

// ~~

inline const BOOL_8 STRING_8_Replace(
    STRING_8 & text,
    const STRING_8 & old_text,
    const STRING_8 & new_text
    )
{
    BOOL_8
        text_is_replaced;
    UINT_64
        character_index;

    DEBUG_Check( old_text.length() > 0 );

    text_is_replaced = false;

    character_index = 0;

    while ( ( character_index = text.find( old_text, character_index ) )
            != STRING_8_NotFound )
    {
        text.replace( character_index, old_text.length(), new_text );
        text_is_replaced = true;

        character_index += new_text.length();
    }

    return text_is_replaced;
}

// ~~

inline const BOOL_8 STRING_8_HasPrefix(
    const STRING_8 & text,
    const STRING_8 & prefix
    )
{
    return
        prefix.length() <= text.length()
        && std::equal( prefix.begin(), prefix.end(), text.begin() );
}

// ~~

inline const BOOL_8 STRING_8_HasSuffix(
    const STRING_8 & text,
    const STRING_8 & suffix
    )
{
    return
        suffix.length() <= text.length()
        && std::equal( suffix.begin(), suffix.end(), text.end() - suffix.length() );
}

// ~~

inline const STRING_8 STRING_8_Trim(
    const STRING_8 & text
    )
{
    UINT_64
        first_character_index,
        post_character_index;

    first_character_index = 0;

    while ( std::isspace( text[ first_character_index ] ) )
    {
        ++first_character_index;
    }

    post_character_index = text.size();

    while ( post_character_index > first_character_index
            && std::isspace( text[ post_character_index - 1 ] ) )
    {
        --post_character_index;
    }

    return text.substr( first_character_index, post_character_index - first_character_index );
}
