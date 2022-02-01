#pragma once

// == LOCAL

// -- IMPORTS

#include "streamed.hpp"

// ~~

#include <iostream>
#include <stdlib.h>

// == GLOBAL

// -- FUNCTIONS

#define NATIVE_ForEachElement( _value_, _range_ ) \
    \
    for ( auto && _value_ : _range_ )

// ~~

#define NATIVE_ForEachIndex( _index_, _count_ ) \
    \
    for ( _index_ = 0; ( _index_ ) < ( _count_ ); ++( _index_ ) )

// ~~

#define NATIVE_FromEachIndex( _index_, _count_ ) \
    \
    for ( _index_ = ( _count_ ) - 1; ( _index_ ) >= 0; --( _index_ ) )

// ~~

#define NATIVE_ForEachIntervalIndex( _index_, _first_index_, _last_index_ ) \
    \
    for ( _index_ = ( _first_index_ ); ( _index_ ) <= ( _last_index_ ); ++( _index_ ) )

// ~~

#define NATIVE_FromEachIntervalIndex( _index_, _first_index_, _last_index_ ) \
    \
    for ( _index_ = ( _last_index_ ); ( _index_ ) >= ( _first_index_ ); --( _index_ ) )

// ~~

#define NATIVE_ForEachRangeIndex( _index_, _first_index_, _post_index_ ) \
    \
    for ( _index_ = ( _first_index_ ); ( _index_ ) < ( _post_index_ ); ++( _index_ ) )

// ~~

#define NATIVE_FromEachRangeIndex( _index_, _first_index_, _post_index_ ) \
    \
    for ( _index_ = ( _post_index_ ) - 1; ( _index_ ) >= ( _first_index_ ); --( _index_ ) )

// ~~

#define NATIVE_Print( _expression_ ) \
    \
    STREAMED_Output << _expression_

// ~~

#define NATIVE_PrintLine( _expression_ ) \
    \
    STREAMED_Output << _expression_ << "\n"

// ~~

#define NATIVE_Dump( _variable_ ) \
    \
    STREAMED_Output << #_variable_ << " = " << _variable_ << "\n"

// ~~

#define NATIVE_PrintError( _expression_ ) \
    \
    STREAMED_Output << _expression_

// ~~

#define NATIVE_PrintErrorLine( _expression_ ) \
    \
    STREAMED_Output << _expression_ << "\n"

// ~~

#define NATIVE_Abort( _message_ ) \
    \
    { \
        NATIVE_PrintErrorLine( __FILE__ << "(" << __LINE__ << ") : " << _message_ ); \
        \
        abort(); \
    }

// ~~

#define NATIVE_Check( _expression_ ) \
    \
    { \
        if ( !( _expression_ ) ) \
        { \
            NATIVE_Abort( #_expression_ );  \
        } \
    }

// ~~

#define NATIVE_GetMinimum2( _first_value_, _second_value_ ) \
    \
    ( ( _first_value_ ) < ( _second_value_ ) ? ( _first_value_ ) : ( _second_value_ ) )

// ~~

#define NATIVE_GetMaximum2( _first_value_, _second_value_ ) \
    \
    ( ( _second_value_ ) < ( _first_value_ ) ? ( _first_value_ ) : ( _second_value_ ) )

// ~~

#define NATIVE_GetMinimum3( _first_value_, _second_value_, _third_value_ ) \
    \
    ( ( _first_value_ ) < ( _second_value_ ) \
      ? ( ( _first_value_ ) < ( _third_value_ ) ? ( _first_value_ ) : ( _third_value_ ) ) \
      : ( ( _second_value_ ) < ( _third_value_ ) ? ( _second_value_ ) : ( _third_value_ ) ) )

// ~~

#define NATIVE_GetMaximum3( _first_value_, _second_value_, _third_value_ ) \
    \
    ( ( _second_value_ ) < ( _first_value_ ) \
      ? ( ( _third_value_ ) < ( _first_value_ ) ? ( _first_value_ ) : ( _third_value_ ) ) \
      : ( ( _third_value_ ) < ( _second_value_ ) ? ( _second_value_ ) : ( _third_value_ ) ) )

// ~~

#define NATIVE_GetSign( _value_ ) \
    \
    ( ( _value_ ) > 0 ? 1 : ( ( _value_ ) < 0 ? -1 : 0 ) )

// ~~

#define NATIVE_HasSameSign( _value_, _other_value_ ) \
    \
    ( ( ( _value_ ) == 0 && ( _other_value_ ) == 0 ) \
      || ( ( _value_ ) > 0 && ( _other_value_ ) > 0 ) \
      || ( ( _value_ ) < 0 && ( _other_value_ ) < 0 ) )

// ~~

#define NATIVE_GetPositive( _value_ ) \
    \
    ( ( _value_ ) >= 0 ? ( _value_ ) : -( _value_ ) )

// ~~

#define NATIVE_GetSquare( _value_ ) \
    \
    ( ( _value_ ) * ( _value_ ) )

// ~~

#define NATIVE_GetXy( _vector_ ) \
    \
    ( _vector_.X ), ( _vector_.Y )

// ~~

#define NATIVE_GetXyz( _vector_ ) \
    \
    ( _vector_ ).X, ( _vector_ ).Y, ( _vector_ ).Z

// ~~

#define NATIVE_GetXyzw( _vector_ ) \
    \
    ( _vector_ ).X, ( _vector_ ).Y, ( _vector_ ).Z, ( _vector_ ).W

// ~~

#define NATIVE_KeepInsideInterval( _value_, _minimum_value_, _maximum_value_ ) \
    \
    { \
        if ( ( _value_ ) < ( _minimum_value_ ) ) \
        { \
            _value_ = ( _minimum_value_ ); \
        } \
        else if ( ( _value_ ) > ( _maximum_value_ ) ) \
        { \
            _value_ = ( _maximum_value_ ); \
        } \
    }
