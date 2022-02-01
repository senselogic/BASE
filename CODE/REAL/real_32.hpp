#pragma once

// == LOCAL

// -- IMPORTS

#include "bool_8.hpp"
#include "debug.hpp"
#include "native.hpp"
#include "streamed.hpp"

// ~~

#include <math.h>

// == GLOBAL

// -- TYPES

typedef float
    REAL_32;

// -- CONSTANTS

#define REAL_32_SmallestReal    1.175494351e-38f
#define REAL_32_MinimumReal    -3.402823466e+38f
#define REAL_32_MaximumReal    3.402823466e+38f
#define REAL_32_SignBitIndex    31
#define REAL_32_ExponentBitCount    8
#define REAL_32_ExponentMask    255
#define REAL_32_ExponentNull    127
#define REAL_32_MinimumDecimalExponent    -37
#define REAL_32_MaximumDecimalExponent    38
#define REAL_32_MinimumBinaryExponent    -125
#define REAL_32_MaximumBinaryExponent    128
#define REAL_32_MantissaBitCount    24
#define REAL_32_MantissaLeftShiftCount    23
#define REAL_32_SignificantDigitCount    6
#define REAL_32_Precision    0.00001f
#define REAL_32_SquareRootOfTwo    1.4142135623730950488016887242097f
#define REAL_32_SquareRootOfThree    1.7320508075688772935274463415059f
#define REAL_32_OneOverSquareRootOfTwo    0.70710678118654752440084436210485f
#define REAL_32_OneOverSquareRootOfThree    0.57735026918962576450914878050196f
#define REAL_32_Pi    3.1415926535897932384626433832795f
#define REAL_32_HalfPi    1.5707963267948966192313216916398f
#define REAL_32_TwoPi    6.283185307179586476925286766559f
#define REAL_32_OneOverPi    0.3183098861837906715377675267450f
#define REAL_32_OneOverTwoPi    0.15915494309189533576888376337251f
#define REAL_32_Microsecond    0.000001f
#define REAL_32_Millisecond    0.001f
#define REAL_32_Centisecond    0.01f
#define REAL_32_Second    1.0f
#define REAL_32_Minute    60.0f
#define REAL_32_Hour    3600.0f
#define REAL_32_Day    86400.0f
#define REAL_32_OneOverMicrosecond    1000000.0f
#define REAL_32_OneOverMillisecond    1000.0f
#define REAL_32_OneOverCentisecond    100.0f
#define REAL_32_OneOverSecond    1.0f
#define REAL_32_OneOverMinute    ( 1.0f / 60.0f )
#define REAL_32_OneOverHour    ( 1.0f / 3600.0f )
#define REAL_32_OneOverDay    ( 1.0f / 86400.0f )
#define REAL_32_Degree    ( REAL_32_Pi / 180.0f )
#define REAL_32_5Degrees    ( REAL_32_Pi / 36.0f )
#define REAL_32_10Degrees    ( REAL_32_Pi / 18.0f )
#define REAL_32_30Degrees    ( REAL_32_Pi / 6.0f )
#define REAL_32_45Degrees    ( REAL_32_Pi / 4.0f )
#define REAL_32_60Degrees    ( REAL_32_Pi / 3.0f )
#define REAL_32_90Degrees    ( REAL_32_Pi / 2.0f )
#define REAL_32_180Degrees    REAL_32_Pi
#define REAL_32_270Degrees    ( REAL_32_Pi * 1.5f )
#define REAL_32_360Degrees    ( REAL_32_Pi * 2.0f )

// -- FUNCTIONS

// ease(x) = 3 * x^2 - 2 * x^3
// sin(x) = x - (1/6) * x^3 + (1/120) * x^5 - (1/5040) * x^7 + (1/362880) * x^9
// cos(x) = 1 - (1/2) * x^2 + (1/24) * x^4 - (1/720) * x^6 + (1/40320) * x^8
// tan(x) = x + (1/3) * x^3 + (2/15) * x^5 - (17/315) * x^7 + (62/2835) * x^9
// asin(x) = x + (1/6) * x^3 + (3/40) * x^5 + (5/112) * x^7 + (35/1152) * x^9
// acos(x) = (1/2) * PI - x - (1/6) * x^3 - (3/40) * x^5 - (5/112) * x^7 - (35/1152) * x^9
// atan(x) = x - (1/3) * x^3 + (1/5) * x^5 - (1/7) * x^7 + (1/9) * x^9
// sinh(x) = x + (1/6) * x^3 + (1/120) * x^5 + (1/5040) * x^7 + (1/362880) * x^9
// cosh(x) = 1 + (1/2) * x^2 + (1/24) * x^4 + (1/720) * x^6 + (1/40320) * x^8
// tanh(x) = x - (1/3) * x^3 + (2/15) * x^5 - (17/315) * x^7 + (62/2835) * x^9
// chord(x,a) = 2 * k * x^2 - 3 * k * x + k + 1, where k = 0.5069269f * (1 - 0.7878088f * cos(a))^2

