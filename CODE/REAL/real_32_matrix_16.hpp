#pragma once

// == LOCAL

// -- IMPORTS

#include "bool_8.hpp"
#include "debug.hpp"
#include "int_64.hpp"
#include "real_32.hpp"
#include "real_32_vector_3.hpp"
#include "real_32_vector_4.hpp"
#include "streamed_output.hpp"
#include "void.hpp"

// ~~

struct REAL_32_MATRIX_9;
struct REAL_32_MATRIX_12;
struct REAL_32_QUATERNION;

// == GLOBAL

// -- TYPES

struct REAL_32_MATRIX_16
{
    // == PUBLIC

    // -- ATTRIBUTES

    REAL_32_VECTOR_4
        XVector,
        YVector,
        ZVector,
        WVector;

    // -- CONSTRUCTORS

    REAL_32_MATRIX_16(
        ) = default;

    // ~~

    REAL_32_MATRIX_16(
        const REAL_32_VECTOR_4 & x_vector,
        const REAL_32_VECTOR_4 & y_vector,
        const REAL_32_VECTOR_4 & z_vector,
        const REAL_32_VECTOR_4 & w_vector
        ) :
        XVector( x_vector ),
        YVector( y_vector ),
        ZVector( z_vector ),
        WVector( w_vector )
    {
    }

    // -- INQUIRIES

    const BOOL_8 IsIdentity(
        VOID
        ) const
    {
        return
            XVector.X == 1.0f
            && XVector.Y == 0.0f
            && XVector.Z == 0.0f
            && XVector.W == 0.0f
            && YVector.X == 0.0f
            && YVector.Y == 1.0f
            && YVector.Z == 0.0f
            && YVector.W == 0.0f
            && ZVector.X == 0.0f
            && ZVector.Y == 0.0f
            && ZVector.Z == 1.0f
            && ZVector.W == 0.0f
            && WVector.X == 0.0f
            && WVector.Y == 0.0f
            && WVector.Z == 0.0f
            && WVector.W == 1.0f;
    }

    // ~~

    const BOOL_8 IsRoughlyIdentity(
        VOID
        ) const
    {
        return
            REAL_32_IsRoughlyOne( XVector.X )
            && REAL_32_IsRoughlyZero( XVector.Y )
            && REAL_32_IsRoughlyZero( XVector.Z )
            && REAL_32_IsRoughlyZero( XVector.W )
            && REAL_32_IsRoughlyZero( YVector.X )
            && REAL_32_IsRoughlyOne( YVector.Y )
            && REAL_32_IsRoughlyZero( YVector.Z )
            && REAL_32_IsRoughlyZero( YVector.W )
            && REAL_32_IsRoughlyZero( ZVector.X )
            && REAL_32_IsRoughlyZero( ZVector.Y )
            && REAL_32_IsRoughlyOne( ZVector.Z )
            && REAL_32_IsRoughlyZero( ZVector.W )
            && REAL_32_IsRoughlyZero( WVector.X )
            && REAL_32_IsRoughlyZero( WVector.Y )
            && REAL_32_IsRoughlyZero( WVector.Z )
            && REAL_32_IsRoughlyOne( WVector.W );
    }

    // ~~

    const BOOL_8 IsRoughlyEqual(
        const REAL_32_MATRIX_16 & matrix
        ) const
    {
        return
            this == &matrix
            || ( REAL_32_IsRoughlyEqual( XVector.X, matrix.XVector.X )
                 && REAL_32_IsRoughlyEqual( XVector.Y, matrix.XVector.Y )
                 && REAL_32_IsRoughlyEqual( XVector.Z, matrix.XVector.Z )
                 && REAL_32_IsRoughlyEqual( XVector.W, matrix.XVector.W )
                 && REAL_32_IsRoughlyEqual( YVector.X, matrix.YVector.X )
                 && REAL_32_IsRoughlyEqual( YVector.Y, matrix.YVector.Y )
                 && REAL_32_IsRoughlyEqual( YVector.Z, matrix.YVector.Z )
                 && REAL_32_IsRoughlyEqual( YVector.W, matrix.YVector.W )
                 && REAL_32_IsRoughlyEqual( ZVector.X, matrix.ZVector.X )
                 && REAL_32_IsRoughlyEqual( ZVector.Y, matrix.ZVector.Y )
                 && REAL_32_IsRoughlyEqual( ZVector.Z, matrix.ZVector.Z )
                 && REAL_32_IsRoughlyEqual( ZVector.W, matrix.ZVector.W )
                 && REAL_32_IsRoughlyEqual( WVector.X, matrix.WVector.X )
                 && REAL_32_IsRoughlyEqual( WVector.Y, matrix.WVector.Y )
                 && REAL_32_IsRoughlyEqual( WVector.Z, matrix.WVector.Z )
                 && REAL_32_IsRoughlyEqual( WVector.W, matrix.WVector.W )
                 );
    }

    // ~~

    const BOOL_8 HasRotation(
        VOID
        ) const
    {
        return
            XVector.Y != 0
            || XVector.Z != 0
            || YVector.X != 0
            || YVector.Z != 0
            || ZVector.X != 0
            || ZVector.Y != 0;
    }

    // ~~

    const REAL_32_VECTOR_3 & GetXAxisVector(
        VOID
        ) const
    {
        DEBUG_Check( XVector.HasRoughlyUnitLength() );

        return *( const REAL_32_VECTOR_3 * ) &XVector;
    }

