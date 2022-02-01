#pragma once

// == LOCAL

// -- IMPORTS

#include "bool_8.hpp"
#include "debug.hpp"
#include "native.hpp"
#include "real_64.hpp"
#include "streamed_output.hpp"
#include "void.hpp"

// ~~

struct REAL_32_VECTOR_3;

// == GLOBAL

// -- TYPES

struct REAL_64_VECTOR_3
{
    // == PUBLIC

    // -- ATTRIBUTES

    REAL_64
        X,
        Y,
        Z;

    // -- CONSTRUCTORS

    REAL_64_VECTOR_3(
        ) = default;

    // ~~

    REAL_64_VECTOR_3(
        const REAL_64 x,
        const REAL_64 y,
        const REAL_64 z
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
            X == 0.0
            && Y == 0.0
            && Z == 0.0;
    }

    // ~~

    const BOOL_8 IsRoughlyNull(
        VOID
        ) const
    {
        return
            REAL_64_IsRoughlyZero( X )
            && REAL_64_IsRoughlyZero( Y )
            && REAL_64_IsRoughlyZero( Z );
    }

    // ~~

    const BOOL_8 IsRoughlyEqual(
        const REAL_64_VECTOR_3 & vector
        ) const
    {
        return
            REAL_64_IsRoughlyEqual( X, vector.X )
            && REAL_64_IsRoughlyEqual( Y, vector.Y )
            && REAL_64_IsRoughlyEqual( Z, vector.Z );
    }

    // ~~

    const REAL_64 GetLength(
        ) const
    {
        return REAL_64_GetSquareRoot( X * X + Y * Y + Z * Z );
    }

    // ~~

    const BOOL_8 HasRoughlyNullLength(
        VOID
        ) const
    {
        return
            REAL_64_IsRoughlyZero( X )
            && REAL_64_IsRoughlyZero( Y )
            && REAL_64_IsRoughlyZero( Z );
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

    // ~~

    const REAL_64_VECTOR_3 GetOppositeVector(
        ) const
    {
        return REAL_64_VECTOR_3( -X, -Y, -Z );
    }

    // ~~

    const REAL_64 GetAxisDotProduct(
        const REAL_64_VECTOR_3 & axis_vector
        ) const
    {
        return X * axis_vector.X + Y * axis_vector.Y + Z * axis_vector.Z;
    }

    // ~~

    const REAL_64 GetAngle(
        const REAL_64_VECTOR_3 & axis_vector
        ) const
    {
        REAL_64
            angle_cosinus;

        angle_cosinus = GetAxisDotProduct( axis_vector );

        NATIVE_KeepInsideInterval( angle_cosinus, -1.0, 1.0 );

        return REAL_64_GetArcCosinus( angle_cosinus );
    }

    // ~~

    VOID GetZUpVector(
        REAL_64_VECTOR_3 & z_up_vector
        ) const
    {
        z_up_vector.X = X;
        z_up_vector.Y = -Z;
        z_up_vector.Z = Y;
    }

    // ~~

    VOID GetXyzAxesFromZxAxes(
        REAL_64_VECTOR_3 & x_axis_vector,
        REAL_64_VECTOR_3 & y_axis_vector,
        REAL_64_VECTOR_3 & z_axis_vector,
        const REAL_64_VECTOR_3 & old_x_axis_vector
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
        REAL_64_VECTOR_3 & x_axis_vector,
        REAL_64_VECTOR_3 & y_axis_vector,
        REAL_64_VECTOR_3 & z_axis_vector,
        const REAL_64_VECTOR_3 & old_y_axis_vector
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
        REAL_64_VECTOR_3 & x_axis_vector,
        REAL_64_VECTOR_3 & y_axis_vector,
        REAL_64_VECTOR_3 & z_axis_vector
        ) const
    {
        DEBUG_Check( HasRoughlyUnitLength() );

        z_axis_vector = *this;
        x_axis_vector.SetAxisCrossProductVector( REAL_64_VECTOR_3( 0.0, 1.0, 0.0 ), z_axis_vector );

        if ( x_axis_vector.HasRoughlyNullLength() )
        {
            x_axis_vector = REAL_64_VECTOR_3( 1.0, 0.0, 0.0 );

            if ( z_axis_vector.Y > 0.0 )
            {
                y_axis_vector = REAL_64_VECTOR_3( 0.0, 0.0, -1.0 );
            }
            else
            {
                y_axis_vector = REAL_64_VECTOR_3( 0.0, 0.0, 1.0 );
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
        X = 0.0;
        Y = 0.0;
        Z = 0.0;
    }

    // ~~

    VOID SetFromComponents(
        const REAL_64 x,
        const REAL_64 y,
        const REAL_64 z
        )
    {
        X = x;
        Y = y;
        Z = z;
    }

    // ~~

    VOID SetFromValue(
        const REAL_64 value
        )
    {
        X = value;
        Y = value;
        Z = value;
    }

    // ~~

    VOID SetFromVector(
        const REAL_32_VECTOR_3 & vector
        );

    // ~~

    VOID AddComponents(
        const REAL_64 x,
        const REAL_64 y,
        const REAL_64 z
        )
    {
        X += x;
        Y += y;
        Z += z;
    }

    // ~~

    VOID AddValue(
        const REAL_64 value
        )
    {
        X += value;
        Y += value;
        Z += value;
    }

    // ~~

    VOID AddVector(
        const REAL_64_VECTOR_3 & vector
        )
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
    }

    // ~~

    VOID SetSumVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector
        )
    {
        X = first_vector.X + second_vector.X;
        Y = first_vector.Y + second_vector.Y;
        Z = first_vector.Z + second_vector.Z;
    }

    // ~~

    VOID SetSumVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector,
        const REAL_64_VECTOR_3 & third_vector
        )
    {
        X = first_vector.X + second_vector.X + third_vector.X;
        Y = first_vector.Y + second_vector.Y + third_vector.Y;
        Z = first_vector.Z + second_vector.Z + third_vector.Z;
    }