// ~~

#define REAL_32_GetPositive( _real_ ) \
    \
    fabsf( _real_ )

// ~~

#define REAL_32_GetModulo( _dividend_, _divisor_ ) \
    \
    fmodf( _dividend_, _divisor_ )

// ~~

#define REAL_32_GetFloor( _real_ ) \
    \
    floorf( _real_ )

// ~~

#define REAL_32_GetCeil( _real_ ) \
    \
    ceilf( _real_ )

// ~~

#define REAL_32_GetSquareRoot( _real_ ) \
    \
    sqrtf( _real_ )

// ~~

#define REAL_32_GetPower( _base_, _exponent_ ) \
    \
    powf( _base_, _exponent_ )

// ~~

#define REAL_32_GetNeperianPower( _real_ ) \
    \
    expf( _real_ )

// ~~

#define REAL_32_GetNeperianLogarithm( _real_ ) \
    \
    logf( _real_ )

// ~~

#define REAL_32_GetDecimalLogarithm( _real_ ) \
    \
    log10f( _real_ )

// ~~

#define REAL_32_GetCosinus( _angle_ ) \
    \
    cosf( _angle_ )

// ~~

#define REAL_32_GetSinus( _angle_ ) \
    \
    sinf( _angle_ )

// ~~

#define REAL_32_GetTangent( _angle_ ) \
    \
    tanf( _angle_ )

// ~~

#define REAL_32_GetArcCosinus( _cosinus_ ) \
    \
    acosf( _cosinus_ )

// ~~

#define REAL_32_GetArcSinus( _sinus_ ) \
    \
    asinf( _sinus_ )

// ~~

#define REAL_32_GetArcTangent( _tangent_ ) \
    \
    atanf( _tangent_ )

// ~~

#define REAL_32_GetArcTangent2( _sinus_, _cosinus_ ) \
    \
    atan2f( _sinus_, _cosinus_ )

// ~~

#define REAL_32_IsAlmostZero( _real_, _precision_ ) \
    \
    ( ( _real_ ) >= -( _precision_ ) \
      && ( _real_ ) <= ( _precision_ ) )

// ~~

#define REAL_32_IsAlmostOne( _real_, _precision_ ) \
    \
    ( ( _real_ ) >= 1.0f - ( _precision_ ) \
      && ( _real_ ) <= 1.0f + ( _precision_ ) )

// ~~

#define REAL_32_IsAlmostEqual( _real_, _other_real_, _precision_ ) \
    \
    ( ( _real_ ) >= ( _other_real_ ) - ( _precision_ ) \
      && ( _real_ ) <= ( _other_real_ ) + ( _precision_ ) )

// ~~

#define REAL_32_IsAlmostInsideInterval( _real_, _minimum_real_, _maximum_real_, _precision_ ) \
    \
    ( ( _real_ ) >= ( _minimum_real_ ) - ( _precision_ ) \
      && ( _real_ ) <= ( _maximum_real_ ) + ( _precision_ ) )

// ~~

#define REAL_32_IsRoughlyZero( _real_ ) \
    \
    ( ( _real_ ) >= -REAL_32_Precision \
      && ( _real_ ) <= REAL_32_Precision )

// ~~

#define REAL_32_IsRoughlyOne( _real_ ) \
    \
    ( ( _real_ ) >= 1.0f - REAL_32_Precision \
      && ( _real_ ) <= 1.0f + REAL_32_Precision )

// ~~

#define REAL_32_IsRoughlyMinusOne( _real_ ) \
    \
    ( ( _real_ ) >= -1.0f - REAL_32_Precision \
      && ( _real_ ) <= -1.0f + REAL_32_Precision )

// ~~

#define REAL_32_IsRoughlyEqual( _real_, _other_real_ ) \
    \
    ( ( _real_ ) >= ( _other_real_ ) - REAL_32_Precision \
      && ( _real_ ) <= ( _other_real_ ) + REAL_32_Precision )

// ~~

#define REAL_32_IsRoughlyInsideInterval( _real_, _minimum_real_, _maximum_real_ ) \
    \
    ( ( _real_ ) >= ( _minimum_real_ ) - REAL_32_Precision \
      && ( _real_ ) <= ( _maximum_real_ ) + REAL_32_Precision )