    // ~~

    const REAL_32_VECTOR_3 & GetYAxisVector(
        VOID
        ) const
    {
        DEBUG_Check( YVector.HasRoughlyUnitLength() );

        return *( const REAL_32_VECTOR_3 * ) &YVector;
    }

    // ~~

    const REAL_32_VECTOR_3 & GetZAxisVector(
        VOID
        ) const
    {
        DEBUG_Check( ZVector.HasRoughlyUnitLength() );

        return *( const REAL_32_VECTOR_3 * ) &ZVector;
    }

    // ~~

    VOID GetTransformedVector(
        REAL_32_VECTOR_3 & transformed_vector,
        const REAL_32_VECTOR_3 & vector
        ) const
    {
        REAL_32
            one_over_w;

        DEBUG_Check( &transformed_vector != &vector );

        one_over_w = 1.0f / ( vector.X * XVector.W + vector.Y * YVector.W + vector.Z * ZVector.W + WVector.W );

        transformed_vector.X = ( vector.X * XVector.X + vector.Y * YVector.X + vector.Z * ZVector.X + WVector.X ) * one_over_w;
        transformed_vector.Y = ( vector.X * XVector.Y + vector.Y * YVector.Y + vector.Z * ZVector.Y + WVector.Y ) * one_over_w;
        transformed_vector.Z = ( vector.X * XVector.Z + vector.Y * YVector.Z + vector.Z * ZVector.Z + WVector.Z ) * one_over_w;
    }

    // ~~

    VOID GetTransformedOriginVector(
        REAL_32_VECTOR_3 & transformed_origin_vector
        ) const
    {
        REAL_32
            one_over_w_divisor;

        one_over_w_divisor = 1.0f / WVector.W;

        transformed_origin_vector.X = WVector.X * one_over_w_divisor;
        transformed_origin_vector.Y = WVector.Y * one_over_w_divisor;
        transformed_origin_vector.Z = WVector.Z * one_over_w_divisor;
    }

    // -- OPERATIONS

    VOID SetIdentity(
        VOID
        )
    {
        XVector.X = 1.0f;
        XVector.Y = 0.0f;
        XVector.Z = 0.0f;
        XVector.W = 0.0f;

        YVector.X = 0.0f;
        YVector.Y = 1.0f;
        YVector.Z = 0.0f;
        YVector.W = 0.0f;

        ZVector.X = 0.0f;
        ZVector.Y = 0.0f;
        ZVector.Z = 1.0f;
        ZVector.W = 0.0f;

        WVector.X = 0.0f;
        WVector.Y = 0.0f;
        WVector.Z = 0.0f;
        WVector.W = 1.0f;
    }

    // ~~

    VOID SetFromMatrix(
        const REAL_32_MATRIX_9 & matrix
        );

    // ~~

    VOID SetFromMatrix(
        const REAL_32_MATRIX_12 & matrix
        );

    // ~~

    VOID SetFromQuaternion(
        const REAL_32_QUATERNION & quaternion
        );

    // ~~

    VOID SetFromAxes(
        const REAL_32_VECTOR_3 & x_axis_vector,
        const REAL_32_VECTOR_3 & y_axis_vector,
        const REAL_32_VECTOR_3 & z_axis_vector
        )
    {
        XVector.X = x_axis_vector.X;
        XVector.Y = x_axis_vector.Y;
        XVector.Z = x_axis_vector.Z;
        XVector.W = 0.0f;

        YVector.X = y_axis_vector.X;
        YVector.Y = y_axis_vector.Y;
        YVector.Z = y_axis_vector.Z;
        YVector.W = 0.0f;

        ZVector.X = z_axis_vector.X;
        ZVector.Y = z_axis_vector.Y;
        ZVector.Z = z_axis_vector.Z;
        ZVector.W = 0.0f;

        WVector.X = 0.0f;
        WVector.Y = 0.0f;
        WVector.Z = 0.0f;
        WVector.W = 1.0f;
    }

    // ~~

    VOID SetFromZAxisVector(
        const REAL_32_VECTOR_3 & z_axis_vector
        )
    {
        DEBUG_Check( z_axis_vector.HasRoughlyUnitLength() );

        SetIdentity();

        z_axis_vector.GetXyzAxesFromZAxisVector(
            *( REAL_32_VECTOR_3 * ) &XVector,
            *( REAL_32_VECTOR_3 * ) &YVector,
            *( REAL_32_VECTOR_3 * ) &ZVector
            );
    }

    // ~~

    VOID SetFromTranslationVector(
        const REAL_32_VECTOR_3 & translation_vector
        )
    {
        XVector.X = 1.0f;
        XVector.Y = 0.0f;
        XVector.Z = 0.0f;
        XVector.W = 0.0f;

        YVector.X = 0.0f;
        YVector.Y = 1.0f;
        YVector.Z = 0.0f;
        YVector.W = 0.0f;

        ZVector.X = 0.0f;
        ZVector.Y = 0.0f;
        ZVector.Z = 1.0f;
        ZVector.W = 0.0f;

        WVector.X = translation_vector.X;
        WVector.Y = translation_vector.Y;
        WVector.Z = translation_vector.Z;
        WVector.W = 1.0f;
    }

    // ~~

    VOID Translate(
        const REAL_32_VECTOR_3 & translation_vector
        )
    {
        WVector.X += translation_vector.X;
        WVector.Y += translation_vector.Y;
        WVector.Z += translation_vector.Z;
    }

