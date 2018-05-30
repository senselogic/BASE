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

typedef double
    REAL_64;

// -- CONSTANTS

#define REAL_64_SmallestReal    2.2250738585072014e-308    // ( 4.94065645841246544e-324 )
#define REAL_64_MinimumReal    -1.7976931348623158e+308
#define REAL_64_MaximumReal    1.7976931348623158e+308
#define REAL_64_SignBitIndex    63
#define REAL_64_ExponentBitCount    11
#define REAL_64_ExponentMask    2047
#define REAL_64_ExponentNull    1023
#define REAL_64_MinimumDecimalExponent    -307
#define REAL_64_MaximumDecimalExponent    308
#define REAL_64_MinimumBinaryExponent    -1021
#define REAL_64_MaximumBinaryExponent    1024
#define REAL_64_MantissaBitCount    53
#define REAL_64_MantissaLeftShiftCount    52
#define REAL_64_SignificantDigitCount    15
#define REAL_64_Precision    0.000001
#define REAL_64_SquareRootOfTwo    1.4142135623730950488016887242097
#define REAL_64_SquareRootOfThree    1.7320508075688772935274463415059
#define REAL_64_OneOverSquareRootOfTwo    0.70710678118654752440084436210485
#define REAL_64_OneOverSquareRootOfThree    0.57735026918962576450914878050196
#define REAL_64_Pi    3.1415926535897932384626433832795
#define REAL_64_HalfPi    1.5707963267948966192313216916398
#define REAL_64_TwoPi    6.283185307179586476925286766559
#define REAL_64_OneOverPi    0.3183098861837906715377675267450
#define REAL_64_OneOverTwoPi    0.15915494309189533576888376337251
#define REAL_64_Microsecond    0.000001
#define REAL_64_Millisecond    0.001
#define REAL_64_Centisecond    0.01
#define REAL_64_Second    1.0
#define REAL_64_Minute    60.0
#define REAL_64_Hour    3600.0
#define REAL_64_Day    86400.0
#define REAL_64_OneOverMicrosecond    1000000.0
#define REAL_64_OneOverMillisecond    1000.0
#define REAL_64_OneOverCentisecond    100.0
#define REAL_64_OneOverSecond    1.0
#define REAL_64_OneOverMinute    ( 1.0 / 60.0 )
#define REAL_64_OneOverHour    ( 1.0 / 3600.0 )
#define REAL_64_OneOverDay    ( 1.0 / 86400.0 )
#define REAL_64_Degree    ( REAL_64_Pi / 180.0 )
#define REAL_64_5Degrees    ( REAL_64_Pi / 36.0 )
#define REAL_64_10Degrees    ( REAL_64_Pi / 18.0 )
#define REAL_64_30Degrees    ( REAL_64_Pi / 6.0 )
#define REAL_64_45Degrees    ( REAL_64_Pi / 4.0 )
#define REAL_64_60Degrees    ( REAL_64_Pi / 3.0 )
#define REAL_64_90Degrees    ( REAL_64_Pi / 2.0 )
#define REAL_64_180Degrees    REAL_64_Pi
#define REAL_64_270Degrees    ( REAL_64_Pi * 1.5 )
#define REAL_64_360Degrees    ( REAL_64_Pi * 2.0 )

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
// chord(x,a) = 2 * k * x^2 - 3 * k * x + k + 1, where k = 0.5069269 * (1 - 0.7878088 * cos(a))^2

// ~~

#define REAL_64_GetPositive( _real_ ) \
    \
    fabs( _real_ )

// ~~

#define REAL_64_GetModulo( _dividend_, _divisor_ ) \
    \
    fmod( _dividend_, _divisor_ )

// ~~

#define REAL_64_GetFloor( _real_ ) \
    \
    floor( _real_ )

// ~~

#define REAL_64_GetCeil( _real_ ) \
    \
    ceil( _real_ )

// ~~

#define REAL_64_GetSquareRoot( _real_ ) \
    \
    sqrt( _real_ )

// ~~

#define REAL_64_GetPower( _base_, _exponent_ ) \
    \
    pow( _base_, _exponent_ )

// ~~

#define REAL_64_GetNeperianPower( _real_ ) \
    \
    exp( _real_ )

// ~~

#define REAL_64_GetNeperianLogarithm( _real_ ) \
    \
    log( _real_ )

// ~~

#define REAL_64_GetDecimalLogarithm( _real_ ) \
    \
    log10( _real_ )

// ~~

#define REAL_64_GetCosinus( _angle_ ) \
    \
    cos( _angle_ )

// ~~

#define REAL_64_GetSinus( _angle_ ) \
    \
    sin( _angle_ )

// ~~

#define REAL_64_GetTangent( _angle_ ) \
    \
    tan( _angle_ )

// ~~

#define REAL_64_GetArcCosinus( _cosinus_ ) \
    \
    acos( _cosinus_ )

// ~~

#define REAL_64_GetArcSinus( _sinus_ ) \
    \
    asin( _sinus_ )