// ~~

#define REAL_32_SetRoughSinus( _sinus_, _angle_ ) \
    \
    { \
        _sinus_ = _angle_ * _angle_; \
        _sinus_ = _angle_ + _sinus_ * ( ( -1.0f / 6.0f ) * _angle_ + _sinus_ * ( ( 1.0f / 120.0f ) * _angle_ + _sinus_ *( ( -1.0f / 5040.0f ) * _angle_ + _sinus_ * ( 1.0f / 362880.0f ) * _angle_ ) ) ); \
    }

// ~~

#define REAL_32_SetRoughCosinus( _cosinus_, _angle_ ) \
    \
    { \
        _cosinus_ = _angle_ * _angle_; \
        _cosinus_ = 1.0f + _cosinus_ * ( ( -1.0f / 2.0f ) + _cosinus_ * ( ( 1.0f / 24.0f ) + _cosinus_ * ( ( -1.0f / 720.0f ) + _cosinus_ * ( 1.0f / 40320.0f ) ) ) ); \
    }

// ~~

#define REAL_32_SetRoughPartialChordRatio( _partial_chord_ratio_, _angle_ratio_, _angle_cosinus_ ) \
    \
    { \
        DEBUG_Check( ( _angle_ratio_ ) >= 0.0f && ( _angle_ratio_ ) <= 0.5f ); \
        _partial_chord_ratio_ = 1.0f - 0.82279687f * ( _angle_cosinus_ ); \
        _partial_chord_ratio_ *= 0.58549219f * ( _partial_chord_ratio_ ); \
        _partial_chord_ratio_ += ( _partial_chord_ratio_ ) * ( _angle_ratio_ ) * ( 2.0f * ( _angle_ratio_ ) - 3.0f ) + 1.0f; \
        _partial_chord_ratio_ *= _angle_ratio_; \
    }

// ~~

#define REAL_32_SetRoughChordRatio( _chord_ratio_, _angle_ratio_, _angle_cosinus_ ) \
    \
    { \
        REAL_32 \
            angle_ratio_complement; \
        \
        if ( ( _angle_ratio_ ) <= 0.5f ) \
        { \
            REAL_SetRoughPartialChordRatioFast( _chord_ratio_, _angle_ratio_, _angle_cosinus_ ) \
        } \
        else \
        { \
            angle_ratio_complement = 1.0f - _angle_ratio_; \
            REAL_SetRoughPartialChordRatioFast( _chord_ratio_, angle_ratio_complement, _angle_cosinus_ ) \
            _chord_ratio_ = 1.0f - ( _chord_ratio_ ); \
        } \
    }

// ~~

#define REAL_32_SetRoughInverseSquareRoot( _rough_inverse_square_root_, _square_ ) \
    \
    { \
        DEBUG_Check( ( _square_ ) > 0.005f && ( _square_ ) < 1.1f ); \
        \
        _rough_inverse_square_root_ = 1.021798f - 0.5325156f * ( ( _square_ ) - 0.959066f ); \
        _rough_inverse_square_root_ *= 1.021798f - 0.5325156f * ( ( _rough_inverse_square_root_ ) * ( _rough_inverse_square_root_ ) * ( _square_ ) - 0.959066f ); \
        \
        if ( ( _square_ ) <= 0.91521198f ) \
        { \
            _rough_inverse_square_root_ *= 1.021798f - 0.5325156f * ( ( _rough_inverse_square_root_ ) * ( _rough_inverse_square_root_ ) * ( _square_ ) - 0.959066f ); \
            \
            if ( ( _square_ ) <= 0.65211970f ) \
            { \
                _rough_inverse_square_root_ *= 1.021798f - 0.5325156f * ( ( _rough_inverse_square_root_ ) * ( _rough_inverse_square_root_ ) * ( _square_ ) - 0.959066f ); \
                \
                if ( ( _square_ ) <= 0.53f ) \
                { \
                    _rough_inverse_square_root_ *= 1.021798f - 0.5325156f * ( ( _rough_inverse_square_root_ ) * ( _rough_inverse_square_root_ ) * ( _square_ ) - 0.959066f ); \
                    _rough_inverse_square_root_ *= 1.021798f - 0.5325156f * ( ( _rough_inverse_square_root_ ) * ( _rough_inverse_square_root_ ) * ( _square_ ) - 0.959066f ); \
                    _rough_inverse_square_root_ *= 1.021798f - 0.5325156f * ( ( _rough_inverse_square_root_ ) * ( _rough_inverse_square_root_ ) * ( _square_ ) - 0.959066f ); \
                } \
            } \
        } \
    }