    // ~~

    VOID SetTranslatedMatrix(
        const REAL_32_MATRIX_16 & matrix,
        const REAL_32_VECTOR_3 & translation_vector
        )
    {
        DEBUG_Check( &matrix != this );

        *this = matrix;
        Translate( translation_vector );
    }

    // ~~

    VOID SetFromScaling(
        const REAL_32 scaling
        )
    {
        XVector.X = scaling;
        XVector.Y = 0.0f;
        XVector.Z = 0.0f;
        XVector.W = 0.0f;

        YVector.X = 0.0f;
        YVector.Y = scaling;
        YVector.Z = 0.0f;
        YVector.W = 0.0f;

        ZVector.X = 0.0f;
        ZVector.Y = 0.0f;
        ZVector.Z = scaling;
        ZVector.W = 0.0f;

        WVector.X = 0.0f;
        WVector.Y = 0.0f;
        WVector.Z = 0.0f;
        WVector.W = 1.0f;
    }

    // ~~

    VOID SetFromScaling(
        const REAL_32_VECTOR_3 & scaling_vector
        )
    {
        XVector.X = scaling_vector.X;
        XVector.Y = 0.0f;
        XVector.Z = 0.0f;
        XVector.W = 0.0f;

        YVector.X = 0.0f;
        YVector.Y = scaling_vector.Y;
        YVector.Z = 0.0f;
        YVector.W = 0.0f;

        ZVector.X = 0.0f;
        ZVector.Y = 0.0f;
        ZVector.Z = scaling_vector.Z;
        ZVector.W = 0.0f;

        WVector.X = 0.0f;
        WVector.Y = 0.0f;
        WVector.Z = 0.0f;
        WVector.W = 1.0f;
    }

    // ~~

    VOID SetFromRotationAroundX(
        const REAL_32 x_cosinus,
        const REAL_32 x_sinus
        )
    {
        XVector.X = 1.0f;
        XVector.Y = 0.0f;
        XVector.Z = 0.0f;
        XVector.W = 0.0f;

        YVector.X = 0.0f;
        YVector.Y = x_cosinus;
        YVector.Z = x_sinus;
        YVector.W = 0.0f;

        ZVector.X = 0.0f;
        ZVector.Y = -x_sinus;
        ZVector.Z = x_cosinus;
        ZVector.W = 0.0f;

        WVector.X = 0.0f;
        WVector.Y = 0.0f;
        WVector.Z = 0.0f;
        WVector.W = 1.0f;
    }

    // ~~

    VOID SetFromRotationAroundX(
        const REAL_32 x_angle
        )
    {
        SetFromRotationAroundX(
            REAL_32_GetCosinus( x_angle ),
            REAL_32_GetSinus( x_angle )
            );
    }

    // ~~

    VOID SetFromRotationAroundY(
        const REAL_32 y_cosinus,
        const REAL_32 y_sinus
        )
    {
        XVector.X = y_cosinus;
        XVector.Y = 0.0f;
        XVector.Z = -y_sinus;
        XVector.W = 0.0f;

        YVector.X = 0.0f;
        YVector.Y = 1.0f;
        YVector.Z = 0.0f;
        YVector.W = 0.0f;

        ZVector.X = y_sinus;
        ZVector.Y = 0.0f;
        ZVector.Z = y_cosinus;
        ZVector.W = 0.0f;

        WVector.X = 0.0f;
        WVector.Y = 0.0f;
        WVector.Z = 0.0f;
        WVector.W = 1.0f;
    }

    // ~~

    VOID SetFromRotationAroundY(
        const REAL_32 y_angle
        )
    {
        SetFromRotationAroundY(
            REAL_32_GetCosinus( y_angle ),
            REAL_32_GetSinus( y_angle )
            );
    }

    // ~~

    VOID SetFromRotationAroundZ(
        const REAL_32 z_cosinus,
        const REAL_32 z_sinus
        )
    {
        XVector.X = z_cosinus;
        XVector.Y = z_sinus;
        XVector.Z = 0.0f;
        XVector.W = 0.0f;

        YVector.X = -z_sinus;
        YVector.Y = z_cosinus;
        YVector.Z = 0.0f;
        YVector.W = 0.0f;

        ZVector.X = 0.0f;
        ZVector.Y = 0.0f;
        ZVector.Z = 1.0f;
        ZVector.W = 0.0f;

        WVector.X = 0.0f;
        WVector.Y = 0.0f;
        WVector.Z = 0.0f;
        WVector.W = 1.0f;
    }

    // ~~

    VOID SetFromRotationAroundZ(
        const REAL_32 z_angle
        )
    {
        SetFromRotationAroundZ(
            REAL_32_GetCosinus( z_angle ),
            REAL_32_GetSinus( z_angle )
            );
    }

    // ~~

    VOID SetFromRotationAroundXyz(
        const REAL_32 x_cosinus,
        const REAL_32 x_sinus,
        const REAL_32 y_cosinus,
        const REAL_32 y_sinus,
        const REAL_32 z_cosinus,
        const REAL_32 z_sinus
        )
    {
        XVector.X = y_cosinus * z_cosinus;
        XVector.Y = y_cosinus * z_sinus;
        XVector.Z = -y_sinus;
        XVector.W = 0.0f;

        YVector.X = x_sinus * y_sinus * z_cosinus - x_cosinus * z_sinus;
        YVector.Y = x_sinus * y_sinus * z_sinus + x_cosinus * z_cosinus;
        YVector.Z = x_sinus * y_cosinus;
        YVector.W = 0.0f;

        ZVector.X = x_cosinus * y_sinus * z_cosinus + x_sinus * z_sinus;
        ZVector.Y = x_cosinus * y_sinus * z_sinus - x_sinus * z_cosinus;
        ZVector.Z = x_cosinus * y_cosinus;
        ZVector.W = 0.0f;

        WVector.X = 0.0f;
        WVector.Y = 0.0f;
        WVector.Z = 0.0f;
        WVector.W = 1.0f;
    }

