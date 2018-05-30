#pragma once

// == LOCAL

// -- IMPORTS

#include "bool_8.hpp"
#include "debug.hpp"
#include "real_64.hpp"
#include "real_64_vector_3.hpp"
#include "streamed_output.hpp"
#include "void.hpp"

// == GLOBAL

// -- TYPES

struct REAL_64_BOX
{
    // == PUBLIC

    // -- ATTRIBUTES

    BOOL_8
        IsEmpty;
    REAL_64_VECTOR_3
        MinimumPositionVector,
        MaximumPositionVector;

    // -- CONSTRUCTORS

    REAL_64_BOX(
        ) :
        IsEmpty( true ),
        MinimumPositionVector( 0.0, 0.0, 0.0 ),
        MaximumPositionVector( 0.0, 0.0, 0.0 )
    {
    }

    // -- INQUIRIES

    const REAL_64 GetWidth(
        ) const
    {
        DEBUG_Check( !IsEmpty );

        return MaximumPositionVector.X - MinimumPositionVector.X;
    }

    // ~~

    const REAL_64 GetHeight(
        ) const
    {
        DEBUG_Check( !IsEmpty );

        return MaximumPositionVector.Y - MinimumPositionVector.Y;
    }

    // ~~

    const REAL_64 GetDepth(
        ) const
    {
        DEBUG_Check( !IsEmpty );

        return MaximumPositionVector.Z - MinimumPositionVector.Z;
    }

    // ~~

    VOID GetCenterVector(
        REAL_64_VECTOR_3 & center_vector
        ) const
    {
        DEBUG_Check( !IsEmpty );

        center_vector.SetAverageVector( MinimumPositionVector, MaximumPositionVector );
    }

    // ~~

    VOID GetSizeVector(
        REAL_64_VECTOR_3 & size_vector
        ) const
    {
        DEBUG_Check( !IsEmpty );

        size_vector.SetDifferenceVector( MaximumPositionVector, MinimumPositionVector );
    }

    // ~~

    VOID GetHalfSizeVector(
        REAL_64_VECTOR_3 & half_size_vector
        ) const
    {
        DEBUG_Check( !IsEmpty );

        half_size_vector.SetScaledDifferenceVector( 0.5, MaximumPositionVector, MinimumPositionVector );
    }

    // ~~

    const BOOL_8 ContainsPositionVector(
        const REAL_64_VECTOR_3 & position_vector
        ) const
    {
        return
            !IsEmpty
            && position_vector.X >= MinimumPositionVector.X
            && position_vector.X <= MaximumPositionVector.X
            && position_vector.Z >= MinimumPositionVector.Z
            && position_vector.Z <= MaximumPositionVector.Z
            && position_vector.Y >= MinimumPositionVector.Y
            && position_vector.Y <= MaximumPositionVector.Y;
    }

    // ~~

    const BOOL_8 ContainsBox(
        const REAL_64_BOX & box
        ) const
    {
        return
            !IsEmpty
            && !box.IsEmpty
            && box.MinimumPositionVector.X >= MinimumPositionVector.X
            && box.MaximumPositionVector.X <= MaximumPositionVector.X
            && box.MinimumPositionVector.Z >= MinimumPositionVector.Z
            && box.MaximumPositionVector.Z <= MaximumPositionVector.Z
            && box.MinimumPositionVector.Y >= MinimumPositionVector.Y
            && box.MaximumPositionVector.Y <= MaximumPositionVector.Y;
    }

    // ~~

    const BOOL_8 IntersectsBox(
        const REAL_64_BOX & box
        ) const
    {
        return
            !IsEmpty
            && !box.IsEmpty
            && box.MinimumPositionVector.X <= MaximumPositionVector.X
            && box.MaximumPositionVector.X >= MinimumPositionVector.X
            && box.MinimumPositionVector.Z <= MaximumPositionVector.Z
            && box.MaximumPositionVector.Z >= MinimumPositionVector.Z
            && box.MinimumPositionVector.Y <= MaximumPositionVector.Y
            && box.MaximumPositionVector.Y >= MinimumPositionVector.Y;
    }

    // -- OPERATIONS

    VOID SetEmpty(
        )
    {
        IsEmpty = true;
    }

    // ~~

    VOID AddBox(
        const REAL_64_BOX & box
        )
    {
        if ( !box.IsEmpty )
        {
            if ( IsEmpty )
            {
                *this = box;
            }
            else
            {
                if ( box.MinimumPositionVector.X < MinimumPositionVector.X )
                {
                    MinimumPositionVector.X = box.MinimumPositionVector.X;
                }

                if ( box.MinimumPositionVector.Y < MinimumPositionVector.Y )
                {
                    MinimumPositionVector.Y = box.MinimumPositionVector.Y;
                }

                if ( box.MinimumPositionVector.Z < MinimumPositionVector.Z )
                {
                    MinimumPositionVector.Z = box.MinimumPositionVector.Z;
                }

                if ( box.MaximumPositionVector.X > MaximumPositionVector.X )
                {
                    MaximumPositionVector.X = box.MaximumPositionVector.X;
                }

                if ( box.MaximumPositionVector.Y > MaximumPositionVector.Y )
                {
                    MaximumPositionVector.Y = box.MaximumPositionVector.Y;
                }

                if ( box.MaximumPositionVector.Z > MaximumPositionVector.Z )
                {
                    MaximumPositionVector.Z = box.MaximumPositionVector.Z;
                }
            }
        }
    }

    // ~~

    VOID AddPositionVector(
        const REAL_64_VECTOR_3 & position_vector
        )
    {
        if ( IsEmpty )
        {
            IsEmpty = false;
            MinimumPositionVector = position_vector;
            MaximumPositionVector = position_vector;
        }
        else
        {
            if ( position_vector.X < MinimumPositionVector.X )
            {
                MinimumPositionVector.X = position_vector.X;
            }

            if ( position_vector.Y < MinimumPositionVector.Y )
            {
                MinimumPositionVector.Y = position_vector.Y;
            }

            if ( position_vector.Z < MinimumPositionVector.Z )
            {
                MinimumPositionVector.Z = position_vector.Z;
            }

            if ( position_vector.X > MaximumPositionVector.X )
            {
                MaximumPositionVector.X = position_vector.X;
            }

            if ( position_vector.Y > MaximumPositionVector.Y )
            {
                MaximumPositionVector.Y = position_vector.Y;
            }

            if ( position_vector.Z > MaximumPositionVector.Z )
            {
                MaximumPositionVector.Z = position_vector.Z;
            }
        }
    }
};

// -- OPERATORS

inline STREAMED_OUTPUT & operator<<(
    STREAMED_OUTPUT & output,
    const REAL_64_BOX & box
    )
{
    if ( box.IsEmpty )
    {
        output
            << "{}\n";
    }
    else
    {
        output
            << "{"
            << box.MinimumPositionVector
            << ","
            << box.MaximumPositionVector
            << "}";
    }

    return output;
}