// ~~

#define REAL_64_GetArcTangent( _tangent_ ) \
    \
    atan( _tangent_ )

// ~~

#define REAL_64_GetArcTangent2( _sinus_, _cosinus_ ) \
    \
    atan2( _sinus_, _cosinus_ )

// ~~

#define REAL_64_IsAlmostZero( _real_, _precision_ ) \
    \
    ( ( _real_ ) >= -( _precision_ ) \
      && ( _real_ ) <= ( _precision_ ) )

// ~~

#define REAL_64_IsAlmostOne( _real_, _precision_ ) \
    \
    ( ( _real_ ) >= 1.0 - ( _precision_ ) \
      && ( _real_ ) <= 1.0 + ( _precision_ ) )

// ~~

#define REAL_64_IsAlmostEqual( _real_, _other_real_, _precision_ ) \
    \
    ( ( _real_ ) >= ( _other_real_ ) - ( _precision_ ) \
      && ( _real_ ) <= ( _other_real_ ) + ( _precision_ ) )

// ~~

#define REAL_64_IsAlmostInsideInterval( _real_, _minimum_real_, _maximum_real_, _precision_ ) \
    \
    ( ( _real_ ) >= ( _minimum_real_ ) - ( _precision_ ) \
      && ( _real_ ) <= ( _maximum_real_ ) + ( _precision_ ) )

// ~~

#define REAL_64_IsRoughlyZero( _real_ ) \
    \
    ( ( _real_ ) >= -REAL_64_Precision \
      && ( _real_ ) <= REAL_64_Precision )

// ~~

#define REAL_64_IsRoughlyOne( _real_ ) \
    \
    ( ( _real_ ) >= 1.0 - REAL_64_Precision \
      && ( _real_ ) <= 1.0 + REAL_64_Precision )

// ~~

#define REAL_64_IsRoughlyMinusOne( _real_ ) \
    \
    ( ( _real_ ) >= -1.0 - REAL_64_Precision \
      && ( _real_ ) <= -1.0 + REAL_64_Precision )

// ~~

#define REAL_64_IsRoughlyEqual( _real_, _other_real_ ) \
    \
    ( ( _real_ ) >= ( _other_real_ ) - REAL_64_Precision \
      && ( _real_ ) <= ( _other_real_ ) + REAL_64_Precision )

// ~~

#define REAL_64_IsRoughlyInsideInterval( _real_, _minimum_real_, _maximum_real_ ) \
    \
    ( ( _real_ ) >= ( _minimum_real_ ) - REAL_64_Precision \
      && ( _real_ ) <= ( _maximum_real_ ) + REAL_64_Precision )

// ~~

#define REAL_64_SetRoughSinus( _sinus_, _angle_ ) \
    \
    { \
        _sinus_ = _angle_ * _angle_; \
        _sinus_ = _angle_ + _sinus_ * ( ( -1.0 / 6.0 ) * _angle_ + _sinus_ * ( ( 1.0 / 120.0 ) * _angle_ + _sinus_ *( ( -1.0 / 5040.0 ) * _angle_ + _sinus_ * ( 1.0 / 362880.0 ) * _angle_ ) ) ); \
    }

// ~~

#define REAL_64_SetRoughCosinus( _cosinus_, _angle_ ) \
    \
    { \
        _cosinus_ = _angle_ * _angle_; \
        _cosinus_ = 1.0 + _cosinus_ * ( ( -1.0 / 2.0 ) + _cosinus_ * ( ( 1.0 / 24.0 ) + _cosinus_ * ( ( -1.0 / 720.0 ) + _cosinus_ * ( 1.0 / 40320.0 ) ) ) ); \
    }

// ~~

#define REAL_64_SetRoughPartialChordRatio( _partial_chord_ratio_, _angle_ratio_, _angle_cosinus_ ) \
    \
    { \
        DEBUG_Check( ( _angle_ratio_ ) >= 0.0 && ( _angle_ratio_ ) <= 0.5 ); \
        _partial_chord_ratio_ = 1.0f - 0.82279687 * ( _angle_cosinus_ ); \
        _partial_chord_ratio_ *= 0.58549219 * ( _partial_chord_ratio_ ); \
        _partial_chord_ratio_ += ( _partial_chord_ratio_ ) * ( _angle_ratio_ ) * ( 2.0 * ( _angle_ratio_ ) - 3.0 ) + 1.0; \
        _partial_chord_ratio_ *= _angle_ratio_; \
    }

// ~~

#define REAL_64_SetRoughChordRatio( _chord_ratio_, _angle_ratio_, _angle_cosinus_ ) \
    \
    { \
        REAL_64 \
            angle_ratio_complement; \
        \
        if ( ( _angle_ratio_ ) <= 0.5 ) \
        { \
            REAL_SetRoughPartialChordRatioFast( _chord_ratio_, _angle_ratio_, _angle_cosinus_ ) \
        } \
        else \
        { \
            angle_ratio_complement = 1.0 - _angle_ratio_; \
            REAL_SetRoughPartialChordRatioFast( _chord_ratio_, angle_ratio_complement, _angle_cosinus_ ) \
            _chord_ratio_ = 1.0 - ( _chord_ratio_ ); \
        } \
    }