    // ~~

    VOID SetFromRotationAroundXyz(
        const REAL_32 x_angle,
        const REAL_32 y_angle,
        const REAL_32 z_angle
        )
    {
        SetFromRotationAroundXyz(
            REAL_32_GetCosinus( x_angle ),
            REAL_32_GetSinus( x_angle ),
            REAL_32_GetCosinus( y_angle ),
            REAL_32_GetSinus( y_angle ),
            REAL_32_GetCosinus( z_angle ),
            REAL_32_GetSinus( z_angle )
            );
    }

    // ~~

    VOID SetFromRotationAroundXzy(
        const REAL_32 x_cosinus,
        const REAL_32 x_sinus,
        const REAL_32 z_cosinus,
        const REAL_32 z_sinus,
        const REAL_32 y_cosinus,
        const REAL_32 y_sinus
        )
    {
        XVector.X = z_cosinus * y_cosinus;
        XVector.Y = z_sinus;
        XVector.Z = -z_cosinus * y_sinus;
        XVector.W = 0.0f;

        YVector.X = -x_cosinus * z_sinus * y_cosinus + x_sinus * y_sinus;
        YVector.Y = x_cosinus * z_cosinus;
        YVector.Z = x_cosinus * z_sinus * y_sinus + x_sinus * y_cosinus;
        YVector.W = 0.0f;

        ZVector.X = x_sinus * z_sinus * y_cosinus + x_cosinus * y_sinus;
        ZVector.Y = -x_sinus * z_cosinus;
        ZVector.Z = -x_sinus * z_sinus * y_sinus + x_cosinus * y_cosinus;
        ZVector.W = 0.0f;

        WVector.X = 0.0f;
        WVector.Y = 0.0f;
        WVector.Z = 0.0f;
        WVector.W = 1.0f;
    }

    // ~~

    VOID SetFromRotationAroundXzy(
        const REAL_32 x_angle,
        const REAL_32 z_angle,
        const REAL_32 y_angle
        )
    {
        SetFromRotationAroundXzy(
            REAL_32_GetCosinus( x_angle ),
            REAL_32_GetSinus( x_angle ),
            REAL_32_GetCosinus( z_angle ),
            REAL_32_GetSinus( z_angle ),
            REAL_32_GetCosinus( y_angle ),
            REAL_32_GetSinus( y_angle )
            );
    }

    // ~~

    VOID SetFromRotationAroundYxz(
        const REAL_32 y_cosinus,
        const REAL_32 y_sinus,
        const REAL_32 x_cosinus,
        const REAL_32 x_sinus,
        const REAL_32 z_cosinus,
        const REAL_32 z_sinus
        )
    {
        XVector.X = y_cosinus * z_cosinus - y_sinus * x_sinus * z_sinus;
        XVector.Y = y_cosinus * z_sinus + y_sinus * x_sinus * z_cosinus;
        XVector.Z = -y_sinus * x_cosinus;
        XVector.W = 0.0f;

        YVector.X = -x_cosinus * z_sinus;
        YVector.Y = x_cosinus * z_cosinus;
        YVector.Z = x_sinus;
        YVector.W = 0.0f;

        ZVector.X = y_sinus * z_cosinus + y_cosinus * x_sinus * z_sinus;
        ZVector.Y = y_sinus * z_sinus - y_cosinus * x_sinus * z_cosinus;
        ZVector.Z = y_cosinus * x_cosinus;
        ZVector.W = 0.0f;

        WVector.X = 0.0f;
        WVector.Y = 0.0f;
        WVector.Z = 0.0f;
        WVector.W = 1.0f;
    }

    // ~~

    VOID SetFromRotationAroundYxz(
        const REAL_32 y_angle,
        const REAL_32 x_angle,
        const REAL_32 z_angle
        )
    {
        SetFromRotationAroundYxz(
            REAL_32_GetCosinus( y_angle ),
            REAL_32_GetSinus( y_angle ),
            REAL_32_GetCosinus( x_angle ),
            REAL_32_GetSinus( x_angle ),
            REAL_32_GetCosinus( z_angle ),
            REAL_32_GetSinus( z_angle )
            );
    }

    // ~~

    VOID SetFromRotationAroundYzx(
        const REAL_32 y_cosinus,
        const REAL_32 y_sinus,
        const REAL_32 z_cosinus,
        const REAL_32 z_sinus,
        const REAL_32 x_cosinus,
        const REAL_32 x_sinus
        )
    {
        XVector.X = y_cosinus * z_cosinus;
        XVector.Y = y_cosinus * z_sinus * x_cosinus + y_sinus * x_sinus;
        XVector.Z = y_cosinus * z_sinus * x_sinus - y_sinus * x_cosinus;
        XVector.W = 0.0f;

        YVector.X = -z_sinus;
        YVector.Y = z_cosinus * x_cosinus;
        YVector.Z = z_cosinus * x_sinus;
        YVector.W = 0.0f;

        ZVector.X = y_sinus * z_cosinus;
        ZVector.Y = y_sinus * z_sinus * x_cosinus - y_cosinus * x_sinus;
        ZVector.Z = y_sinus * z_sinus * x_sinus + y_cosinus * x_cosinus;
        ZVector.W = 0.0f;

        WVector.X = 0.0f;
        WVector.Y = 0.0f;
        WVector.Z = 0.0f;
        WVector.W = 1.0f;
    }

