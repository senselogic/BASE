#pragma once

// == LOCAL

// -- IMPORTS

#include <stdint.h>

// == GLOBAL

// -- TYPES

typedef uint64_t
    UINT_64;

// -- FUNCTIONS

#define UINT_64_GetTag8( _first_character_, _second_character_, _third_character_, _fourth_character_, _fifth_character_, _sixth_character_, _seventh_character_, _eighth_character_ ) \
    \
    ( UINT_64( _first_character_ ) \
    | ( UINT_64( _second_character_ ) << 8 ) \
    | ( UINT_64( _third_character_ ) << 16 ) \
    | ( UINT_64( _fourth_character_ ) << 24 ) \
    | ( UINT_64( _fifth_character_ ) << 32 ) \
    | ( UINT_64( _sixth_character_ ) << 40 ) \
    | ( UINT_64( _seventh_character_ ) << 48 ) \
    | ( UINT_64( _eighth_character_ ) << 56 ) )
