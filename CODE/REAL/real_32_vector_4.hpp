#pragma once

// == LOCAL

// -- IMPORTS

#include "bool_8.hpp"
#include "real_32.hpp"
#include "streamed_output.hpp"
#include "void.hpp"

// == GLOBAL

// -- TYPES

struct REAL_32_VECTOR_4
{
    // == PUBLIC

    // -- ATTRIBUTES

    REAL_32
        X,
        Y,
        Z,
        W;

    // -- CONSTRUCTORS

    REAL_32_VECTOR_4(
        ) = default;

    // ~~

    REAL_32_VECTOR_4(
        const REAL_32 x,
        const REAL_32 y,
        const REAL_32 z,
        const REAL_32 w
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
            X == 0.0f
            && Y == 0.0f
            && Z == 0.0f
            && W == 0.0f;
    }

    // ~~

    const BOOL_8 IsRoughlyNull(
        VOID
        ) const
    {
        return
            REAL_32_IsRoughlyZero( X )
            && REAL_32_IsRoughlyZero( Y )
            && REAL_32_IsRoughlyZero( Z )
            && REAL_32_IsRoughlyZero( W );
    }

    // ~~

    const BOOL_8 IsRoughlyEqual(
        const REAL_32_VECTOR_4 & vector
        ) const
    {
        return
            REAL_32_IsRoughlyEqual( X, vector.X )
            && REAL_32_IsRoughlyEqual( Y, vector.Y )
            && REAL_32_IsRoughlyEqual( Z, vector.Z )
            && REAL_32_IsRoughlyEqual( W, vector.W );
    }

    // ~~

    const REAL_32 GetLength(
        ) const
    {
        return REAL_32_GetSquareRoot( X * X + Y * Y + Z * Z + W * W );
    }

    // ~~

    const BOOL_8 HasRoughlyUnitLength(
        ) const
    {
        REAL_32
            length;

        length = GetLength();

        return REAL_32_IsRoughlyOne( length );
    }

    // -- OPERATIONS

    VOID SetNull(
        )
    {
        X = 0.0f;
        Y = 0.0f;
        Z = 0.0f;
        W = 0.0f;
    }

    // ~~

    VOID SetFromComponents(
        const REAL_32 x,
        const REAL_32 y,
        const REAL_32 z,
        const REAL_32 w
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
        REAL_32
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
    const REAL_32_VECTOR_4 & vector
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