    // ~~

    VOID SetFromRotationAroundYzx(
        const REAL_32 y_angle,
        const REAL_32 z_angle,
        const REAL_32 x_angle
        )
    {
        SetFromRotationAroundYzx(
            REAL_32_GetCosinus( y_angle ),
            REAL_32_GetSinus( y_angle ),
            REAL_32_GetCosinus( z_angle ),
            REAL_32_GetSinus( z_angle ),
            REAL_32_GetCosinus( x_angle ),
            REAL_32_GetSinus( x_angle )
            );
    }

    // ~~

    VOID SetFromRotationAroundZxy(
        const REAL_32 z_cosinus,
        const REAL_32 z_sinus,
        const REAL_32 x_cosinus,
        const REAL_32 x_sinus,
        const REAL_32 y_cosinus,
        const REAL_32 y_sinus
        )
    {
        XVector.X = z_cosinus * y_cosinus + z_sinus * x_sinus * y_sinus;
        XVector.Y = z_sinus * x_cosinus;
        XVector.Z = -z_cosinus * y_sinus + z_sinus * x_sinus * y_cosinus;
        XVector.W = 0.0f;

        YVector.X = -z_sinus * y_cosinus + z_cosinus * x_sinus * y_sinus;
        YVector.Y = z_cosinus * x_cosinus;
        YVector.Z = z_sinus * y_sinus + z_cosinus * x_sinus * y_cosinus;
        YVector.W = 0.0f;

        ZVector.X = x_cosinus * y_sinus;
        ZVector.Y = -x_sinus;
        ZVector.Z = x_cosinus * y_cosinus;
        ZVector.W = 0.0f;

        WVector.X = 0.0f;
        WVector.Y = 0.0f;
        WVector.Z = 0.0f;
        WVector.W = 1.0f;
    }

    // ~~

    VOID SetFromRotationAroundZxy(
        const REAL_32 z_angle,
        const REAL_32 x_angle,
        const REAL_32 y_angle
        )
    {
        SetFromRotationAroundZxy(
            REAL_32_GetCosinus( z_angle ),
            REAL_32_GetSinus( z_angle ),
            REAL_32_GetCosinus( x_angle ),
            REAL_32_GetSinus( x_angle ),
            REAL_32_GetCosinus( y_angle ),
            REAL_32_GetSinus( y_angle )
            );
    }

    // ~~

    VOID SetFromRotationAroundZyx(
        const REAL_32 z_cosinus,
        const REAL_32 z_sinus,
        const REAL_32 y_cosinus,
        const REAL_32 y_sinus,
        const REAL_32 x_cosinus,
        const REAL_32 x_sinus
        )
    {
        XVector.X = z_cosinus * y_cosinus;
        XVector.Y = z_sinus * x_cosinus + z_cosinus * y_sinus * x_sinus;
        XVector.Z = z_sinus * x_sinus - z_cosinus * y_sinus * x_cosinus;
        XVector.W = 0.0f;

        YVector.X = -z_sinus * y_cosinus;
        YVector.Y = z_cosinus * x_cosinus - z_sinus * y_sinus * x_sinus;
        YVector.Z = z_cosinus * x_sinus + z_sinus * y_sinus * x_cosinus;
        YVector.W = 0.0f;

        ZVector.X = y_sinus;
        ZVector.Y = -y_cosinus * x_sinus;
        ZVector.Z = y_cosinus * x_cosinus;
        ZVector.W = 0.0f;

        WVector.X = 0.0f;
        WVector.Y = 0.0f;
        WVector.Z = 0.0f;
        WVector.W = 1.0f;
    }

    // ~~

    VOID SetFromRotationAroundZyx(
        const REAL_32 z_angle,
        const REAL_32 y_angle,
        const REAL_32 x_angle
        )
    {
        SetFromRotationAroundZyx(
            REAL_32_GetCosinus( z_angle ),
            REAL_32_GetSinus( z_angle ),
            REAL_32_GetCosinus( y_angle ),
            REAL_32_GetSinus( y_angle ),
            REAL_32_GetCosinus( x_angle ),
            REAL_32_GetSinus( x_angle )
            );
    }

    // ~~