    // ~~

    VOID SetSumVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector,
        const REAL_64_VECTOR_3 & third_vector,
        const REAL_64_VECTOR_3 & fourth_vector
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
        const REAL_64 x,
        const REAL_64 y,
        const REAL_64 z
        )
    {
        X -= x;
        Y -= y;
        Z -= z;
    }

    // ~~

    VOID SubstractValue(
        const REAL_64 value
        )
    {
        X -= value;
        Y -= value;
        Z -= value;
    }

    // ~~

    VOID SubstractVector(
        const REAL_64_VECTOR_3 & vector
        )
    {
        X -= vector.X;
        Y -= vector.Y;
        Z -= vector.Z;
    }

    // ~~

    VOID SetDifferenceVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector
        )
    {
        X = first_vector.X - second_vector.X;
        Y = first_vector.Y - second_vector.Y;
        Z = first_vector.Z - second_vector.Z;
    }

    // ~~

    VOID SetScaledDifferenceVector(
        const REAL_64 difference_scale,
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector
        )
    {
        X = difference_scale * ( first_vector.X - second_vector.X );
        Y = difference_scale * ( first_vector.Y - second_vector.Y );
        Z = difference_scale * ( first_vector.Z - second_vector.Z );
    }

    // ~~

    VOID SetScaledDifferenceVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector,
        const REAL_64 second_vector_scale
        )
    {
        X = first_vector.X - second_vector.X * second_vector_scale;
        Y = first_vector.Y - second_vector.Y * second_vector_scale;
        Z = first_vector.Z - second_vector.Z * second_vector_scale;
    }

    // ~~

    VOID SetScaledDifferenceVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64 first_vector_scale,
        const REAL_64_VECTOR_3 & second_vector,
        const REAL_64 second_vector_scale
        )
    {
        X = first_vector.X * first_vector_scale - second_vector.X * second_vector_scale;
        Y = first_vector.Y * first_vector_scale - second_vector.Y * second_vector_scale;
        Z = first_vector.Z * first_vector_scale - second_vector.Z * second_vector_scale;
    }

    // ~~

    VOID SetTranslationVector(
        const REAL_64_VECTOR_3 & origin_vector,
        const REAL_64_VECTOR_3 & target_vector
        )
    {
        X = target_vector.X - origin_vector.X;
        Y = target_vector.Y - origin_vector.Y;
        Z = target_vector.Z - origin_vector.Z;
    }

    // ~~

    VOID SetTranslationAxisVector(
        const REAL_64_VECTOR_3 & origin_vector,
        const REAL_64_VECTOR_3 & target_vector
        )
    {
        X = target_vector.X - origin_vector.X;
        Y = target_vector.Y - origin_vector.Y;
        Z = target_vector.Z - origin_vector.Z;

        Normalize();
    }

    // ~~

    VOID MultiplyByComponents(
        const REAL_64 x,
        const REAL_64 y,
        const REAL_64 z
        )
    {
        X *= x;
        Y *= z;
        Z *= z;
    }

    // ~~

    VOID MultiplyByValue(
        const REAL_64 value
        )
    {
        X *= value;
        Y *= value;
        Z *= value;
    }

    // ~~

    VOID MultiplyByVector(
        const REAL_64_VECTOR_3 & vector
        )
    {
        X *= vector.X;
        Y *= vector.Y;
        Z *= vector.Z;
    }

    // ~~

    VOID SetProductVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector
        )
    {
        X = first_vector.X * second_vector.X;
        Y = first_vector.Y * second_vector.Y;
        Z = first_vector.Z * second_vector.Z;
    }
    // ~~

    VOID SetProductVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector,
        const REAL_64_VECTOR_3 & third_vector
        )
    {
        X = first_vector.X * second_vector.X * third_vector.X;
        Y = first_vector.Y * second_vector.Y * third_vector.Y;
        Z = first_vector.Z * second_vector.Z * third_vector.Z;
    }

    // ~~

    VOID SetScaledVector(
        const REAL_64_VECTOR_3 & vector,
        const REAL_64 scale
        )
    {
        X = vector.X * scale;
        Y = vector.Y * scale;
        Z = vector.Z * scale;
    }

    // ~~

    VOID AddScaledVector(
        const REAL_64_VECTOR_3 & vector,
        const REAL_64 scale
        )
    {
        X += vector.X * scale;
        Y += vector.Y * scale;
        Z += vector.Z * scale;
    }

    // ~~

    VOID SetScaledSumVector(
        const REAL_64 sum_scale,
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector
        )
    {
        X = sum_scale * ( first_vector.X + second_vector.X );
        Y = sum_scale * ( first_vector.Y + second_vector.Y );
        Z = sum_scale * ( first_vector.Z + second_vector.Z );
    }

    // ~~

    VOID AddScaledSumVector(
        const REAL_64 sum_scale,
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector
        )
    {
        X += sum_scale * ( first_vector.X + second_vector.X );
        Y += sum_scale * ( first_vector.Y + second_vector.Y );
        Z += sum_scale * ( first_vector.Z + second_vector.Z );
    }

    // ~~

    VOID SetScaledSumVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector,
        const REAL_64 second_vector_scale
        )
    {
        X = first_vector.X + second_vector.X * second_vector_scale;
        Y = first_vector.Y + second_vector.Y * second_vector_scale;
        Z = first_vector.Z + second_vector.Z * second_vector_scale;
    }

    // ~~

    VOID AddScaledSumVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector,
        const REAL_64 second_vector_scale
        )
    {
        X += first_vector.X + second_vector.X * second_vector_scale;
        Y += first_vector.Y + second_vector.Y * second_vector_scale;
        Z += first_vector.Z + second_vector.Z * second_vector_scale;
    }

    // ~~

    VOID SetScaledSumVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64 first_vector_scale,
        const REAL_64_VECTOR_3 & second_vector,
        const REAL_64 second_vector_scale
        )
    {
        X = first_vector.X * first_vector_scale + second_vector.X * second_vector_scale;
        Y = first_vector.Y * first_vector_scale + second_vector.Y * second_vector_scale;
        Z = first_vector.Z * first_vector_scale + second_vector.Z * second_vector_scale;
    }

    // ~~

    VOID AddScaledSumVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64 first_vector_scale,
        const REAL_64_VECTOR_3 & second_vector,
        const REAL_64 second_vector_scale
        )
    {
        X += first_vector.X * first_vector_scale + second_vector.X * second_vector_scale;
        Y += first_vector.Y * first_vector_scale + second_vector.Y * second_vector_scale;
        Z += first_vector.Z * first_vector_scale + second_vector.Z * second_vector_scale;
    }

    // ~~

    VOID SetScaledSumVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector,
        const REAL_64 second_vector_scale,
        const REAL_64_VECTOR_3 & third_vector,
        const REAL_64 third_vector_scale
        )
    {
        X = first_vector.X + second_vector.X * second_vector_scale + third_vector.X * third_vector_scale;
        Y = first_vector.Y + second_vector.Y * second_vector_scale + third_vector.Y * third_vector_scale;
        Z = first_vector.Z + second_vector.Z * second_vector_scale + third_vector.Z * third_vector_scale;
    }

    // ~~

    VOID AddScaledSumVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector,
        const REAL_64 second_vector_scale,
        const REAL_64_VECTOR_3 & third_vector,
        const REAL_64 third_vector_scale
        )
    {
        X += first_vector.X + second_vector.X * second_vector_scale + third_vector.X * third_vector_scale;
        Y += first_vector.Y + second_vector.Y * second_vector_scale + third_vector.Y * third_vector_scale;
        Z += first_vector.Z + second_vector.Z * second_vector_scale + third_vector.Z * third_vector_scale;
    }

    // ~~

    VOID DivideByComponents(
        const REAL_64 x,
        const REAL_64 y,
        const REAL_64 z
        )
    {
        DEBUG_Check( x != 0.0 );
        DEBUG_Check( y != 0.0 );
        DEBUG_Check( z != 0.0 );

        X /= x;
        Y /= y;
        Z /= z;
    }

    // ~~

    VOID DivideByValue(
        const REAL_64 value
        )
    {
        DEBUG_Check( value != 0.0 );

        X /= value;
        Y /= value;
        Z /= value;
    }

    // ~~

    VOID DivideByVector(
        const REAL_64_VECTOR_3 & vector
        )
    {
        DEBUG_Check( vector.X != 0.0 );
        DEBUG_Check( vector.Y != 0.0 );
        DEBUG_Check( vector.Z != 0.0 );

        X /= vector.X;
        Y /= vector.Y;
        Z /= vector.Z;
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
    }

    // ~~

    VOID SetAverageVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector
        )
    {
        X = ( first_vector.X + second_vector.X ) * 0.5;
        Y = ( first_vector.Y + second_vector.Y );
        Z = ( first_vector.Z + second_vector.Z );
    }

    // ~~

    VOID SetAverageVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector,
        const REAL_64_VECTOR_3 & third_vector
        )
    {
        X = ( first_vector.X + second_vector.X + third_vector.X ) * ( 1.0 / 3.0 );
        Y = ( first_vector.Y + second_vector.Y + third_vector.Y ) * ( 1.0 / 3.0 );
        Z = ( first_vector.Z + second_vector.Z + third_vector.Z ) * ( 1.0 / 3.0 );
    }

    // ~~

    VOID SetAverageVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector,
        const REAL_64_VECTOR_3 & third_vector,
        const REAL_64_VECTOR_3 & fourth_vector
        )
    {
        X = ( first_vector.X + second_vector.X + third_vector.X + fourth_vector.X ) * 0.25;
        Y = ( first_vector.Y + second_vector.Y + third_vector.Y + fourth_vector.Y ) * 0.25;
        Z = ( first_vector.Z + second_vector.Z + third_vector.Z + fourth_vector.Z ) * 0.25;
    }

    // ~~

    VOID AddInterpolatedVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector,
        const REAL_64 second_vector_ratio
        )
    {
        X += ( second_vector.X - first_vector.X ) * second_vector_ratio;
        Y += ( second_vector.Y - first_vector.Y ) * second_vector_ratio;
        Z += ( second_vector.Z - first_vector.Z ) * second_vector_ratio;
    }

    // ~~

    VOID SetInterpolatedVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector,
        const REAL_64 second_vector_ratio
        )
    {
        X = first_vector.X + ( second_vector.X - first_vector.X ) * second_vector_ratio;
        Y = first_vector.Y + ( second_vector.Y - first_vector.Y ) * second_vector_ratio;
        Z = first_vector.Z + ( second_vector.Z - first_vector.Z ) * second_vector_ratio;
    }

    // ~~

    VOID SetInterpolatedVector(
        const REAL_64_VECTOR_3 & lower_left_vector,
        const REAL_64_VECTOR_3 & lower_right_vector,
        const REAL_64_VECTOR_3 & upper_left_vector,
        const REAL_64_VECTOR_3 & upper_right_vector,
        const REAL_64 right_vector_ratio,
        const REAL_64 upper_vector_ratio
        )
    {
        REAL_64_VECTOR_3
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
        const REAL_64_VECTOR_3 & first_axis_vector,
        const REAL_64_VECTOR_3 & second_axis_vector,
        const REAL_64 second_axis_ratio
        )
    {
        REAL_64
            angle_cosinus,
            one_over_angle_sinus,
            first_axis_factor,
            second_axis_factor;
        REAL_64
            angle;

        DEBUG_Check( first_axis_vector.HasRoughlyUnitLength() );
        DEBUG_Check( second_axis_vector.HasRoughlyUnitLength() );

        if ( second_axis_ratio == 0.0 )
        {
            *this = first_axis_vector;
        }
        else if ( second_axis_ratio == 1.0 )
        {
            *this = second_axis_vector;
        }
        else
        {
            angle_cosinus = first_axis_vector.GetAxisDotProduct( second_axis_vector );

            if ( REAL_64_IsRoughlyOne( angle_cosinus ) )
            {
                *this = first_axis_vector;
            }
            else
            {
                NATIVE_KeepInsideInterval( angle_cosinus, -1.0, 1.0 );

                angle = REAL_64_GetArcCosinus( angle_cosinus );
                one_over_angle_sinus = 1.0 / REAL_64_GetSinus( angle );

                first_axis_factor = REAL_64_GetSinus( ( 1.0 - second_axis_ratio ) * angle ) * one_over_angle_sinus;
                second_axis_factor = REAL_64_GetSinus( second_axis_ratio * angle ) * one_over_angle_sinus;

                X = first_axis_vector.X * first_axis_factor + second_axis_vector.X * second_axis_factor;
                Y = first_axis_vector.Y * first_axis_factor + second_axis_vector.Y * second_axis_factor;
                Z = first_axis_vector.Z * first_axis_factor + second_axis_vector.Z * second_axis_factor;

                DEBUG_Check( HasRoughlyUnitLength() );
            }
        }
    }

    // ~~

    VOID SetSphericalAverageVector(
        const REAL_64_VECTOR_3 & first_axis_vector,
        const REAL_64_VECTOR_3 & second_axis_vector
        )
    {
        SetSphericalInterpolationVector( first_axis_vector, second_axis_vector, 0.5 );
    }

    // ~~

    VOID SetSphericalAverageVector(
        const REAL_64_VECTOR_3 & first_axis_vector,
        const REAL_64_VECTOR_3 & second_axis_vector,
        const REAL_64_VECTOR_3 & third_axis_vector
        )
    {
        REAL_64_VECTOR_3
            middle_axis_vector;

        middle_axis_vector.SetSphericalInterpolationVector( first_axis_vector, second_axis_vector, 0.5 );
        SetSphericalInterpolationVector( middle_axis_vector, third_axis_vector, 0.5 );
    }

    // ~~

    VOID SetCrossProductVector(
        const REAL_64_VECTOR_3 & first_vector,
        const REAL_64_VECTOR_3 & second_vector
        )
    {
        X = first_vector.Y * second_vector.Z - first_vector.Z * second_vector.Y;
        Y = first_vector.Z * second_vector.X - first_vector.X * second_vector.Z;
        Z = first_vector.X * second_vector.Y - first_vector.Y * second_vector.X;
    }

    // ~~

    VOID SetAxisCrossProductVector(
        const REAL_64_VECTOR_3 & first_axis_vector,
        const REAL_64_VECTOR_3 & second_axis_vector
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
    const REAL_64_VECTOR_3 & vector
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
