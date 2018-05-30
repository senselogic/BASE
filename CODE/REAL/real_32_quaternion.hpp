#pragma once

// == LOCAL

// -- IMPORTS

#include "bool_8.hpp"
#include "debug.hpp"
#include "native.hpp"
#include "real_32.hpp"
#include "real_32_matrix_16.hpp"
#include "real_32_matrix_9.hpp"
#include "real_32_vector_3.hpp"
#include "real_64_quaternion.hpp"
#include "streamed_output.hpp"
#include "void.hpp"

// ~~

struct REAL_64_QUATERNION;

// == GLOBAL

// -- TYPES

struct REAL_32_QUATERNION
{
    // == PUBLIC

    // -- ATTRIBUTES

    REAL_32
        X,
        Y,
        Z,
        W;

    // -- CONSTRUCTORS

    REAL_32_QUATERNION(
        ) = default;

    // ~~

    REAL_32_QUATERNION(
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

    // ~~

    const BOOL_8 IsNull(
        VOID
        ) const
    {
        return X == 0.0f && Y == 0.0f && Z == 0.0f && W == 1.0f;
    }

    // ~~

    const BOOL_8 IsEquivalent(
        const REAL_32_QUATERNION & quaternion
        ) const
    {
        return
            ( X == quaternion.X && Y == quaternion.Y && Z == quaternion.Z && W == quaternion.W )
            || ( X == -quaternion.X && Y == -quaternion.Y && Z == -quaternion.Z && W == -quaternion.W );
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
            && REAL_32_IsRoughlyOne( W );
    }

    // ~~

    const BOOL_8 IsRoughlyEqual(
        const REAL_32_QUATERNION & quaternion
        ) const
    {
        return
            REAL_32_IsRoughlyEqual( X, quaternion.X )
            && REAL_32_IsRoughlyEqual( Y, quaternion.Y )
            && REAL_32_IsRoughlyEqual( Z, quaternion.Z )
            && REAL_32_IsRoughlyEqual( W, quaternion.W );
    }

    // ~~

    const BOOL_8 IsRoughlyEquivalent(
        const REAL_32_QUATERNION & quaternion
        ) const
    {
        return
            ( REAL_32_IsRoughlyEqual( X, quaternion.X )
              && REAL_32_IsRoughlyEqual( Y, quaternion.Y )
              && REAL_32_IsRoughlyEqual( Z, quaternion.Z )
              && REAL_32_IsRoughlyEqual( W, quaternion.W ) )
            || ( REAL_32_IsRoughlyEqual( X, -quaternion.X )
                 && REAL_32_IsRoughlyEqual( Y, -quaternion.Y )
                 && REAL_32_IsRoughlyEqual( Z, -quaternion.Z )
                 && REAL_32_IsRoughlyEqual( W, -quaternion.W ) );
    }

    // ~~

    VOID GetAxisVector(
        REAL_32_VECTOR_3 axis_vector
        ) const
    {
        REAL_32
            square_length,
            one_over_length;

        square_length = X * X + Y * Y + Z * Z;

        if ( REAL_32_IsRoughlyZero( square_length ) )
        {
            axis_vector.X = 0.0f;
            axis_vector.Y = 0.0f;
            axis_vector.Z = 0.0f;
        }
        else
        {
            one_over_length = 1.0f / REAL_32_GetSquareRoot( square_length );
            axis_vector.X = X * one_over_length;
            axis_vector.Y = Y * one_over_length;
            axis_vector.Z = Z * one_over_length;
        }
    }

    // ~~

    REAL_32 GetAngle(
        VOID
        ) const
    {
        DEBUG_Check( W >= -1.0f && W <= 1.0f );

        return REAL_32_GetArcCosinus( W ) * 2.0f;
    }

    // ~~

    REAL_32_VECTOR_3 GetXAxisVector(
        VOID
        ) const
    {
        return
            REAL_32_VECTOR_3(
                1.0f - ( Y * Y ) * 2.0f - ( Z * Z ) * 2.0f,
                ( X * Y + W * Z ) * 2.0f,
                ( X * Z - W * Y ) * 2.0f
                );
    }

    // ~~

    REAL_32_VECTOR_3 GetYAxisVector(
        VOID
        ) const
    {
        return
            REAL_32_VECTOR_3(
                ( X * Y - W * Z ) * 2.0f,
                1.0f - ( X * X ) * 2.0f - ( Z * Z ) * 2.0f,
                ( Y * Z + W * X ) * 2.0f
                );
    }

    // ~~

    REAL_32_VECTOR_3 GetZAxisVector(
        VOID
        ) const
    {
        return
            REAL_32_VECTOR_3(
                ( X * Z + W * Y ) * 2.0f,
                ( Y * Z - W * X ) * 2.0f,
                1.0f - ( X * X ) * 2.0f - ( Y * Y ) * 2.0f
                );
    }

    // ~~

    REAL_32_VECTOR_3 GetLeftAxisVector(
        VOID
        ) const
    {
        return GetXAxisVector();
    }

    // ~~

    REAL_32_VECTOR_3 GetRightAxisVector(
        VOID
        ) const
    {
        return GetXAxisVector().GetOppositeVector();
    }

    // ~~

    REAL_32_VECTOR_3 GetUpAxisVector(
        VOID
        ) const
    {
        return GetYAxisVector();
    }

    // ~~

    REAL_32_VECTOR_3 GetDownAxisVector(
        VOID
        ) const
    {
        return GetYAxisVector().GetOppositeVector();
    }

    // ~~

    REAL_32_VECTOR_3 GetForwardAxisVector(
        VOID
        ) const
    {
        return GetZAxisVector();
    }

    // ~~

    REAL_32_VECTOR_3 GetBackwardAxisVector(
        VOID
        ) const
    {
        return GetZAxisVector().GetOppositeVector();
    }

    // ~~

    VOID GetXAxisVector(
        REAL_32_VECTOR_3 & axis_vector
        ) const
    {
        axis_vector.X = ( Y * Y ) * -2.0f + ( Z * Z ) * -2.0f + 1.0f;
        axis_vector.Y = ( X * Y + W * Z ) * 2.0f;
        axis_vector.Z = ( X * Z - W * Y ) * 2.0f;
    }

    // ~~

    VOID GetYAxisVector(
        REAL_32_VECTOR_3 & axis_vector
        ) const
    {
        axis_vector.X = ( X * Y - W * Z ) * 2.0f;
        axis_vector.Y = ( X * X ) * -2.0f + ( Z * Z ) * -2.0f + 1.0f;
        axis_vector.Z = ( Y * Z + W * X ) * 2.0f;
    }

    // ~~

    VOID GetZAxisVector(
        REAL_32_VECTOR_3 & axis_vector
        ) const
    {
        axis_vector.X = ( X * Z + W * Y ) * 2.0f;
        axis_vector.Y = ( Y * Z - W * X ) * 2.0f;
        axis_vector.Z = ( X * X ) * -2.0f + ( Y * Y ) * -2.0f + 1.0f;
    }

    // ~~

    VOID GetLeftAxisVector(
        REAL_32_VECTOR_3 & axis_vector
        ) const
    {
        GetXAxisVector( axis_vector );
    }

    // ~~

    REAL_32_VECTOR_3 GetRightAxisVector(
        REAL_32_VECTOR_3 & axis_vector
        ) const
    {
        GetXAxisVector( axis_vector );

        axis_vector.Negate();
    }

    // ~~

    VOID GetUpAxisVector(
        REAL_32_VECTOR_3 & axis_vector
        ) const
    {
        GetYAxisVector( axis_vector );
    }

    // ~~

    REAL_32_VECTOR_3 GetDownAxisVector(
        REAL_32_VECTOR_3 & axis_vector
        ) const
    {
        GetYAxisVector( axis_vector );

        axis_vector.Negate();
    }

    // ~~

    VOID GetForwardAxisVector(
        REAL_32_VECTOR_3 & axis_vector
        ) const
    {
        GetZAxisVector( axis_vector );
    }

    // ~~

    REAL_32_VECTOR_3 GetBackwardAxisVector(
        REAL_32_VECTOR_3 & axis_vector
        ) const
    {
        GetZAxisVector( axis_vector );

        axis_vector.Negate();
    }

    // ~~

    VOID GetXyzAxes(
        REAL_32_VECTOR_3 & x_axis_vector,
        REAL_32_VECTOR_3 & y_axis_vector,
        REAL_32_VECTOR_3 & z_axis_vector
        ) const
    {
        GetXAxisVector( x_axis_vector );
        GetYAxisVector( y_axis_vector );
        GetZAxisVector( z_axis_vector );
    }

    // ~~

    VOID GetRotatedVector(
        REAL_32_VECTOR_3 & rotated_vector,
        const REAL_32_VECTOR_3 & vector
        ) const
    {
        REAL_32_VECTOR_3
            temporary_vector;

        temporary_vector.X = Y * vector.Z - Z * vector.Y;
        temporary_vector.Y = Z * vector.X - X * vector.Z;
        temporary_vector.Z = X * vector.Y - Y * vector.X;

        rotated_vector.X = vector.X + ( W * temporary_vector.X + Y * temporary_vector.Z - Z * temporary_vector.Y ) * 2.0f;
        rotated_vector.Y = vector.Y + ( W * temporary_vector.Y + Z * temporary_vector.X - X * temporary_vector.Z ) * 2.0f;
        rotated_vector.Z = vector.Z + ( W * temporary_vector.Z + X * temporary_vector.Y - Y * temporary_vector.X ) * 2.0f;
    }

    // ~~

    VOID GetInverseRotatedVector(
        REAL_32_VECTOR_3 & inverse_rotated_vector,
        const REAL_32_VECTOR_3 & vector
        ) const
    {
        REAL_32_QUATERNION
            inverse_quaternion;
        REAL_32_VECTOR_3
            temporary_vector;

        inverse_quaternion.X = -X;
        inverse_quaternion.Y = -Y;
        inverse_quaternion.Z = -Z;
        inverse_quaternion.W = W;

        temporary_vector.X = inverse_quaternion.Y * vector.Z - inverse_quaternion.Z * vector.Y;
        temporary_vector.Y = inverse_quaternion.Z * vector.X - inverse_quaternion.X * vector.Z;
        temporary_vector.Z = inverse_quaternion.X * vector.Y - inverse_quaternion.Y * vector.X;

        inverse_rotated_vector.X = vector.X + ( inverse_quaternion.W * temporary_vector.X + inverse_quaternion.Y * temporary_vector.Z - inverse_quaternion.Z * temporary_vector.Y ) * 2.0f;
        inverse_rotated_vector.Y = vector.Y + ( inverse_quaternion.W * temporary_vector.Y + inverse_quaternion.Z * temporary_vector.X - inverse_quaternion.X * temporary_vector.Z ) * 2.0f;
        inverse_rotated_vector.Z = vector.Z + ( inverse_quaternion.W * temporary_vector.Z + inverse_quaternion.X * temporary_vector.Y - inverse_quaternion.Y * temporary_vector.X ) * 2.0f;
    }

    // ~~

    VOID GetTransformedVector(
        REAL_32_VECTOR_3 & transformed_vector,
        const REAL_32_VECTOR_3 & vector,
        const REAL_32_VECTOR_3 & translation_vector
        ) const
    {
        REAL_32_VECTOR_3
            temporary_vector;

        DEBUG_Check( &transformed_vector != &vector );
        DEBUG_Check( &transformed_vector != &translation_vector );

        temporary_vector.X = Y * vector.Z - Z * vector.Y;
        temporary_vector.Y = Z * vector.X - X * vector.Z;
        temporary_vector.Z = X * vector.Y - Y * vector.X;

        transformed_vector.X = translation_vector.X + vector.X + ( W * temporary_vector.X + Y * temporary_vector.Z - Z * temporary_vector.Y ) * 2.0f;
        transformed_vector.Y = translation_vector.Y + vector.Y + ( W * temporary_vector.Y + Z * temporary_vector.X - X * temporary_vector.Z ) * 2.0f;
        transformed_vector.Z = translation_vector.Z + vector.Z + ( W * temporary_vector.Z + X * temporary_vector.Y - Y * temporary_vector.X ) * 2.0f;
    }

    // ~~

    VOID GetInverseTransformedVector(
        REAL_32_VECTOR_3 & inverse_transformed_vector,
        const REAL_32_VECTOR_3 & vector,
        const REAL_32_VECTOR_3 & translation_vector,
        const REAL_32_QUATERNION & quaternion
        ) const
    {
        REAL_32_QUATERNION
            inverse_quaternion;
        REAL_32_VECTOR_3
            translated_vector,
            temporary_vector;

        translated_vector.X = vector.X - translation_vector.X;
        translated_vector.Y = vector.Y - translation_vector.Y;
        translated_vector.Z = vector.Z - translation_vector.Z;

        inverse_quaternion.X = -X;
        inverse_quaternion.Y = -Y;
        inverse_quaternion.Z = -Z;
        inverse_quaternion.W = W;

        temporary_vector.X = inverse_quaternion.Y * translated_vector.Z - inverse_quaternion.Z * translated_vector.Y;
        temporary_vector.Y = inverse_quaternion.Z * translated_vector.X - inverse_quaternion.X * translated_vector.Z;
        temporary_vector.Z = inverse_quaternion.X * translated_vector.Y - inverse_quaternion.Y * translated_vector.X;

        inverse_transformed_vector.X = translated_vector.X + ( inverse_quaternion.W * temporary_vector.X + inverse_quaternion.Y * temporary_vector.Z - inverse_quaternion.Z * temporary_vector.Y ) * 2.0f;
        inverse_transformed_vector.Y = translated_vector.Y + ( inverse_quaternion.W * temporary_vector.Y + inverse_quaternion.Z * temporary_vector.X - inverse_quaternion.X * temporary_vector.Z ) * 2.0f;
        inverse_transformed_vector.Z = translated_vector.Z + ( inverse_quaternion.W * temporary_vector.Z + inverse_quaternion.X * temporary_vector.Y - inverse_quaternion.Y * temporary_vector.X ) * 2.0f;
    }

    // ~~

    VOID GetXyzAngles(
        REAL_32 & x_angle,
        REAL_32 & y_angle,
        REAL_32 & z_angle
        ) const;

    // ~~

    VOID GetXzyAngles(
        REAL_32 & x_angle,
        REAL_32 & z_angle,
        REAL_32 & y_angle
        ) const;

    // ~~

    VOID GetYxzAngles(
        REAL_32 & y_angle,
        REAL_32 & x_angle,
        REAL_32 & z_angle
        ) const;

    // ~~

    VOID GetYzxAngles(
        REAL_32 & y_angle,
        REAL_32 & z_angle,
        REAL_32 & x_angle
        ) const;

    // ~~

    VOID GetZxyAngles(
        REAL_32 & z_angle,
        REAL_32 & x_angle,
        REAL_32 & y_angle
        ) const;

    // ~~

    VOID GetZyxAngles(
        REAL_32 & z_angle,
        REAL_32 & y_angle,
        REAL_32 & x_angle
        ) const;

    // -- OPERATIONS

    VOID SetIdentity(
        VOID
        )
    {
        X = 0.0f;
        Y = 0.0f;
        Z = 0.0f;
        W = 1.0f;
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

    VOID SetFromQuaternion(
        const REAL_64_QUATERNION & quaternion
        );

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

    // ~~

    VOID Inverse(
        VOID
        )
    {
        X = -X;
        Y = -Y;
        Z = -Z;
    }

    // ~~

    VOID SetInverseQuaternion(
        const REAL_32_QUATERNION & quaternion
        )
    {
        X = -quaternion.X;
        Y = -quaternion.Y;
        Z = -quaternion.Z;
        W = quaternion.W;
    }

    // ~~

    VOID SetInterpolatedQuaternion(
        const REAL_32_QUATERNION & initial_quaternion,
        const REAL_32_QUATERNION & final_quaternion,
        const REAL_32 final_quaternion_ratio
        )
    {
        REAL_32
            angle_cosinus,
            actual_final_quaternion_ratio,
            actual_initial_quaternion_ratio;
        REAL_32_QUATERNION
            actual_final_quaternion;
        REAL_32
            square_length,
            one_over_length;

        DEBUG_Check( initial_quaternion.HasRoughlyUnitLength() );
        DEBUG_Check( final_quaternion.HasRoughlyUnitLength() );
        DEBUG_Check( REAL_32_IsRoughlyInsideInterval( final_quaternion_ratio, 0.0f, 1.0f ) );

        if ( final_quaternion_ratio <= 0.0f )
        {
            *this = initial_quaternion;
        }
        else if ( final_quaternion_ratio >= 1.0f )
        {
            *this = final_quaternion;
        }
        else
        {
            angle_cosinus
                = initial_quaternion.X * final_quaternion.X
                  + initial_quaternion.Y * final_quaternion.Y
                  + initial_quaternion.Z * final_quaternion.Z
                  + initial_quaternion.W * final_quaternion.W;

            if ( angle_cosinus < 0.0f )
            {
                actual_final_quaternion.X = -final_quaternion.X;
                actual_final_quaternion.Y = -final_quaternion.Y;
                actual_final_quaternion.Z = -final_quaternion.Z;
                actual_final_quaternion.W = -final_quaternion.W;

                angle_cosinus
                    = initial_quaternion.X * actual_final_quaternion.X
                      + initial_quaternion.Y * actual_final_quaternion.Y
                      + initial_quaternion.Z * actual_final_quaternion.Z
                      + initial_quaternion.W * actual_final_quaternion.W;

                DEBUG_Check( angle_cosinus >= 0.0f );
            }
            else
            {
                actual_final_quaternion.X = final_quaternion.X;
                actual_final_quaternion.Y = final_quaternion.Y;
                actual_final_quaternion.Z = final_quaternion.Z;
                actual_final_quaternion.W = final_quaternion.W;
            }

            actual_final_quaternion_ratio = final_quaternion_ratio;
            actual_initial_quaternion_ratio = 1.0f - actual_final_quaternion_ratio;

            X = actual_initial_quaternion_ratio * initial_quaternion.X + actual_final_quaternion_ratio * actual_final_quaternion.X;
            Y = actual_initial_quaternion_ratio * initial_quaternion.Y + actual_final_quaternion_ratio * actual_final_quaternion.Y;
            Z = actual_initial_quaternion_ratio * initial_quaternion.Z + actual_final_quaternion_ratio * actual_final_quaternion.Z;
            W = actual_initial_quaternion_ratio * initial_quaternion.W + actual_final_quaternion_ratio * actual_final_quaternion.W;

            Normalize();
        }

        DEBUG_Check( HasRoughlyUnitLength() );
    }

    // ~~

    VOID SetPreciseInterpolatedQuaternion(
        const REAL_32_QUATERNION & initial_quaternion,
        const REAL_32_QUATERNION & final_quaternion,
        const REAL_32 final_quaternion_ratio
        )
    {
        REAL_32
            angle_cosinus,
            actual_final_quaternion_ratio,
            actual_initial_quaternion_ratio,
            initial_quaternion_ratio,
            square_length,
            one_over_length;
        REAL_32_QUATERNION
            actual_final_quaternion;

        DEBUG_Check( initial_quaternion.HasRoughlyUnitLength() );
        DEBUG_Check( final_quaternion.HasRoughlyUnitLength() );
        DEBUG_Check( REAL_32_IsRoughlyInsideInterval( final_quaternion_ratio, 0.0f, 1.0f ) );

        if ( final_quaternion_ratio <= 0.0f )
        {
            *this = initial_quaternion;
        }
        else if ( final_quaternion_ratio >= 1.0f )
        {
            *this = final_quaternion;
        }
        else
        {
            angle_cosinus
                = initial_quaternion.X * final_quaternion.X
                  + initial_quaternion.Y * final_quaternion.Y
                  + initial_quaternion.Z * final_quaternion.Z
                  + initial_quaternion.W * final_quaternion.W;

            if ( angle_cosinus < 0.0f )
            {
                actual_final_quaternion.X = -final_quaternion.X;
                actual_final_quaternion.Y = -final_quaternion.Y;
                actual_final_quaternion.Z = -final_quaternion.Z;
                actual_final_quaternion.W = -final_quaternion.W;

                angle_cosinus
                    = initial_quaternion.X * actual_final_quaternion.X
                      + initial_quaternion.Y * actual_final_quaternion.Y
                      + initial_quaternion.Z * actual_final_quaternion.Z
                      + initial_quaternion.W * actual_final_quaternion.W;

                DEBUG_Check( angle_cosinus >= 0.0f );
            }
            else
            {
                actual_final_quaternion.X = final_quaternion.X;
                actual_final_quaternion.Y = final_quaternion.Y;
                actual_final_quaternion.Z = final_quaternion.Z;
                actual_final_quaternion.W = final_quaternion.W;
            }

            if ( final_quaternion_ratio <= 0.5f )
            {
                REAL_32_SetRoughPartialChordRatio( actual_final_quaternion_ratio, final_quaternion_ratio, angle_cosinus );
                actual_initial_quaternion_ratio = 1.0f - actual_final_quaternion_ratio;
            }
            else
            {
                initial_quaternion_ratio = 1.0f - final_quaternion_ratio;
                REAL_32_SetRoughPartialChordRatio( actual_initial_quaternion_ratio, initial_quaternion_ratio, angle_cosinus );
                actual_final_quaternion_ratio = 1.0f - actual_initial_quaternion_ratio;
            }

            X = actual_initial_quaternion_ratio * initial_quaternion.X + actual_final_quaternion_ratio * actual_final_quaternion.X;
            Y = actual_initial_quaternion_ratio * initial_quaternion.Y + actual_final_quaternion_ratio * actual_final_quaternion.Y;
            Z = actual_initial_quaternion_ratio * initial_quaternion.Z + actual_final_quaternion_ratio * actual_final_quaternion.Z;
            W = actual_initial_quaternion_ratio * initial_quaternion.W + actual_final_quaternion_ratio * actual_final_quaternion.W;

            Normalize();
        }
    }

    // ~~

    VOID SetProductQuaternion(
        const REAL_32_QUATERNION & first_quaternion,
        const REAL_32_QUATERNION & second_quaternion
        )
    {
        DEBUG_Check( &first_quaternion != this );
        DEBUG_Check( &second_quaternion != this );

        // inverse order of matrices : Mx.My.Mz => (Qz.Qy).Qx

        X = first_quaternion.W * second_quaternion.X + first_quaternion.X * second_quaternion.W + first_quaternion.Y * second_quaternion.Z - first_quaternion.Z * second_quaternion.Y;
        Y = first_quaternion.W * second_quaternion.Y - first_quaternion.X * second_quaternion.Z + first_quaternion.Y * second_quaternion.W + first_quaternion.Z * second_quaternion.X;
        Z = first_quaternion.W * second_quaternion.Z + first_quaternion.X * second_quaternion.Y - first_quaternion.Y * second_quaternion.X + first_quaternion.Z * second_quaternion.W;
        W = first_quaternion.W * second_quaternion.W - first_quaternion.X * second_quaternion.X - first_quaternion.Y * second_quaternion.Y - first_quaternion.Z * second_quaternion.Z;

        Normalize();
    }

    // ~~

    VOID PreRotate(
        const REAL_32_QUATERNION & pre_quaternion
        )
    {
        REAL_32
            x,
            y,
            z,
            w;

        DEBUG_Check( pre_quaternion.HasRoughlyUnitLength() );
        DEBUG_Check( HasRoughlyUnitLength() );

        x = W * pre_quaternion.X + X * pre_quaternion.W + Y * pre_quaternion.Z - Z * pre_quaternion.Y;
        y = W * pre_quaternion.Y - X * pre_quaternion.Z + Y * pre_quaternion.W + Z * pre_quaternion.X;
        z = W * pre_quaternion.Z + X * pre_quaternion.Y - Y * pre_quaternion.X + Z * pre_quaternion.W;
        w = W * pre_quaternion.W - X * pre_quaternion.X - Y * pre_quaternion.Y - Z * pre_quaternion.Z;

        X = x;
        Y = y;
        Z = z;
        W = w;

        Normalize();
    }

    // ~~

    VOID PostRotate(
        const REAL_32_QUATERNION & post_quaternion
        )
    {
        REAL_32
            x,
            y,
            z,
            w;

        DEBUG_Check( post_quaternion.HasRoughlyUnitLength() );
        DEBUG_Check( HasRoughlyUnitLength() );

        x = post_quaternion.W * X + post_quaternion.X * W + post_quaternion.Y * Z - post_quaternion.Z * Y;
        y = post_quaternion.W * Y - post_quaternion.X * Z + post_quaternion.Y * W + post_quaternion.Z * X;
        z = post_quaternion.W * Z + post_quaternion.X * Y - post_quaternion.Y * X + post_quaternion.Z * W;
        w = post_quaternion.W * W - post_quaternion.X * X - post_quaternion.Y * Y - post_quaternion.Z * Z;

        X = x;
        Y = y;
        Z = z;
        W = w;

        Normalize();
    }

    // ~~

    VOID SetFromYawPitchRollAngles(
        const REAL_32 yaw_angle,
        const REAL_32 pitch_angle,
        const REAL_32 roll_angle
        )
    {
        REAL_32
            half_yaw_angle,
            half_pitch_angle,
            half_roll_angle;
        REAL_32
            yaw_angle_cosinus,
            yaw_angle_sinus,
            pitch_angle_cosinus,
            pitch_angle_sinus,
            roll_angle_cosinus,
            roll_angle_sinus;

        half_yaw_angle = yaw_angle * 0.5f;
        half_pitch_angle = pitch_angle * 0.5f;
        half_roll_angle = roll_angle * 0.5f;

        yaw_angle_cosinus = REAL_32_GetCosinus( half_yaw_angle );
        yaw_angle_sinus = REAL_32_GetSinus( half_yaw_angle );
        pitch_angle_cosinus = REAL_32_GetCosinus( half_pitch_angle );
        pitch_angle_sinus = REAL_32_GetSinus( half_pitch_angle );
        roll_angle_cosinus = REAL_32_GetCosinus( half_roll_angle );
        roll_angle_sinus = REAL_32_GetSinus( half_roll_angle );

        X = yaw_angle_cosinus * pitch_angle_sinus * roll_angle_cosinus + yaw_angle_sinus * pitch_angle_cosinus * roll_angle_sinus;
        Y = yaw_angle_sinus * pitch_angle_cosinus * roll_angle_cosinus - yaw_angle_cosinus * pitch_angle_sinus * roll_angle_sinus;
        Z = yaw_angle_cosinus * pitch_angle_cosinus * roll_angle_sinus - yaw_angle_sinus * pitch_angle_sinus * roll_angle_cosinus;
        W = yaw_angle_cosinus * pitch_angle_cosinus * roll_angle_cosinus + yaw_angle_sinus * pitch_angle_sinus * roll_angle_sinus;

        Normalize();
    }

    // ~~

    VOID SetFromAxisVectorAndAngle(
        const REAL_32_VECTOR_3 & axis_vector,
        const REAL_32 angle
        )
    {
        REAL_32
            half_angle,
            scale;

        DEBUG_Check( axis_vector.HasRoughlyUnitLength() );

        if ( angle != 0.0f )
        {
            half_angle = angle * 0.5f;
            scale = REAL_32_GetSinus( half_angle );
            X = axis_vector.X * scale;
            Y = axis_vector.Y * scale;
            Z = axis_vector.Z * scale;
            W = REAL_32_GetCosinus( half_angle );
        }
        else
        {
            X = 0.0f;
            Y = 0.0f;
            Z = 0.0f;
            W = 1.0f;
        }

        Normalize();
    }

    // ~~

    VOID SetFromZAxisVector(
        const REAL_32_VECTOR_3 & z_axis_vector
        )
    {
        REAL_32_MATRIX_9
            matrix;

        DEBUG_Check( z_axis_vector.HasRoughlyUnitLength() );

        matrix.SetFromZAxisVector( z_axis_vector );
        SetFromMatrix( matrix );

        DEBUG_Check( GetZAxisVector().IsRoughlyEqual( z_axis_vector ) );
    }

    // ~~

    VOID SetFromAxes(
        const REAL_32_VECTOR_3 & initial_axis_vector,
        const REAL_32_VECTOR_3 & final_axis_vector
        )
    {
        REAL_32_VECTOR_3
            cross_product_vector;
        REAL_32
            dot_product,
            scale,
            one_over_scale;

        DEBUG_Check( initial_axis_vector.HasRoughlyUnitLength() );
        DEBUG_Check( final_axis_vector.HasRoughlyUnitLength() );

        cross_product_vector.SetAxisCrossProductVector( initial_axis_vector, final_axis_vector );
        dot_product = initial_axis_vector.GetAxisDotProduct( final_axis_vector );
        scale = REAL_32_GetSquareRoot( ( dot_product + 1.0f ) * 2.0f );
        one_over_scale = 1.0f / scale;

        X = cross_product_vector.X * one_over_scale;
        Y = cross_product_vector.Y * one_over_scale;
        Z = cross_product_vector.Z * one_over_scale;
        W = scale * 0.5f;

        Normalize();
    }

    // ~~

    VOID SetFromAxes(
        const REAL_32_VECTOR_3 & x_axis_vector,
        const REAL_32_VECTOR_3 & y_axis_vector,
        const REAL_32_VECTOR_3 & z_axis_vector
        )
    {
        REAL_32
            a,
            b,
            c,
            d,
            e,
            one_over_e;

        DEBUG_Check( x_axis_vector.HasRoughlyUnitLength() );
        DEBUG_Check( y_axis_vector.HasRoughlyUnitLength() );
        DEBUG_Check( z_axis_vector.HasRoughlyUnitLength() );

        a = x_axis_vector.X + y_axis_vector.Y + z_axis_vector.Z;
        b = x_axis_vector.X - y_axis_vector.Y - z_axis_vector.Z;
        c = -x_axis_vector.X + y_axis_vector.Y - z_axis_vector.Z;
        d = -x_axis_vector.X - y_axis_vector.Y + z_axis_vector.Z;

        if ( a >= NATIVE_GetMaximum3( b, c, d ) )
        {
            e = REAL_32_GetSquareRoot( a + 1.0f ) * 2.0f;
            one_over_e = 1.0f / e;
            X = ( y_axis_vector.Z - z_axis_vector.Y ) * one_over_e;
            Y = ( z_axis_vector.X - x_axis_vector.Z ) * one_over_e;
            Z = ( x_axis_vector.Y - y_axis_vector.X ) * one_over_e;
            W = e * 0.25f;
        }
        else if ( b >= NATIVE_GetMaximum3( a, c, d ) )
        {
            e = REAL_32_GetSquareRoot( b + 1.0f ) * 2.0f;
            one_over_e = 1.0f / e;
            X = e * 0.25f;
            Y = ( y_axis_vector.X + x_axis_vector.Y ) * one_over_e;
            Z = ( z_axis_vector.X + x_axis_vector.Z ) * one_over_e;
            W = ( y_axis_vector.Z - z_axis_vector.Y ) * one_over_e;
        }
        else if ( c >= NATIVE_GetMaximum3( a, b, d ) )
        {
            e = REAL_32_GetSquareRoot( c + 1.0f ) * 2.0f;
            one_over_e = 1.0f / e;
            X = ( y_axis_vector.X + x_axis_vector.Y ) * one_over_e;
            Y = e * 0.25f;
            Z = ( z_axis_vector.Y + y_axis_vector.Z ) * one_over_e;
            W = ( z_axis_vector.X - x_axis_vector.Z ) * one_over_e;
        }
        else
        {
            e = REAL_32_GetSquareRoot( d + 1.0f ) * 2.0f;
            one_over_e = 1.0f / e;
            X = ( z_axis_vector.X + x_axis_vector.Z ) * one_over_e;
            Y = ( z_axis_vector.Y + y_axis_vector.Z ) * one_over_e;
            Z = e * 0.25f;
            W = ( x_axis_vector.Y - y_axis_vector.X ) * one_over_e;
        }

        Normalize();
    }

    // ~~

    VOID SetFromZPlane(
        const REAL_32_VECTOR_3 & origin_point_vector,
        const REAL_32_VECTOR_3 & x_axis_point_vector,
        const REAL_32_VECTOR_3 & y_axis_point_vector
        )
    {
        REAL_32_VECTOR_3
            x_axis_vector,
            y_axis_vector,
            z_axis_vector;

        x_axis_vector.SetTranslationAxisVector( origin_point_vector, x_axis_point_vector );
        y_axis_vector.SetTranslationAxisVector( origin_point_vector, y_axis_point_vector );
        z_axis_vector.SetAxisCrossProductVector( x_axis_vector, y_axis_vector );
        z_axis_vector.Normalize();
        y_axis_vector.SetAxisCrossProductVector( z_axis_vector, x_axis_vector );

        SetFromAxes( x_axis_vector, y_axis_vector, z_axis_vector );
    }

    // ~~

    VOID SetFromMatrix(
        const REAL_32_MATRIX_16 & matrix
        )
    {
        SetFromAxes(
            *( REAL_32_VECTOR_3 * ) &matrix.XVector,
            *( REAL_32_VECTOR_3 * ) &matrix.YVector,
            *( REAL_32_VECTOR_3 * ) &matrix.ZVector
            );
    }

    // ~~

    VOID SetFromMatrix(
        const REAL_32_MATRIX_9 & matrix
        )
    {
        SetFromAxes(
            *( REAL_32_VECTOR_3 * ) &matrix.XVector,
            *( REAL_32_VECTOR_3 * ) &matrix.YVector,
            *( REAL_32_VECTOR_3 * ) &matrix.ZVector
            );
    }

    // ~~

    VOID SetFromRotationAroundX(
        const REAL_32 x_angle
        )
    {
        REAL_32
            half_x_angle;

        if ( x_angle == 0.0f )
        {
            X = 0.0f;
            Y = 0.0f;
            Z = 0.0f;
            W = 1.0f;
        }
        else
        {
            half_x_angle = x_angle * 0.5f;
            X = REAL_32_GetSinus( half_x_angle );
            Y = 0.0f;
            Z = 0.0f;
            W = REAL_32_GetCosinus( half_x_angle );

            Normalize();
        }
    }

    // ~~

    VOID SetFromRotationAroundY(
        const REAL_32 y_angle
        )
    {
        REAL_32
            half_y_angle;

        if ( y_angle == 0.0f )
        {
            X = 0.0f;
            Y = 0.0f;
            Z = 0.0f;
            W = 1.0f;
        }
        else
        {
            half_y_angle = y_angle * 0.5f;
            X = 0.0f;
            Y = REAL_32_GetSinus( half_y_angle );
            Z = 0.0f;
            W = REAL_32_GetCosinus( half_y_angle );

            Normalize();
        }
    }

    // ~~

    VOID SetFromRotationAroundZ(
        const REAL_32 z_angle
        )
    {
        REAL_32
            half_z_angle;

        if ( z_angle == 0.0f )
        {
            X = 0.0f;
            Y = 0.0f;
            Z = 0.0f;
            W = 1.0f;
        }
        else
        {
            half_z_angle = z_angle * 0.5f;
            X = 0.0f;
            Y = 0.0f;
            Z = REAL_32_GetSinus( half_z_angle );
            W = REAL_32_GetCosinus( half_z_angle );

            Normalize();
        }
    }

    // ~~

    VOID SetFromRotationAroundXyz(
        const REAL_32 half_x_cosinus,
        const REAL_32 half_x_sinus,
        const REAL_32 half_y_cosinus,
        const REAL_32 half_y_sinus,
        const REAL_32 half_z_cosinus,
        const REAL_32 half_z_sinus
        )
    {
        // Mx.My.Mz => (Qz.Qy).Qx

        X = half_z_cosinus * half_y_cosinus * half_x_sinus - half_z_sinus * half_y_sinus * half_x_cosinus;
        Y = half_z_cosinus * half_y_sinus * half_x_cosinus + half_z_sinus * half_y_cosinus * half_x_sinus;
        Z = -half_z_cosinus * half_y_sinus * half_x_sinus + half_z_sinus * half_y_cosinus * half_x_cosinus;
        W = half_z_cosinus * half_y_cosinus * half_x_cosinus + half_z_sinus * half_y_sinus * half_x_sinus;

        Normalize();
    }

    // ~~

    VOID SetFromRotationAroundXyz(
        const REAL_32 x_angle,
        const REAL_32 y_angle,
        const REAL_32 z_angle
        )
    {
        REAL_32
            half_x_angle,
            half_y_angle,
            half_z_angle;

        half_x_angle = x_angle * 0.5f;
        half_y_angle = y_angle * 0.5f;
        half_z_angle = z_angle * 0.5f;

        SetFromRotationAroundXyz(
            REAL_32_GetCosinus( half_x_angle ),
            REAL_32_GetSinus( half_x_angle ),
            REAL_32_GetCosinus( half_y_angle ),
            REAL_32_GetSinus( half_y_angle ),
            REAL_32_GetCosinus( half_z_angle ),
            REAL_32_GetSinus( half_z_angle )
            );
    }

    // ~~

    VOID SetFromRotationAroundXzy(
        const REAL_32 half_x_cosinus,
        const REAL_32 half_x_sinus,
        const REAL_32 half_z_cosinus,
        const REAL_32 half_z_sinus,
        const REAL_32 half_y_cosinus,
        const REAL_32 half_y_sinus
        )
    {
        // Mx.Mz.My => (Qy.Qz).Qx

        X = half_y_cosinus * half_z_cosinus * half_x_sinus + half_y_sinus * half_z_sinus * half_x_cosinus;
        Y = half_y_sinus * half_z_cosinus * half_x_cosinus + half_y_cosinus * half_z_sinus * half_x_sinus;
        Z = -half_y_sinus * half_z_cosinus * half_x_sinus + half_y_cosinus * half_z_sinus * half_x_cosinus;
        W = half_y_cosinus * half_z_cosinus * half_x_cosinus - half_y_sinus * half_z_sinus * half_x_sinus;

        Normalize();
    }

    // ~~

    VOID SetFromRotationAroundXzy(
        const REAL_32 x_angle,
        const REAL_32 z_angle,
        const REAL_32 y_angle
        )
    {
        REAL_32
            half_x_angle,
            half_y_angle,
            half_z_angle;

        half_x_angle = x_angle * 0.5f;
        half_z_angle = z_angle * 0.5f;
        half_y_angle = y_angle * 0.5f;

        SetFromRotationAroundXzy(
            REAL_32_GetCosinus( half_x_angle ),
            REAL_32_GetSinus( half_x_angle ),
            REAL_32_GetCosinus( half_z_angle ),
            REAL_32_GetSinus( half_z_angle ),
            REAL_32_GetCosinus( half_y_angle ),
            REAL_32_GetSinus( half_y_angle )
            );
    }

    // ~~

    VOID SetFromRotationAroundYxz(
        const REAL_32 half_y_cosinus,
        const REAL_32 half_y_sinus,
        const REAL_32 half_x_cosinus,
        const REAL_32 half_x_sinus,
        const REAL_32 half_z_cosinus,
        const REAL_32 half_z_sinus
        )
    {
        // My.Mx.Mz => (Qz.Qx).Qy

        X = half_z_cosinus * half_x_sinus * half_y_cosinus - half_z_sinus * half_x_cosinus * half_y_sinus;
        Y = half_z_cosinus * half_x_cosinus * half_y_sinus + half_z_sinus * half_x_sinus * half_y_cosinus;
        Z = half_z_cosinus * half_x_sinus * half_y_sinus + half_z_sinus * half_x_cosinus * half_y_cosinus;
        W = half_z_cosinus * half_x_cosinus * half_y_cosinus - half_z_sinus * half_x_sinus * half_y_sinus;

        Normalize();
    }

    // ~~

    VOID SetFromRotationAroundYxz(
        const REAL_32 y_angle,
        const REAL_32 x_angle,
        const REAL_32 z_angle
        )
    {
        REAL_32
            half_x_angle,
            half_y_angle,
            half_z_angle;

        half_y_angle = y_angle * 0.5f;
        half_x_angle = x_angle * 0.5f;
        half_z_angle = z_angle * 0.5f;

        SetFromRotationAroundYxz(
            REAL_32_GetCosinus( half_y_angle ),
            REAL_32_GetSinus( half_y_angle ),
            REAL_32_GetCosinus( half_x_angle ),
            REAL_32_GetSinus( half_x_angle ),
            REAL_32_GetCosinus( half_z_angle ),
            REAL_32_GetSinus( half_z_angle )
            );
    }

    // ~~

    VOID SetFromRotationAroundYzx(
        const REAL_32 half_y_cosinus,
        const REAL_32 half_y_sinus,
        const REAL_32 half_z_cosinus,
        const REAL_32 half_z_sinus,
        const REAL_32 half_x_cosinus,
        const REAL_32 half_x_sinus
        )
    {
        // My.Mz.Mx => (Qx.Qz).Qy

        X = half_x_sinus * half_z_cosinus * half_y_cosinus - half_x_cosinus * half_z_sinus * half_y_sinus;
        Y = half_x_cosinus * half_z_cosinus * half_y_sinus - half_x_sinus * half_z_sinus * half_y_cosinus;
        Z = half_x_sinus * half_z_cosinus * half_y_sinus + half_x_cosinus * half_z_sinus * half_y_cosinus;
        W = half_x_cosinus * half_z_cosinus * half_y_cosinus + half_x_sinus * half_z_sinus * half_y_sinus;

        Normalize();
    }

    // ~~

    VOID SetFromRotationAroundYzx(
        const REAL_32 y_angle,
        const REAL_32 z_angle,
        const REAL_32 x_angle
        )
    {
        REAL_32
            half_x_angle,
            half_y_angle,
            half_z_angle;

        half_y_angle = y_angle * 0.5f;
        half_z_angle = z_angle * 0.5f;
        half_x_angle = x_angle * 0.5f;

        SetFromRotationAroundYzx(
            REAL_32_GetCosinus( half_y_angle ),
            REAL_32_GetSinus( half_y_angle ),
            REAL_32_GetCosinus( half_z_angle ),
            REAL_32_GetSinus( half_z_angle ),
            REAL_32_GetCosinus( half_x_angle ),
            REAL_32_GetSinus( half_x_angle )
            );
    }

    // ~~

    VOID SetFromRotationAroundZxy(
        const REAL_32 half_z_cosinus,
        const REAL_32 half_z_sinus,
        const REAL_32 half_x_cosinus,
        const REAL_32 half_x_sinus,
        const REAL_32 half_y_cosinus,
        const REAL_32 half_y_sinus
        )
    {
        // Mz.Mx.My => (Qy.Qx).Qz

        X = half_y_cosinus * half_x_sinus * half_z_cosinus + half_y_sinus * half_x_cosinus * half_z_sinus;
        Y = -half_y_cosinus * half_x_sinus * half_z_sinus + half_y_sinus * half_x_cosinus * half_z_cosinus;
        Z = half_y_cosinus * half_x_cosinus * half_z_sinus - half_y_sinus * half_x_sinus * half_z_cosinus;
        W = half_y_cosinus * half_x_cosinus * half_z_cosinus + half_y_sinus * half_x_sinus * half_z_sinus;

        Normalize();
    }

    // ~~

    VOID SetFromRotationAroundZxy(
        const REAL_32 z_angle,
        const REAL_32 x_angle,
        const REAL_32 y_angle
        )
    {
        REAL_32
            half_x_angle,
            half_y_angle,
            half_z_angle;

        half_z_angle = z_angle * 0.5f;
        half_x_angle = x_angle * 0.5f;
        half_y_angle = y_angle * 0.5f;

        SetFromRotationAroundZxy(
            REAL_32_GetCosinus( half_z_angle ),
            REAL_32_GetSinus( half_z_angle ),
            REAL_32_GetCosinus( half_x_angle ),
            REAL_32_GetSinus( half_x_angle ),
            REAL_32_GetCosinus( half_y_angle ),
            REAL_32_GetSinus( half_y_angle )
            );
    }

    // ~~

    VOID SetFromRotationAroundZyx(
        const REAL_32 half_z_cosinus,
        const REAL_32 half_z_sinus,
        const REAL_32 half_y_cosinus,
        const REAL_32 half_y_sinus,
        const REAL_32 half_x_cosinus,
        const REAL_32 half_x_sinus
        )
    {
        // Mz.My.Mx = (Qx.Qy).Qz

        X = half_x_sinus * half_y_cosinus * half_z_cosinus + half_x_cosinus * half_y_sinus * half_z_sinus;
        Y = -half_x_sinus * half_y_cosinus * half_z_sinus + half_x_cosinus * half_y_sinus * half_z_cosinus;
        Z = half_x_cosinus * half_y_cosinus * half_z_sinus + half_x_sinus * half_y_sinus * half_z_cosinus;
        W = half_x_cosinus * half_y_cosinus * half_z_cosinus - half_x_sinus * half_y_sinus * half_z_sinus;

        Normalize();
    }

    // ~~

    VOID SetFromRotationAroundZyx(
        const REAL_32 z_angle,
        const REAL_32 y_angle,
        const REAL_32 x_angle
        )
    {
        REAL_32
            half_x_angle,
            half_y_angle,
            half_z_angle;

        half_z_angle = z_angle * 0.5f;
        half_y_angle = y_angle * 0.5f;
        half_x_angle = x_angle * 0.5f;

        SetFromRotationAroundZyx(
            REAL_32_GetCosinus( half_z_angle ),
            REAL_32_GetSinus( half_z_angle ),
            REAL_32_GetCosinus( half_y_angle ),
            REAL_32_GetSinus( half_y_angle ),
            REAL_32_GetCosinus( half_x_angle ),
            REAL_32_GetSinus( half_x_angle )
            );
    }

    // ~~
    /*
        VOID SetFromRotationAroundXyz(
            const REAL_32 x_angle,
            const REAL_32 y_angle,
            const REAL_32 z_angle
            )
        {
            REAL_32_QUATERNION
                x_rotation_quaternion,
                y_rotation_quaternion,
                z_rotation_quaternion,
                zy_rotation_quaternion;

            x_rotation_quaternion.SetFromRotationAroundX( x_angle );
            y_rotation_quaternion.SetFromRotationAroundY( y_angle );
            z_rotation_quaternion.SetFromRotationAroundZ( z_angle );
            zy_rotation_quaternion.SetProduct( z_rotation_quaternion, y_rotation_quaternion );
            SetProduct( zy_rotation_quaternion, x_rotation_quaternion );
        }

        // ~~

        VOID SetFromRotationAroundXzy(
            const REAL_32 x_angle,
            const REAL_32 z_angle,
            const REAL_32 y_angle
            )
        {
            REAL_32_QUATERNION
                x_rotation_quaternion,
                y_rotation_quaternion,
                yz_rotation_quaternion,
                z_rotation_quaternion;

            x_rotation_quaternion.SetFromRotationAroundX( x_angle );
            z_rotation_quaternion.SetFromRotationAroundZ( z_angle );
            y_rotation_quaternion.SetFromRotationAroundY( y_angle );
            yz_rotation_quaternion.SetProduct( y_rotation_quaternion, z_rotation_quaternion );
            SetProduct( yz_rotation_quaternion, x_rotation_quaternion );
        }

        // ~~

        VOID SetFromRotationAroundYxz(
            const REAL_32 y_angle,
            const REAL_32 x_angle,
            const REAL_32 z_angle
            )
        {
            REAL_32_QUATERNION
                x_rotation_quaternion,
                y_rotation_quaternion,
                z_rotation_quaternion,
                zx_rotation_quaternion;

            y_rotation_quaternion.SetFromRotationAroundY( y_angle );
            x_rotation_quaternion.SetFromRotationAroundX( x_angle );
            z_rotation_quaternion.SetFromRotationAroundZ( z_angle );
            zx_rotation_quaternion.SetProduct( z_rotation_quaternion, x_rotation_quaternion );
            SetProduct( zx_rotation_quaternion, y_rotation_quaternion );
        }

        // ~~

        VOID SetFromRotationAroundYzx(
            const REAL_32 y_angle,
            const REAL_32 z_angle,
            const REAL_32 x_angle
            )
        {
            REAL_32_QUATERNION
                x_rotation_quaternion,
                xz_rotation_quaternion,
                y_rotation_quaternion,
                z_rotation_quaternion;

            y_rotation_quaternion.SetFromRotationAroundY( y_angle );
            z_rotation_quaternion.SetFromRotationAroundZ( z_angle );
            x_rotation_quaternion.SetFromRotationAroundX( x_angle );
            xz_rotation_quaternion.SetProduct( x_rotation_quaternion, z_rotation_quaternion );
            SetProduct( xz_rotation_quaternion, y_rotation_quaternion );
        }

        // ~~

        VOID SetFromRotationAroundZxy(
            const REAL_32 z_angle,
            const REAL_32 x_angle,
            const REAL_32 y_angle
            )
        {
            REAL_32_QUATERNION
                x_rotation_quaternion,
                y_rotation_quaternion,
                yx_rotation_quaternion,
                z_rotation_quaternion;

            z_rotation_quaternion.SetFromRotationAroundZ( z_angle );
            x_rotation_quaternion.SetFromRotationAroundX( x_angle );
            y_rotation_quaternion.SetFromRotationAroundY( y_angle );
            yx_rotation_quaternion.SetProduct( y_rotation_quaternion, x_rotation_quaternion );
            SetProduct( yx_rotation_quaternion, z_rotation_quaternion );
        }

        // ~~

        VOID SetFromRotationAroundZyx(
            const REAL_32 z_angle,
            const REAL_32 y_angle,
            const REAL_32 x_angle
            )
        {
            REAL_32_QUATERNION
                x_rotation_quaternion,
                xy_rotation_quaternion,
                y_rotation_quaternion,
                z_rotation_quaternion;

            z_rotation_quaternion.SetFromRotationAroundZ( z_angle );
            y_rotation_quaternion.SetFromRotationAroundY( y_angle );
            x_rotation_quaternion.SetFromRotationAroundX( x_angle );
            xy_rotation_quaternion.SetProduct( x_rotation_quaternion, y_rotation_quaternion );
            SetProduct( xy_rotation_quaternion, z_rotation_quaternion );
        }
    */
    // ~~

    VOID SetPreRotatedQuaternion(
        const REAL_32_QUATERNION & quaternion,
        const REAL_32_QUATERNION & pre_quaternion
        )
    {
        *this = quaternion;
        PreRotate( pre_quaternion );
    }

    // ~~

    VOID SetPostRotatedQuaternion(
        const REAL_32_QUATERNION & quaternion,
        const REAL_32_QUATERNION & post_quaternion
        )
    {
        *this = quaternion;
        PostRotate( post_quaternion );
    }

    // ~~

    VOID SetInversePreRotatedQuaternion(
        const REAL_32_QUATERNION & quaternion,
        const REAL_32_QUATERNION & rotation_quaternion
        )
    {
        REAL_32_QUATERNION
            inverse_rotation;

        inverse_rotation.SetInverseQuaternion( rotation_quaternion );
        SetProductQuaternion( inverse_rotation, quaternion );
    }

    // ~~

    VOID SetPreRotatedQuaternionAroundX(
        const REAL_32_QUATERNION & quaternion,
        const REAL_32 x_angle
        )
    {
        REAL_32_QUATERNION
            pre_quaternion;

        *this = quaternion;

        if ( x_angle != 0.0f )
        {
            pre_quaternion.SetFromRotationAroundX( x_angle );
            PreRotate( pre_quaternion );
        }
    }

    // ~~

    VOID SetPostRotatedQuaternionAroundX(
        const REAL_32_QUATERNION & quaternion,
        const REAL_32 x_angle
        )
    {
        REAL_32_QUATERNION
            post_quaternion;

        *this = quaternion;

        if ( x_angle != 0.0f )
        {
            post_quaternion.SetFromRotationAroundX( x_angle );
            PostRotate( post_quaternion );
        }
    }

    // ~~

    VOID SetPreRotatedQuaternionAroundY(
        const REAL_32_QUATERNION & quaternion,
        const REAL_32 y_angle
        )
    {
        REAL_32_QUATERNION
            pre_quaternion;

        *this = quaternion;

        if ( y_angle != 0.0f )
        {
            pre_quaternion.SetFromRotationAroundY( y_angle );
            PreRotate( pre_quaternion );
        }
    }

    // ~~

    VOID SetPostRotatedQuaternionAroundY(
        const REAL_32_QUATERNION & quaternion,
        const REAL_32 y_angle
        )
    {
        REAL_32_QUATERNION
            post_quaternion;

        *this = quaternion;

        if ( y_angle != 0.0f )
        {
            post_quaternion.SetFromRotationAroundY( y_angle );
            PostRotate( post_quaternion );
        }
    }

    // ~~

    VOID SetPreRotatedQuaternionAroundZ(
        const REAL_32_QUATERNION & quaternion,
        const REAL_32 z_angle
        )
    {
        REAL_32_QUATERNION
            pre_quaternion;

        *this = quaternion;

        if ( z_angle != 0.0f )
        {
            pre_quaternion.SetFromRotationAroundZ( z_angle );
            PreRotate( pre_quaternion );
        }
    }

    // ~~

    VOID SetPostRotatedQuaternionAroundZ(
        const REAL_32_QUATERNION & quaternion,
        const REAL_32 z_angle
        )
    {
        REAL_32_QUATERNION
            post_quaternion;

        *this = quaternion;

        if ( z_angle != 0.0f )
        {
            post_quaternion.SetFromRotationAroundZ( z_angle );
            PostRotate( post_quaternion );
        }
    }

    // ~~

    VOID PreRotateAroundX(
        const REAL_32 x_angle
        )
    {
        REAL_32_QUATERNION
            pre_quaternion;

        if ( x_angle != 0.0f )
        {
            pre_quaternion.SetFromRotationAroundX( x_angle );
            PreRotate( pre_quaternion );
        }
    }

    // ~~

    VOID PostRotateAroundX(
        const REAL_32 x_angle
        )
    {
        REAL_32_QUATERNION
            post_quaternion;

        if ( x_angle != 0.0f )
        {
            post_quaternion.SetFromRotationAroundX( x_angle );
            PostRotate( post_quaternion );
        }
    }

    // ~~

    VOID PreRotateAroundY(
        const REAL_32 y_angle
        )
    {
        REAL_32_QUATERNION
            pre_quaternion;

        if ( y_angle != 0.0f )
        {
            pre_quaternion.SetFromRotationAroundY( y_angle );
            PreRotate( pre_quaternion );
        }
    }

    // ~~

    VOID PostRotateAroundY(
        const REAL_32 y_angle
        )
    {
        REAL_32_QUATERNION
            post_quaternion;

        if ( y_angle != 0.0f )
        {
            post_quaternion.SetFromRotationAroundY( y_angle );
            PostRotate( post_quaternion );
        }
    }

    // ~~

    VOID PreRotateAroundZ(
        const REAL_32 z_angle
        )
    {
        REAL_32_QUATERNION
            pre_quaternion;

        if ( z_angle != 0.0f )
        {
            pre_quaternion.SetFromRotationAroundZ( z_angle );
            PreRotate( pre_quaternion );
        }
    }

    // ~~

    VOID PostRotateAroundZ(
        const REAL_32 z_angle
        )
    {
        REAL_32_QUATERNION
            post_quaternion;

        if ( z_angle != 0.0f )
        {
            post_quaternion.SetFromRotationAroundZ( z_angle );
            PostRotate( post_quaternion );
        }
    }
};

// -- OPERATORS

inline STREAMED_OUTPUT & operator<<(
    STREAMED_OUTPUT & output,
    const REAL_32_QUATERNION & quaternion
    )
{
    output
        << "["
        << quaternion.X
        << ","
        << quaternion.Y
        << ","
        << quaternion.Z
        << ","
        << quaternion.W
        << "]";

    return output;
}