    VOID SetFromRotationAroundAxisVector(
        const REAL_32_VECTOR_3 & axis_vector,
        const REAL_32 angle
        )
    {
        REAL_32
            cosinus,
            one_minus_cosinus,
            sinus;

        DEBUG_Check( axis_vector.HasRoughlyUnitLength() );

        cosinus = REAL_32_GetCosinus( angle );
        sinus = REAL_32_GetSinus( angle );
        one_minus_cosinus = 1.0f - cosinus;

        XVector.X = one_minus_cosinus * axis_vector.X * axis_vector.X + cosinus;
        XVector.Y = one_minus_cosinus * axis_vector.X * axis_vector.Y + sinus * axis_vector.Z;
        XVector.Z = one_minus_cosinus * axis_vector.X * axis_vector.Z - sinus * axis_vector.Y;
        XVector.W = 0.0f;

        YVector.X = one_minus_cosinus * axis_vector.Y * axis_vector.X - sinus * axis_vector.Z;
        YVector.Y = one_minus_cosinus * axis_vector.Y * axis_vector.Y + cosinus;
        YVector.Z = one_minus_cosinus * axis_vector.Y * axis_vector.Z + sinus * axis_vector.X;
        YVector.W = 0.0f;

        ZVector.X = one_minus_cosinus * axis_vector.Z * axis_vector.X + sinus * axis_vector.Y;
        ZVector.Y = one_minus_cosinus * axis_vector.Z * axis_vector.Y - sinus * axis_vector.X;
        ZVector.Z = one_minus_cosinus * axis_vector.Z * axis_vector.Z + cosinus;
        ZVector.W = 0.0f;

        WVector.X = 0.0f;
        WVector.Y = 0.0f;
        WVector.Z = 0.0f;
        WVector.W = 1.0f;
    }

    // ~~

    VOID Scale(
        const REAL_32_VECTOR_3 & scaling_vector
        )
    {
        if ( !REAL_32_IsRoughlyOne( scaling_vector.X ) )
        {
            XVector.X *= scaling_vector.X;
            YVector.X *= scaling_vector.X;
            ZVector.X *= scaling_vector.X;
            WVector.X *= scaling_vector.X;
        }

        if ( !REAL_32_IsRoughlyOne( scaling_vector.Y ) )
        {
            XVector.Y *= scaling_vector.Y;
            YVector.Y *= scaling_vector.Y;
            ZVector.Y *= scaling_vector.Y;
            WVector.Y *= scaling_vector.Y;
        }

        if ( !REAL_32_IsRoughlyOne( scaling_vector.Z ) )
        {
            XVector.Z *= scaling_vector.Z;
            YVector.Z *= scaling_vector.Z;
            ZVector.Z *= scaling_vector.Z;
            WVector.Z *= scaling_vector.Z;
        }
    }

    // ~~

    VOID Unscale(
        VOID
        )
    {
        DEBUG_Check( XVector.X != 0.0f );
        DEBUG_Check( YVector.Y != 0.0f );
        DEBUG_Check( ZVector.Z != 0.0f );

        Scale(
            REAL_32_VECTOR_3(
                1.0f / XVector.X,
                1.0f / YVector.Y,
                1.0f / ZVector.Z
                )
            );
    }

    // ~~

    VOID SetColumnVector(
        REAL_32_VECTOR_3 & column_vector,
        const INT_64 column_index
        )
    {
        ( &XVector.X )[ column_index ] = column_vector.X;
        ( &YVector.X )[ column_index ] = column_vector.Y;
        ( &ZVector.X )[ column_index ] = column_vector.Z;
    }

    // ~~

    VOID GetColumnVector(
        REAL_32_VECTOR_3 & column_vector,
        const INT_64 column_index
        ) const
    {
        column_vector.X = ( &XVector.X )[ column_index ];
        column_vector.Y = ( &YVector.X )[ column_index ];
        column_vector.Z = ( &ZVector.X )[ column_index ];
    }

    // ~~

    VOID SetXVector(
        const REAL_32_VECTOR_3 x_vector
        )
    {
        XVector.X = x_vector.X;
        XVector.Y = x_vector.Y;
        XVector.Z = x_vector.Z;
    }

    // ~~

    VOID SetYVector(
        const REAL_32_VECTOR_3 y_vector
        )
    {
        YVector.X = y_vector.X;
        YVector.Y = y_vector.Y;
        YVector.Z = y_vector.Z;
    }

    // ~~

    VOID SetZVector(
        const REAL_32_VECTOR_3 z_vector
        )
    {
        ZVector.X = z_vector.X;
        ZVector.Y = z_vector.Y;
        ZVector.Z = z_vector.Z;
    }

    // ~~

    VOID SetWVector(
        const REAL_32_VECTOR_3 w_vector
        )
    {
        WVector.X = w_vector.X;
        WVector.Y = w_vector.Y;
        WVector.Z = w_vector.Z;
    }

    // ~~

