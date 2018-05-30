#pragma once

// == LOCAL

// -- IMPORTS

#include "bool_8.hpp"
#include "real_64.hpp"
#include "streamed_output.hpp"
#include "void.hpp"

// == GLOBAL

// -- TYPES

struct REAL_64_VECTOR_4
{
    // == PUBLIC

    // -- ATTRIBUTES

    REAL_64
        X,
        Y,
        Z,
        W;

    // -- CONSTRUCTORS

    REAL_64_VECTOR_4(
        ) = default;

    // ~~

    REAL_64_VECTOR_4(
        const REAL_64 x,
        const REAL_64 y,
        const REAL_64 z,
        const REAL_64 w
        ) :
        X( x ),
        Y( y ),
        Z( z ),
        W( w )
    {
    }

    // -- INQUIRIES

    const BOOL_8 IsNull(
        VOID
        ) const
    {
        return
            X == 0.0
            && Y == 0.0
            && Z == 0.0
            && W == 0.0;
    }

    // ~~

    const BOOL_8 IsRoughlyNull(
        VOID
        ) const
    {
        return
            REAL_64_IsRoughlyZero( X )
            && REAL_64_IsRoughlyZero( Y )
            && REAL_64_IsRoughlyZero( Z )
            && REAL_64_IsRoughlyZero( W );
    }

    // ~~

    const BOOL_8 IsRoughlyEqual(
        const REAL_64_VECTOR_4 & vector
        ) const
    {
        return
            REAL_64_IsRoughlyEqual( X, vector.X )
            && REAL_64_IsRoughlyEqual( Y, vector.Y )
            && REAL_64_IsRoughlyEqual( Z, vector.Z )
            && REAL_64_IsRoughlyEqual( W, vector.W );
    }

    // ~~

    const REAL_64 GetLength(
        ) const
    {
        return REAL_64_GetSquareRoot( X * X + Y * Y + Z * Z + W * W );
    }

    // ~~

    const BOOL_8 HasRoughlyUnitLength(
        ) const
    {
        REAL_64
            length;

        length = GetLength();

        return REAL_64_IsRoughlyOne( length );
    }

    // -- OPERATIONS

    VOID SetNull(
        )
    {
        X = 0.0;
        Y = 0.0;
        Z = 0.0;
        W = 0.0;
    }

    // ~~

    VOID SetFromComponents(
        const REAL_64 x,
        const REAL_64 y,
        const REAL_64 z,
        const REAL_64 w
        )
    {
        X = x;
        Y = y;
        Z = z;
        W = w;
    }

    // ~~

    VOID Normalize(
        )
    {
        REAL_64
            length;

        length = GetLength();

        X /= length;
        Y /= length;
        Z /= length;
        W /= length;
    }
};

// -- OPERATORS

inline STREAMED_OUTPUT & operator<<(
    STREAMED_OUTPUT & output,
    const REAL_64_VECTOR_4 & vector
    )
{
    output
        << "["
        << vector.X
        << ","
        << vector.Y
        << ","
        << vector.Z
        << ","
        << vector.W
        << "]";

    return output;
}