// ~~

#define REAL_64_SetRoughInverseSquareRoot( _rough_inverse_square_root_, _square_ ) \
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

#define REAL_64_SetInterpolatedReal( _interpolated_real_, _initial_real_, _final_real_, _final_real_ratio_ ) \
    \
    { \
        _interpolated_real_ = _final_real_; \
        _interpolated_real_ -= _initial_real_; \
        _interpolated_real_ *= _final_real_ratio_; \
        _interpolated_real_ += _initial_real_; \
    }

// ~~

#define REAL_64_GetInterpolatedReal( _initial_real_, _final_real_, _final_real_ratio_ ) \
    \
    ( ( _initial_real_ ) + ( ( _final_real_ ) - ( _initial_real_ ) ) * ( _final_real_ratio_ ) )

// ~~

#define REAL_64_DumpAngle( _angle_ ) \
    \
    STREAMED_Output << #_angle_ << " = " << ( ( _angle_ ) / REAL_64_Degree ) << "\n"

// ~~

inline const REAL_64 REAL_64_GetAxisVectorAngle(
    REAL_64 cosinus,
    REAL_64 sinus
    )
{
}

// ~~

inline const REAL_64 REAL_64_GetVectorAngle(
    const REAL_64 x,
    const REAL_64 y
    )
{
    REAL_64
        angle,
        cosinus,
        length,
        one_over_length,
        sinus;

    length = REAL_64_GetSquareRoot( x * x + y * y );

    if ( REAL_64_IsRoughlyZero( length ) )
    {
        return 0.0;
    }
    else
    {
        one_over_length = 1.0 / length;

        cosinus = x * one_over_length;
        sinus = y * one_over_length;

        if ( REAL_64_IsRoughlyOne( cosinus ) )
        {
            return 0.0;
        }
        else if ( REAL_64_IsRoughlyOne( sinus ) )
        {
            return REAL_64_90Degrees;
        }
        else if ( REAL_64_IsRoughlyMinusOne( sinus ) )
        {
            return -REAL_64_90Degrees;
        }
        else if ( REAL_64_IsRoughlyMinusOne( cosinus ) )
        {
            if ( sinus >= 0.0 )
            {
                return REAL_64_180Degrees;
            }
            else
            {
                return -REAL_64_180Degrees;
            }
        }
        else
        {
            if ( REAL_64_IsRoughlyZero( sinus ) )
            {
                NATIVE_KeepInsideInterval( cosinus, -1.0, 1.0 );

                angle = REAL_64_GetArcCosinus( REAL_64_GetPositive( cosinus ) );
            }
            else
            {
                NATIVE_KeepInsideInterval( sinus, -1.0, 1.0 );

                angle = REAL_64_GetArcSinus( REAL_64_GetPositive( sinus ) );
            }

            if ( cosinus >= 0.0 )
            {
                if ( sinus < 0.0 )
                {
                    angle = -angle ;
                }
            }
            else
            {
                if ( sinus >= 0.0 )
                {
                    angle = REAL_64_Pi - angle;
                }
                else
                {
                    angle = -REAL_64_Pi + angle;
                }
            }

            DEBUG_Check( REAL_64_IsRoughlyEqual( REAL_64_GetCosinus( angle ), cosinus ) );
            DEBUG_Check( REAL_64_IsRoughlyEqual( REAL_64_GetSinus( angle ), sinus ) );

            return angle;
        }
    }
}

// ~~

inline const REAL_64 REAL_64_GetClosestAngle(
    const REAL_64 angle,
    const REAL_64 other_angle
    )
{
    REAL_64
        closest_angle;

    closest_angle = angle;

    if ( closest_angle - other_angle > REAL_64_180Degrees
         || other_angle - closest_angle > REAL_64_180Degrees )
    {
        while ( closest_angle < other_angle )
        {
            closest_angle += REAL_64_360Degrees;
        }

        while ( closest_angle - other_angle > REAL_64_180Degrees )
        {
            closest_angle -= REAL_64_360Degrees;
        }
    }

    DEBUG_Check(
        REAL_64_GetPositive( closest_angle - other_angle ) <= REAL_64_180Degrees
        );

    return closest_angle;
}

// ~~

inline const BOOL_8 REAL_64_IsRoughlyEquivalentAngle(
    const REAL_64 angle,
    const REAL_64 other_angle
    )
{
    REAL_64
        angle_difference;

    angle_difference = REAL_64_GetPositive( angle - other_angle );

    while ( angle_difference >= REAL_64_360Degrees - REAL_64_Precision )
    {
        angle_difference -= REAL_64_360Degrees;
    }

    return REAL_64_IsRoughlyZero( angle_difference );
}