    VOID SetProductMatrix(
        const REAL_32_MATRIX_16 & first_matrix,
        const REAL_32_MATRIX_16 & second_matrix
        )
    {
        if ( this == &first_matrix || this == &second_matrix )
        {
            REAL_32_MATRIX_16
                result_matrix;

            result_matrix.SetProductMatrix( first_matrix, second_matrix );
            *this = result_matrix;
        }
        else
        {
            DEBUG_Check( &first_matrix != this && &second_matrix != this );

            XVector.X = first_matrix.XVector.X * second_matrix.XVector.X + first_matrix.XVector.Y * second_matrix.YVector.X + first_matrix.XVector.Z * second_matrix.ZVector.X + first_matrix.XVector.W * second_matrix.WVector.X;
            XVector.Y = first_matrix.XVector.X * second_matrix.XVector.Y + first_matrix.XVector.Y * second_matrix.YVector.Y + first_matrix.XVector.Z * second_matrix.ZVector.Y + first_matrix.XVector.W * second_matrix.WVector.Y;
            XVector.Z = first_matrix.XVector.X * second_matrix.XVector.Z + first_matrix.XVector.Y * second_matrix.YVector.Z + first_matrix.XVector.Z * second_matrix.ZVector.Z + first_matrix.XVector.W * second_matrix.WVector.Z;
            XVector.W = first_matrix.XVector.X * second_matrix.XVector.W + first_matrix.XVector.Y * second_matrix.YVector.W + first_matrix.XVector.Z * second_matrix.ZVector.W + first_matrix.XVector.W * second_matrix.WVector.W;

            YVector.X = first_matrix.YVector.X * second_matrix.XVector.X + first_matrix.YVector.Y * second_matrix.YVector.X + first_matrix.YVector.Z * second_matrix.ZVector.X + first_matrix.YVector.W * second_matrix.WVector.X;
            YVector.Y = first_matrix.YVector.X * second_matrix.XVector.Y + first_matrix.YVector.Y * second_matrix.YVector.Y + first_matrix.YVector.Z * second_matrix.ZVector.Y + first_matrix.YVector.W * second_matrix.WVector.Y;
            YVector.Z = first_matrix.YVector.X * second_matrix.XVector.Z + first_matrix.YVector.Y * second_matrix.YVector.Z + first_matrix.YVector.Z * second_matrix.ZVector.Z + first_matrix.YVector.W * second_matrix.WVector.Z;
            YVector.W = first_matrix.YVector.X * second_matrix.XVector.W + first_matrix.YVector.Y * second_matrix.YVector.W + first_matrix.YVector.Z * second_matrix.ZVector.W + first_matrix.YVector.W * second_matrix.WVector.W;

            ZVector.X = first_matrix.ZVector.X * second_matrix.XVector.X + first_matrix.ZVector.Y * second_matrix.YVector.X + first_matrix.ZVector.Z * second_matrix.ZVector.X + first_matrix.ZVector.W * second_matrix.WVector.X;
            ZVector.Y = first_matrix.ZVector.X * second_matrix.XVector.Y + first_matrix.ZVector.Y * second_matrix.YVector.Y + first_matrix.ZVector.Z * second_matrix.ZVector.Y + first_matrix.ZVector.W * second_matrix.WVector.Y;
            ZVector.Z = first_matrix.ZVector.X * second_matrix.XVector.Z + first_matrix.ZVector.Y * second_matrix.YVector.Z + first_matrix.ZVector.Z * second_matrix.ZVector.Z + first_matrix.ZVector.W * second_matrix.WVector.Z;
            ZVector.W = first_matrix.ZVector.X * second_matrix.XVector.W + first_matrix.ZVector.Y * second_matrix.YVector.W + first_matrix.ZVector.Z * second_matrix.ZVector.W + first_matrix.ZVector.W * second_matrix.WVector.W;

            WVector.X = first_matrix.WVector.X * second_matrix.XVector.X + first_matrix.WVector.Y * second_matrix.YVector.X + first_matrix.WVector.Z * second_matrix.ZVector.X + first_matrix.WVector.W * second_matrix.WVector.X;
            WVector.Y = first_matrix.WVector.X * second_matrix.XVector.Y + first_matrix.WVector.Y * second_matrix.YVector.Y + first_matrix.WVector.Z * second_matrix.ZVector.Y + first_matrix.WVector.W * second_matrix.WVector.Y;
            WVector.Z = first_matrix.WVector.X * second_matrix.XVector.Z + first_matrix.WVector.Y * second_matrix.YVector.Z + first_matrix.WVector.Z * second_matrix.ZVector.Z + first_matrix.WVector.W * second_matrix.WVector.Z;
            WVector.W = first_matrix.WVector.X * second_matrix.XVector.W + first_matrix.WVector.Y * second_matrix.YVector.W + first_matrix.WVector.Z * second_matrix.ZVector.W + first_matrix.WVector.W * second_matrix.WVector.W;
        }
    }

    // ~~

    VOID PreRotateAroundX(
        const REAL_32 x_angle
        )
    {
        REAL_32_MATRIX_16
            pre_matrix;

        if ( !REAL_32_IsRoughlyZero( x_angle ) )
        {
            pre_matrix.SetFromRotationAroundX( x_angle );
            SetProductMatrix( pre_matrix, *this );
        }
    }

    // ~~

    VOID PostRotateAroundX(
        const REAL_32 x_angle
        )
    {
        REAL_32_MATRIX_16
            post_matrix;

        if ( !REAL_32_IsRoughlyZero( x_angle ) )
        {
            post_matrix.SetFromRotationAroundX( x_angle );
            SetProductMatrix( *this, post_matrix );
        }
    }

    // ~~

    VOID PreRotateAroundY(
        const REAL_32 y_angle
        )
    {
        REAL_32_MATRIX_16
            pre_matrix ;

        if ( !REAL_32_IsRoughlyZero( y_angle ) )
        {
            pre_matrix.SetFromRotationAroundY( y_angle );
            SetProductMatrix( pre_matrix, *this );
        }
    }

    // ~~

    VOID PostRotateAroundY(
        const REAL_32 y_angle
        )
    {
        REAL_32_MATRIX_16
            post_matrix ;

        if ( !REAL_32_IsRoughlyZero( y_angle ) )
        {
            post_matrix.SetFromRotationAroundY( y_angle );
            SetProductMatrix( *this, post_matrix );
        }
    }

    // ~~

    VOID PreRotateAroundZ(
        const REAL_32 z_angle
        )
    {
        REAL_32_MATRIX_16
            pre_matrix ;

        if ( !REAL_32_IsRoughlyZero( z_angle ) )
        {
            pre_matrix.SetFromRotationAroundZ( z_angle );
            SetProductMatrix( pre_matrix, *this );
        }
    }

