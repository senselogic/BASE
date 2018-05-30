#pragma once

// == LOCAL

// -- IMPORTS

#include "bool_8.hpp"
#include "debug.hpp"
#include "native.hpp"
#include "real_32.hpp"
#include "streamed_output.hpp"
#include "void.hpp"

// ~~

struct REAL_64_VECTOR_3;

// == GLOBAL

// -- TYPES

struct REAL_32_VECTOR_3
{
    // == PUBLIC

    // -- ATTRIBUTES

    REAL_32
        X,
        Y,
        Z;

    // -- CONSTRUCTORS

    REAL_32_VECTOR_3(
        ) = default;

    // ~~

    REAL_32_VECTOR_3(
        const REAL_32 x,
        const REAL_32 y,
        const REAL_32 z
        ) :
        X( x ),
        Y( y ),
        Z( z )
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
            && Z == 0.0f;
    }

    // ~~

    const BOOL_8 IsRoughlyNull(
        VOID
        ) const
    {
        return
            REAL_32_IsRoughlyZero( X )
            && REAL_32_IsRoughlyZero( Y )
            && REAL_32_IsRoughlyZero( Z );
    }

    // ~~

    const BOOL_8 IsRoughlyEqual(
        const REAL_32_VECTOR_3 & vector
        ) const
    {
        return
            REAL_32_IsRoughlyEqual( X, vector.X )
            && REAL_32_IsRoughlyEqual( Y, vector.Y )
            && REAL_32_IsRoughlyEqual( Z, vector.Z );
    }

    // ~~

    const REAL_32 GetLength(
        ) const
    {
        return REAL_32_GetSquareRoot( X * X + Y * Y + Z * Z );
    }

    // ~~

    const BOOL_8 HasRoughlyNullLength(
        VOID
        ) const
    {
        return
            REAL_32_IsRoughlyZero( X )
            && REAL_32_IsRoughlyZero( Y )
            && REAL_32_IsRoughlyZero( Z );
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

    // ~~

    const REAL_32_VECTOR_3 GetOppositeVector(
        ) const
    {
        return REAL_32_VECTOR_3( -X, -Y, -Z );
    }


    // ~~

    const REAL_32 GetAxisDotProduct(
        const REAL_32_VECTOR_3 & axis_vector
        ) const
    {
        return X * axis_vector.X + Y * axis_vector.Y + Z * axis_vector.Z;
    }

    // ~~

    const REAL_32 GetAngle(
        const REAL_32_VECTOR_3 & axis_vector
        ) const
    {
        REAL_32
            angle_cosinus;

        angle_cosinus = GetAxisDotProduct( axis_vector );

        NATIVE_KeepInsideInterval( angle_cosinus, -1.0f, 1.0f );

        return REAL_32_GetArcCosinus( angle_cosinus );
    }

    // ~~

    VOID GetZUpVector(
        REAL_32_VECTOR_3 & z_up_vector
        ) const
    {
        z_up_vector.X = X;
        z_up_vector.Y = -Z;
        z_up_vector.Z = Y;
    }

    // ~~

    VOID GetXyzAxesFromZxAxes(
        REAL_32_VECTOR_3 & x_axis_vector,
        REAL_32_VECTOR_3 & y_axis_vector,
        REAL_32_VECTOR_3 & z_axis_vector,
        const REAL_32_VECTOR_3 & old_x_axis_vector
        ) const
    {
        DEBUG_Check( HasRoughlyUnitLength() );
        DEBUG_Check( old_x_axis_vector.HasRoughlyUnitLength() );

        z_axis_vector = *this;
        y_axis_vector.SetAxisCrossProductVector( z_axis_vector, old_x_axis_vector );

        DEBUG_Check( !y_axis_vector.HasRoughlyNullLength() );

        y_axis_vector.Normalize();
        x_axis_vector.SetAxisCrossProductVector( y_axis_vector, z_axis_vector );

        DEBUG_Check( x_axis_vector.HasRoughlyUnitLength() );
        DEBUG_Check( y_axis_vector.HasRoughlyUnitLength() );
        DEBUG_Check( z_axis_vector.HasRoughlyUnitLength() );
    }

    // ~~

    VOID GetXyzAxesFromZyAxes(
        REAL_32_VECTOR_3 & x_axis_vector,
        REAL_32_VECTOR_3 & y_axis_vector,
        REAL_32_VECTOR_3 & z_axis_vector,
        const REAL_32_VECTOR_3 & old_y_axis_vector
        ) const
    {
        DEBUG_Check( HasRoughlyUnitLength() );
        DEBUG_Check( old_y_axis_vector.HasRoughlyUnitLength() );

        z_axis_vector = *this;
        x_axis_vector.SetAxisCrossProductVector( old_y_axis_vector, z_axis_vector );

        DEBUG_Check( !x_axis_vector.HasRoughlyNullLength() );

        x_axis_vector.Normalize();
        y_axis_vector.SetAxisCrossProductVector( z_axis_vector, x_axis_vector );

        DEBUG_Check( x_axis_vector.HasRoughlyUnitLength() );
        DEBUG_Check( y_axis_vector.HasRoughlyUnitLength() );
        DEBUG_Check( z_axis_vector.HasRoughlyUnitLength() );
    }

    // ~~

    VOID GetXyzAxesFromZAxisVector(
        REAL_32_VECTOR_3 & x_axis_vector,
        REAL_32_VECTOR_3 & y_axis_vector,
        REAL_32_VECTOR_3 & z_axis_vector
        ) const
    {
        DEBUG_Check( HasRoughlyUnitLength() );

        z_axis_vector = *this;
        x_axis_vector.SetAxisCrossProductVector( REAL_32_VECTOR_3( 0.0f, 1.0f, 0.0f ), z_axis_vector );

        if ( x_axis_vector.HasRoughlyNullLength() )
        {
            x_axis_vector = REAL_32_VECTOR_3( 1.0f, 0.0f, 0.0f );

            if ( z_axis_vector.Y > 0.0f )
            {
                y_axis_vector = REAL_32_VECTOR_3( 0.0f, 0.0f, -1.0f );
            }
            else
            {
                y_axis_vector = REAL_32_VECTOR_3( 0.0f, 0.0f, 1.0f );
            }
        }
        else
        {
            x_axis_vector.Normalize();
            y_axis_vector.SetAxisCrossProductVector( z_axis_vector, x_axis_vector );
        }

        DEBUG_Check( x_axis_vector.HasRoughlyUnitLength() );
        DEBUG_Check( y_axis_vector.HasRoughlyUnitLength() );
        DEBUG_Check( z_axis_vector.HasRoughlyUnitLength() );
    }

    // -- OPERATIONS

    VOID SetNull(
        )
    {
        X = 0.0f;
        Y = 0.0f;
        Z = 0.0f;
    }

    // ~~

    VOID SetFromComponents(
        const REAL_32 x,
        const REAL_32 y,
        const REAL_32 z
        )
    {
        X = x;
        Y = y;
        Z = z;
    }

    // ~~

    VOID SetFromValue(
        const REAL_32 value
        )
    {
        X = value;
        Y = value;
        Z = value;
    }

    // ~~

    VOID SetFromVector(
        const REAL_64_VECTOR_3 & vector
        );

    // ~~

    VOID AddComponents(
        const REAL_32 x,
        const REAL_32 y,
        const REAL_32 z
        )
    {
        X += x;
        Y += y;
        Z += z;
    }

    // ~~

    VOID AddValue(
        const REAL_32 value
        )
    {
        X += value;
        Y += value;
        Z += value;
    }

    // ~~

    VOID AddVector(
        const REAL_32_VECTOR_3 & vector
        )
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
    }

    // ~~

    VOID SetSumVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector
        )
    {
        X = first_vector.X + second_vector.X;
        Y = first_vector.Y + second_vector.Y;
        Z = first_vector.Z + second_vector.Z;
    }

    // ~~

    VOID SetSumVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector,
        const REAL_32_VECTOR_3 & third_vector
        )
    {
        X = first_vector.X + second_vector.X + third_vector.X;
        Y = first_vector.Y + second_vector.Y + third_vector.Y;
        Z = first_vector.Z + second_vector.Z + third_vector.Z;
    }

    // ~~

    VOID SetSumVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector,
        const REAL_32_VECTOR_3 & third_vector,
        const REAL_32_VECTOR_3 & fourth_vector
        )
    {
        X = first_vector.X + second_vector.X + third_vector.X + fourth_vector.X;
        Y = first_vector.Y + second_vector.Y + third_vector.Y + fourth_vector.Y;
        Z = first_vector.Z + second_vector.Z + third_vector.Z + fourth_vector.Z;
    }

    // ~~

    VOID Negate(
        )
    {
        X = -X;
        Y = -Y;
        Z = -Z;
    }

    // ~~

    VOID SubstractComponents(
        const REAL_32 x,
        const REAL_32 y,
        const REAL_32 z
        )
    {
        X -= x;
        Y -= y;
        Z -= z;
    }

    // ~~

    VOID SubstractValue(
        const REAL_32 value
        )
    {
        X -= value;
        Y -= value;
        Z -= value;
    }

    // ~~

    VOID SubstractVector(
        const REAL_32_VECTOR_3 & vector
        )
    {
        X -= vector.X;
        Y -= vector.Y;
        Z -= vector.Z;
    }

    // ~~

    VOID SetDifferenceVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector
        )
    {
        X = first_vector.X - second_vector.X;
        Y = first_vector.Y - second_vector.Y;
        Z = first_vector.Z - second_vector.Z;
    }

    // ~~

    VOID SetScaledDifferenceVector(
        const REAL_32 difference_scale,
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector
        )
    {
        X = difference_scale * ( first_vector.X - second_vector.X );
        Y = difference_scale * ( first_vector.Y - second_vector.Y );
        Z = difference_scale * ( first_vector.Z - second_vector.Z );
    }

    // ~~

    VOID SetScaledDifferenceVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector,
        const REAL_32 second_vector_scale
        )
    {
        X = first_vector.X - second_vector.X * second_vector_scale;
        Y = first_vector.Y - second_vector.Y * second_vector_scale;
        Z = first_vector.Z - second_vector.Z * second_vector_scale;
    }

    // ~~

    VOID SetScaledDifferenceVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32 first_vector_scale,
        const REAL_32_VECTOR_3 & second_vector,
        const REAL_32 second_vector_scale
        )
    {
        X = first_vector.X * first_vector_scale - second_vector.X * second_vector_scale;
        Y = first_vector.Y * first_vector_scale - second_vector.Y * second_vector_scale;
        Z = first_vector.Z * first_vector_scale - second_vector.Z * second_vector_scale;
    }

    // ~~

    VOID SetTranslationVector(
        const REAL_32_VECTOR_3 & origin_vector,
        const REAL_32_VECTOR_3 & target_vector
        )
    {
        X = target_vector.X - origin_vector.X;
        Y = target_vector.Y - origin_vector.Y;
        Z = target_vector.Z - origin_vector.Z;
    }

    // ~~

    VOID SetTranslationAxisVector(
        const REAL_32_VECTOR_3 & origin_vector,
        const REAL_32_VECTOR_3 & target_vector
        )
    {
        X = target_vector.X - origin_vector.X;
        Y = target_vector.Y - origin_vector.Y;
        Z = target_vector.Z - origin_vector.Z;

        Normalize();
    }

    // ~~

    VOID MultiplyByComponents(
        const REAL_32 x,
        const REAL_32 y,
        const REAL_32 z
        )
    {
        X *= x;
        Y *= z;
        Z *= z;
    }

    // ~~

    VOID MultiplyByValue(
        const REAL_32 value
        )
    {
        X *= value;
        Y *= value;
        Z *= value;
    }

    // ~~

    VOID MultiplyByVector(
        const REAL_32_VECTOR_3 & vector
        )
    {
        X *= vector.X;
        Y *= vector.Y;
        Z *= vector.Z;
    }

    // ~~

    VOID SetProductVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector
        )
    {
        X = first_vector.X * second_vector.X;
        Y = first_vector.Y * second_vector.Y;
        Z = first_vector.Z * second_vector.Z;
    }
    // ~~

    VOID SetProductVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector,
        const REAL_32_VECTOR_3 & third_vector
        )
    {
        X = first_vector.X * second_vector.X * third_vector.X;
        Y = first_vector.Y * second_vector.Y * third_vector.Y;
        Z = first_vector.Z * second_vector.Z * third_vector.Z;
    }

    // ~~

    VOID SetScaledVector(
        const REAL_32_VECTOR_3 & vector,
        const REAL_32 scale
        )
    {
        X = vector.X * scale;
        Y = vector.Y * scale;
        Z = vector.Z * scale;
    }

    // ~~

    VOID AddScaledVector(
        const REAL_32_VECTOR_3 & vector,
        const REAL_32 scale
        )
    {
        X += vector.X * scale;
        Y += vector.Y * scale;
        Z += vector.Z * scale;
    }

    // ~~

    VOID SetScaledSumVector(
        const REAL_32 sum_scale,
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector
        )
    {
        X = sum_scale * ( first_vector.X + second_vector.X );
        Y = sum_scale * ( first_vector.Y + second_vector.Y );
        Z = sum_scale * ( first_vector.Z + second_vector.Z );
    }

    // ~~

    VOID AddScaledSumVector(
        const REAL_32 sum_scale,
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector
        )
    {
        X += sum_scale * ( first_vector.X + second_vector.X );
        Y += sum_scale * ( first_vector.Y + second_vector.Y );
        Z += sum_scale * ( first_vector.Z + second_vector.Z );
    }

    // ~~

    VOID SetScaledSumVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector,
        const REAL_32 second_vector_scale
        )
    {
        X = first_vector.X + second_vector.X * second_vector_scale;
        Y = first_vector.Y + second_vector.Y * second_vector_scale;
        Z = first_vector.Z + second_vector.Z * second_vector_scale;
    }

    // ~~

    VOID AddScaledSumVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector,
        const REAL_32 second_vector_scale
        )
    {
        X += first_vector.X + second_vector.X * second_vector_scale;
        Y += first_vector.Y + second_vector.Y * second_vector_scale;
        Z += first_vector.Z + second_vector.Z * second_vector_scale;
    }

    // ~~

    VOID SetScaledSumVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32 first_vector_scale,
        const REAL_32_VECTOR_3 & second_vector,
        const REAL_32 second_vector_scale
        )
    {
        X = first_vector.X * first_vector_scale + second_vector.X * second_vector_scale;
        Y = first_vector.Y * first_vector_scale + second_vector.Y * second_vector_scale;
        Z = first_vector.Z * first_vector_scale + second_vector.Z * second_vector_scale;
    }

    // ~~

    VOID AddScaledSumVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32 first_vector_scale,
        const REAL_32_VECTOR_3 & second_vector,
        const REAL_32 second_vector_scale
        )
    {
        X += first_vector.X * first_vector_scale + second_vector.X * second_vector_scale;
        Y += first_vector.Y * first_vector_scale + second_vector.Y * second_vector_scale;
        Z += first_vector.Z * first_vector_scale + second_vector.Z * second_vector_scale;
    }

    // ~~

    VOID SetScaledSumVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector,
        const REAL_32 second_vector_scale,
        const REAL_32_VECTOR_3 & third_vector,
        const REAL_32 third_vector_scale
        )
    {
        X = first_vector.X + second_vector.X * second_vector_scale + third_vector.X * third_vector_scale;
        Y = first_vector.Y + second_vector.Y * second_vector_scale + third_vector.Y * third_vector_scale;
        Z = first_vector.Z + second_vector.Z * second_vector_scale + third_vector.Z * third_vector_scale;
    }

    // ~~

    VOID AddScaledSumVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector,
        const REAL_32 second_vector_scale,
        const REAL_32_VECTOR_3 & third_vector,
        const REAL_32 third_vector_scale
        )
    {
        X += first_vector.X + second_vector.X * second_vector_scale + third_vector.X * third_vector_scale;
        Y += first_vector.Y + second_vector.Y * second_vector_scale + third_vector.Y * third_vector_scale;
        Z += first_vector.Z + second_vector.Z * second_vector_scale + third_vector.Z * third_vector_scale;
    }

    // ~~

    VOID DivideByComponents(
        const REAL_32 x,
        const REAL_32 y,
        const REAL_32 z
        )
    {
        DEBUG_Check( x != 0.0f );
        DEBUG_Check( y != 0.0f );
        DEBUG_Check( z != 0.0f );

        X /= x;
        Y /= y;
        Z /= z;
    }

    // ~~

    VOID DivideByValue(
        const REAL_32 value
        )
    {
        DEBUG_Check( value != 0.0f );

        X /= value;
        Y /= value;
        Z /= value;
    }

    // ~~

    VOID DivideByVector(
        const REAL_32_VECTOR_3 & vector
        )
    {
        DEBUG_Check( vector.X != 0.0f );
        DEBUG_Check( vector.Y != 0.0f );
        DEBUG_Check( vector.Z != 0.0f );

        X /= vector.X;
        Y /= vector.Y;
        Z /= vector.Z;
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
    }

    // ~~

    VOID SetAverageVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector
        )
    {
        X = ( first_vector.X + second_vector.X ) * 0.5f;
        Y = ( first_vector.Y + second_vector.Y );
        Z = ( first_vector.Z + second_vector.Z );
    }

    // ~~

    VOID SetAverageVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector,
        const REAL_32_VECTOR_3 & third_vector
        )
    {
        X = ( first_vector.X + second_vector.X + third_vector.X ) * ( 1.0f / 3.0f );
        Y = ( first_vector.Y + second_vector.Y + third_vector.Y ) * ( 1.0f / 3.0f );
        Z = ( first_vector.Z + second_vector.Z + third_vector.Z ) * ( 1.0f / 3.0f );
    }

    // ~~

    VOID SetAverageVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector,
        const REAL_32_VECTOR_3 & third_vector,
        const REAL_32_VECTOR_3 & fourth_vector
        )
    {
        X = ( first_vector.X + second_vector.X + third_vector.X + fourth_vector.X ) * 0.25f;
        Y = ( first_vector.Y + second_vector.Y + third_vector.Y + fourth_vector.Y ) * 0.25f;
        Z = ( first_vector.Z + second_vector.Z + third_vector.Z + fourth_vector.Z ) * 0.25f;
    }

    // ~~

    VOID AddInterpolatedVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector,
        const REAL_32 second_vector_ratio
        )
    {
        X += ( second_vector.X - first_vector.X ) * second_vector_ratio;
        Y += ( second_vector.Y - first_vector.Y ) * second_vector_ratio;
        Z += ( second_vector.Z - first_vector.Z ) * second_vector_ratio;
    }

    // ~~

    VOID SetInterpolatedVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector,
        const REAL_32 second_vector_ratio
        )
    {
        X = first_vector.X + ( second_vector.X - first_vector.X ) * second_vector_ratio;
        Y = first_vector.Y + ( second_vector.Y - first_vector.Y ) * second_vector_ratio;
        Z = first_vector.Z + ( second_vector.Z - first_vector.Z ) * second_vector_ratio;
    }

    // ~~

    VOID SetInterpolatedVector(
        const REAL_32_VECTOR_3 & lower_left_vector,
        const REAL_32_VECTOR_3 & lower_right_vector,
        const REAL_32_VECTOR_3 & upper_left_vector,
        const REAL_32_VECTOR_3 & upper_right_vector,
        const REAL_32 right_vector_ratio,
        const REAL_32 upper_vector_ratio
        )
    {
        REAL_32_VECTOR_3
            lower_interpolated_vector,
            upper_interpolated_vector;

        lower_interpolated_vector.SetInterpolatedVector(
            lower_left_vector,
            lower_right_vector,
            right_vector_ratio
            );

        upper_interpolated_vector.SetInterpolatedVector(
            upper_left_vector,
            upper_right_vector,
            right_vector_ratio
            );

        SetInterpolatedVector(
            lower_interpolated_vector,
            upper_interpolated_vector,
            upper_vector_ratio
            );
    }

    // ~~

    VOID SetSphericalInterpolationVector(
        const REAL_32_VECTOR_3 & first_axis_vector,
        const REAL_32_VECTOR_3 & second_axis_vector,
        const REAL_32 second_axis_ratio
        )
    {
        REAL_32
            angle_cosinus,
            one_over_angle_sinus,
            first_axis_factor,
            second_axis_factor;
        REAL_32
            angle;

        DEBUG_Check( first_axis_vector.HasRoughlyUnitLength() );
        DEBUG_Check( second_axis_vector.HasRoughlyUnitLength() );

        if ( second_axis_ratio == 0.0f )
        {
            *this = first_axis_vector;
        }
        else if ( second_axis_ratio == 1.0f )
        {
            *this = second_axis_vector;
        }
        else
        {
            angle_cosinus = first_axis_vector.GetAxisDotProduct( second_axis_vector );

            if ( REAL_32_IsRoughlyOne( angle_cosinus ) )
            {
                *this = first_axis_vector;
            }
            else
            {
                NATIVE_KeepInsideInterval( angle_cosinus, -1.0f, 1.0f );

                angle = REAL_32_GetArcCosinus( angle_cosinus );
                one_over_angle_sinus = 1.0f / REAL_32_GetSinus( angle );

                first_axis_factor = REAL_32_GetSinus( ( 1.0f - second_axis_ratio ) * angle ) * one_over_angle_sinus;
                second_axis_factor = REAL_32_GetSinus( second_axis_ratio * angle ) * one_over_angle_sinus;

                X = first_axis_vector.X * first_axis_factor + second_axis_vector.X * second_axis_factor;
                Y = first_axis_vector.Y * first_axis_factor + second_axis_vector.Y * second_axis_factor;
                Z = first_axis_vector.Z * first_axis_factor + second_axis_vector.Z * second_axis_factor;

                DEBUG_Check( HasRoughlyUnitLength() );
            }
        }
    }

    // ~~

    VOID SetSphericalAverageVector(
        const REAL_32_VECTOR_3 & first_axis_vector,
        const REAL_32_VECTOR_3 & second_axis_vector
        )
    {
        SetSphericalInterpolationVector( first_axis_vector, second_axis_vector, 0.5f );
    }

    // ~~

    VOID SetSphericalAverageVector(
        const REAL_32_VECTOR_3 & first_axis_vector,
        const REAL_32_VECTOR_3 & second_axis_vector,
        const REAL_32_VECTOR_3 & third_axis_vector
        )
    {
        REAL_32_VECTOR_3
            middle_axis_vector;

        middle_axis_vector.SetSphericalInterpolationVector( first_axis_vector, second_axis_vector, 0.5f );
        SetSphericalInterpolationVector( middle_axis_vector, third_axis_vector, 0.5f );
    }

    // ~~

    VOID SetCrossProductVector(
        const REAL_32_VECTOR_3 & first_vector,
        const REAL_32_VECTOR_3 & second_vector
        )
    {
        X = first_vector.Y * second_vector.Z - first_vector.Z * second_vector.Y;
        Y = first_vector.Z * second_vector.X - first_vector.X * second_vector.Z;
        Z = first_vector.X * second_vector.Y - first_vector.Y * second_vector.X;
    }

    // ~~

    VOID SetAxisCrossProductVector(
        const REAL_32_VECTOR_3 & first_axis_vector,
        const REAL_32_VECTOR_3 & second_axis_vector
        )
    {
        DEBUG_Check( first_axis_vector.HasRoughlyUnitLength() );
        DEBUG_Check( second_axis_vector.HasRoughlyUnitLength() );

        X = first_axis_vector.Y * second_axis_vector.Z - first_axis_vector.Z * second_axis_vector.Y;
        Y = first_axis_vector.Z * second_axis_vector.X - first_axis_vector.X * second_axis_vector.Z;
        Z = first_axis_vector.X * second_axis_vector.Y - first_axis_vector.Y * second_axis_vector.X;
    }
};

// -- OPERATORS

inline STREAMED_OUTPUT & operator<<(
    STREAMED_OUTPUT & output,
    const REAL_32_VECTOR_3 & vector
    )
{
    output
        << "["
        << vector.X
        << ","
        << vector.Y
        << ","
        << vector.Z
        << "]";

    return output;
}