// ~~

#define REAL_32_SetInterpolatedReal( _interpolated_real_, _initial_real_, _final_real_, _final_real_ratio_ ) \
    \
    { \
        _interpolated_real_ = _final_real_; \
        _interpolated_real_ -= _initial_real_; \
        _interpolated_real_ *= _final_real_ratio_; \
        _interpolated_real_ += _initial_real_; \
    }

// ~~

#define REAL_32_GetInterpolatedReal( _initial_real_, _final_real_, _final_real_ratio_ ) \
    \
    ( ( _initial_real_ ) + ( ( _final_real_ ) - ( _initial_real_ ) ) * ( _final_real_ratio_ ) )

// ~~

#define REAL_32_DumpAngle( _angle_ ) \
    \
    STREAMED_Output << #_angle_ << " = " << ( ( _angle_ ) / REAL_32_Degree ) << "\n"

// ~~

inline const REAL_32 REAL_32_GetAxisVectorAngle(
    REAL_32 cosinus,
    REAL_32 sinus
    )
{
}

// ~~

inline const REAL_32 REAL_32_GetVectorAngle(
    const REAL_32 x,
    const REAL_32 y
    )
{
    REAL_32
        angle,
        cosinus,
        length,
        one_over_length,
        sinus;

    length = REAL_32_GetSquareRoot( x * x + y * y );

    if ( REAL_32_IsRoughlyZero( length ) )
    {
        return 0.0f;
    }
    else
    {
        one_over_length = 1.0f / length;

        cosinus = x * one_over_length;
        sinus = y * one_over_length;

        if ( REAL_32_IsRoughlyOne( cosinus ) )
        {
            return 0.0f;
        }
        else if ( REAL_32_IsRoughlyOne( sinus ) )
        {
            return REAL_32_90Degrees;
        }
        else if ( REAL_32_IsRoughlyMinusOne( sinus ) )
        {
            return -REAL_32_90Degrees;
        }
        else if ( REAL_32_IsRoughlyMinusOne( cosinus ) )
        {
            if ( sinus >= 0.0f )
            {
                return REAL_32_180Degrees;
            }
            else
            {
                return -REAL_32_180Degrees;
            }
        }
        else
        {
            if ( REAL_32_IsRoughlyZero( sinus ) )
            {
                NATIVE_KeepInsideInterval( cosinus, -1.0f, 1.0f );

                angle = REAL_32_GetArcCosinus( REAL_32_GetPositive( cosinus ) );
            }
            else
            {
                NATIVE_KeepInsideInterval( sinus, -1.0f, 1.0f );

                angle = REAL_32_GetArcSinus( REAL_32_GetPositive( sinus ) );
            }

            if ( cosinus >= 0.0f )
            {
                if ( sinus < 0.0f )
                {
                    angle = -angle ;
                }
            }
            else
            {
                if ( sinus >= 0.0f )
                {
                    angle = REAL_32_Pi - angle;
                }
                else
                {
                    angle = -REAL_32_Pi + angle;
                }
            }

            DEBUG_Check( REAL_32_IsRoughlyEqual( REAL_32_GetCosinus( angle ), cosinus ) );
            DEBUG_Check( REAL_32_IsRoughlyEqual( REAL_32_GetSinus( angle ), sinus ) );

            return angle;
        }
    }
}

// ~~

inline const REAL_32 REAL_32_GetClosestAngle(
    const REAL_32 angle,
    const REAL_32 other_angle
    )
{
    REAL_32
        closest_angle;

    closest_angle = angle;

    if ( closest_angle - other_angle > REAL_32_180Degrees
         || other_angle - closest_angle > REAL_32_180Degrees )
    {
        while ( closest_angle < other_angle )
        {
            closest_angle += REAL_32_360Degrees;
        }

        while ( closest_angle - other_angle > REAL_32_180Degrees )
        {
            closest_angle -= REAL_32_360Degrees;
        }
    }

    DEBUG_Check(
        REAL_32_GetPositive( closest_angle - other_angle ) <= REAL_32_180Degrees
        );

    return closest_angle;
}

// ~~

inline const BOOL_8 REAL_32_IsRoughlyEquivalentAngle(
    const REAL_32 angle,
    const REAL_32 other_angle
    )
{
    REAL_32
        angle_difference;

    angle_difference = REAL_32_GetPositive( angle - other_angle );

    while ( angle_difference >= REAL_32_360Degrees - REAL_32_Precision )
    {
        angle_difference -= REAL_32_360Degrees;
    }

    return REAL_32_IsRoughlyZero( angle_difference );
}