    // ~~

    VOID PostRotateAroundZ(
        const REAL_32 z_angle
        )
    {
        REAL_32_MATRIX_16
            post_matrix ;

        if ( !REAL_32_IsRoughlyZero( z_angle ) )
        {
            post_matrix.SetFromRotationAroundZ( z_angle );
            SetProductMatrix( *this, post_matrix );
        }
    }

    // ~~

    VOID SetInverseMatrix(
        const REAL_32_MATRIX_16 & matrix
        )
    {
        REAL_32
            x00,
            x01,
            x02,
            x10,
            x11,
            x12,
            x20,
            x21,
            x22,
            x30,
            x31,
            x32,
            y01,
            y02,
            y03,
            y12,
            y13,
            y23,
            z02,
            z03,
            z12,
            z13,
            z22,
            z23,
            z32,
            z33;
        REAL_32
            & x03 = x01,
            & x13 = x11,
            & x23 = x21,
            & x33 = x31,
            & z00 = x02,
            & z10 = x12,
            & z20 = x22,
            & z30 = x32,
            & z01 = x03,
            & z11 = x13,
            & z21 = x23,
            & z31 = x33,
            & det = y01,
            & rcp = y02;

        x00 = matrix.XVector.X;
        x01 = matrix.XVector.Y;
        x10 = matrix.YVector.X;
        x11 = matrix.YVector.Y;
        x20 = matrix.ZVector.X;
        x21 = matrix.ZVector.Y;
        x30 = matrix.WVector.X;
        x31 = matrix.WVector.Y;

        y01 = x00 * x11 - x10 * x01;
        y02 = x00 * x21 - x20 * x01;
        y03 = x00 * x31 - x30 * x01;
        y12 = x10 * x21 - x20 * x11;
        y13 = x10 * x31 - x30 * x11;
        y23 = x20 * x31 - x30 * x21;

        x02 = matrix.XVector.Z;
        x03 = matrix.XVector.W;
        x12 = matrix.YVector.Z;
        x13 = matrix.YVector.W;
        x22 = matrix.ZVector.Z;
        x23 = matrix.ZVector.W;
        x32 = matrix.WVector.Z;
        x33 = matrix.WVector.W;

        z33 = x02 * y12 - x12 * y02 + x22 * y01;
        z23 = x12 * y03 - x32 * y01 - x02 * y13;
        z13 = x02 * y23 - x22 * y03 + x32 * y02;
        z03 = x22 * y13 - x32 * y12 - x12 * y23;
        z32 = x13 * y02 - x23 * y01 - x03 * y12;
        z22 = x03 * y13 - x13 * y03 + x33 * y01;
        z12 = x23 * y03 - x33 * y02 - x03 * y23;
        z02 = x13 * y23 - x23 * y13 + x33 * y12;

        y01 = x02 * x13 - x12 * x03;
        y02 = x02 * x23 - x22 * x03;
        y03 = x02 * x33 - x32 * x03;
        y12 = x12 * x23 - x22 * x13;
        y13 = x12 * x33 - x32 * x13;
        y23 = x22 * x33 - x32 * x23;

        x00 = matrix.XVector.X;
        x01 = matrix.XVector.Y;
        x10 = matrix.YVector.X;
        x11 = matrix.YVector.Y;
        x20 = matrix.ZVector.X;
        x21 = matrix.ZVector.Y;
        x30 = matrix.WVector.X;
        x31 = matrix.WVector.Y;

        z30 = x11 * y02 - x21 * y01 - x01 * y12;
        z20 = x01 * y13 - x11 * y03 + x31 * y01;
        z10 = x21 * y03 - x31 * y02 - x01 * y23;
        z00 = x11 * y23 - x21 * y13 + x31 * y12;
        z31 = x00 * y12 - x10 * y02 + x20 * y01;
        z21 = x10 * y03 - x30 * y01 - x00 * y13;
        z11 = x00 * y23 - x20 * y03 + x30 * y02;
        z01 = x20 * y13 - x30 * y12 - x10 * y23;

        det = x30 * z30 + x20 * z20 + x10 * z10 + x00 * z00;

        rcp = 1.0f / det;

        XVector.X = z00 * rcp;
        XVector.Y = z10 * rcp;
        XVector.Z = z20 * rcp;
        XVector.W = z30 * rcp;
        YVector.X = z01 * rcp;
        YVector.Y = z11 * rcp;
        YVector.Z = z21 * rcp;
        YVector.W = z31 * rcp;
        ZVector.X = z02 * rcp;
        ZVector.Y = z12 * rcp;
        ZVector.Z = z22 * rcp;
        ZVector.W = z32 * rcp;
        WVector.X = z03 * rcp;
        WVector.Y = z13 * rcp;
        WVector.Z = z23 * rcp;
        WVector.W = z33 * rcp;
    }

    // ~~

    VOID Invert(
        VOID
        )
    {
        SetInverseMatrix( *this );
    }
};

// -- OPERATORS

inline STREAMED_OUTPUT & operator<<(
    STREAMED_OUTPUT & output,
    const REAL_32_MATRIX_16 & matrix
    )
{
    output
        << "["
        << matrix.XVector
        << ","
        << matrix.YVector
        << ","
        << matrix.ZVector
        << ","
        << matrix.WVector
        << "]";

    return output;
}
