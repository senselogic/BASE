// == LOCAL

// -- IMPORTS

#include "real_32.hpp"
#include "real_32_quaternion.hpp"
#include "real_32_vector_3.hpp"
#include "real_64_quaternion.hpp"
#include "void.hpp"

// == PUBLIC

// -- INQUIRIES

VOID REAL_32_QUATERNION::GetXyzAngles(
    REAL_32 & x_angle,
    REAL_32 & y_angle,
    REAL_32 & z_angle
    ) const
{
    REAL_32_QUATERNION
        rotated_quaternion;
    REAL_32_VECTOR_3
        x_axis_vector,
        y_axis_vector;

    rotated_quaternion = *this;
    x_axis_vector = rotated_quaternion.GetXAxisVector();

    if ( REAL_32_IsRoughlyZero( x_axis_vector.X )
         && REAL_32_IsRoughlyZero( x_axis_vector.Y ) )
    {
        z_angle = 0.0f;
    }
    else
    {
        z_angle = REAL_32_GetVectorAngle( x_axis_vector.X, x_axis_vector.Y );
        rotated_quaternion.PostRotateAroundZ( -z_angle );
    }

    x_axis_vector = rotated_quaternion.GetXAxisVector();

    if ( REAL_32_IsRoughlyZero( x_axis_vector.X )
         && REAL_32_IsRoughlyZero( x_axis_vector.Z ) )
    {
        y_angle = 0.0f;
    }
    else
    {
        y_angle = -REAL_32_GetVectorAngle( x_axis_vector.X, x_axis_vector.Z );
        rotated_quaternion.PostRotateAroundY( -y_angle );
    }

    y_axis_vector = rotated_quaternion.GetYAxisVector();

    if ( REAL_32_IsRoughlyZero( y_axis_vector.Y )
         && REAL_32_IsRoughlyZero( y_axis_vector.Z ) )
    {
        x_angle = 0.0f;
    }
    else
    {
        x_angle = REAL_32_GetVectorAngle( y_axis_vector.Y, y_axis_vector.Z );
    }
}

// ~~

VOID REAL_32_QUATERNION::GetXzyAngles(
    REAL_32 & x_angle,
    REAL_32 & z_angle,
    REAL_32 & y_angle
    ) const
{
    REAL_32_QUATERNION
        rotated_quaternion;
    REAL_32_VECTOR_3
        x_axis_vector,
        z_axis_vector;

    rotated_quaternion = *this;
    x_axis_vector = rotated_quaternion.GetXAxisVector();

    if ( REAL_32_IsRoughlyZero( x_axis_vector.X )
         && REAL_32_IsRoughlyZero( x_axis_vector.Z ) )
    {
        y_angle = 0.0f;
    }
    else
    {
        y_angle = REAL_32_GetVectorAngle( x_axis_vector.X, x_axis_vector.Z );
        rotated_quaternion.PostRotateAroundY( -y_angle );
    }

    x_axis_vector = rotated_quaternion.GetXAxisVector();

    if ( REAL_32_IsRoughlyZero( x_axis_vector.X )
         && REAL_32_IsRoughlyZero( x_axis_vector.Y ) )
    {
        z_angle = 0.0f;
    }
    else
    {
        z_angle = -REAL_32_GetVectorAngle( x_axis_vector.X, x_axis_vector.Y );
        rotated_quaternion.PostRotateAroundZ( -z_angle );
    }

    z_axis_vector = rotated_quaternion.GetZAxisVector();

    if ( REAL_32_IsRoughlyZero( z_axis_vector.Z )
         && REAL_32_IsRoughlyZero( z_axis_vector.Y ) )
    {
        x_angle = 0.0f;
    }
    else
    {
        x_angle = REAL_32_GetVectorAngle( z_axis_vector.Z, z_axis_vector.Y );
    }
}

// ~~

VOID REAL_32_QUATERNION::GetYxzAngles(
    REAL_32 & y_angle,
    REAL_32 & x_angle,
    REAL_32 & z_angle
    ) const
{
    REAL_32_QUATERNION
        rotated_quaternion;
    REAL_32_VECTOR_3
        y_axis_vector,
        x_axis_vector;

    rotated_quaternion = *this;
    y_axis_vector = rotated_quaternion.GetYAxisVector();

    if ( REAL_32_IsRoughlyZero( y_axis_vector.Y )
         && REAL_32_IsRoughlyZero( y_axis_vector.X ) )
    {
        z_angle = 0.0f;
    }
    else
    {
        z_angle = REAL_32_GetVectorAngle( y_axis_vector.Y, y_axis_vector.X );
        rotated_quaternion.PostRotateAroundZ( -z_angle );
    }

    y_axis_vector = rotated_quaternion.GetYAxisVector();

    if ( REAL_32_IsRoughlyZero( y_axis_vector.Y )
         && REAL_32_IsRoughlyZero( y_axis_vector.Z ) )
    {
        x_angle = 0.0f;
    }
    else
    {
        x_angle = -REAL_32_GetVectorAngle( y_axis_vector.Y, y_axis_vector.Z );
        rotated_quaternion.PostRotateAroundX( -x_angle );
    }

    x_axis_vector = rotated_quaternion.GetXAxisVector();

    if ( REAL_32_IsRoughlyZero( x_axis_vector.X )
         && REAL_32_IsRoughlyZero( x_axis_vector.Z ) )
    {
        y_angle = 0.0f;
    }
    else
    {
        y_angle = REAL_32_GetVectorAngle( x_axis_vector.X, x_axis_vector.Z );
    }
}

// ~~

VOID REAL_32_QUATERNION::GetYzxAngles(
    REAL_32 & y_angle,
    REAL_32 & z_angle,
    REAL_32 & x_angle
    ) const
{
    REAL_32_QUATERNION
        rotated_quaternion;
    REAL_32_VECTOR_3
        y_axis_vector,
        z_axis_vector;

    rotated_quaternion = *this;
    y_axis_vector = rotated_quaternion.GetYAxisVector();

    if ( REAL_32_IsRoughlyZero( y_axis_vector.Y )
         && REAL_32_IsRoughlyZero( y_axis_vector.Z ) )
    {
        x_angle = 0.0f;
    }
    else
    {
        x_angle = REAL_32_GetVectorAngle( y_axis_vector.Y, y_axis_vector.Z );
        rotated_quaternion.PostRotateAroundX( -x_angle );
    }

    y_axis_vector = rotated_quaternion.GetYAxisVector();

    if ( REAL_32_IsRoughlyZero( y_axis_vector.Y )
         && REAL_32_IsRoughlyZero( y_axis_vector.X ) )
    {
        z_angle = 0.0f;
    }
    else
    {
        z_angle = -REAL_32_GetVectorAngle( y_axis_vector.Y, y_axis_vector.X );
        rotated_quaternion.PostRotateAroundZ( -z_angle );
    }

    z_axis_vector = rotated_quaternion.GetZAxisVector();

    if ( REAL_32_IsRoughlyZero( z_axis_vector.Z )
         && REAL_32_IsRoughlyZero( z_axis_vector.X ) )
    {
        y_angle = 0.0f;
    }
    else
    {
        y_angle = REAL_32_GetVectorAngle( z_axis_vector.Z, z_axis_vector.X );
    }
}

// ~~

VOID REAL_32_QUATERNION::GetZxyAngles(
    REAL_32 & z_angle,
    REAL_32 & x_angle,
    REAL_32 & y_angle
    ) const
{
    REAL_32_QUATERNION
        rotated_quaternion;
    REAL_32_VECTOR_3
        z_axis_vector,
        x_axis_vector;

    rotated_quaternion = *this;
    z_axis_vector = rotated_quaternion.GetZAxisVector();

    if ( REAL_32_IsRoughlyZero( z_axis_vector.Z )
         && REAL_32_IsRoughlyZero( z_axis_vector.X ) )
    {
        y_angle = 0.0f;
    }
    else
    {
        y_angle = REAL_32_GetVectorAngle( z_axis_vector.Z, z_axis_vector.X );
        rotated_quaternion.PostRotateAroundY( -y_angle );
    }

    z_axis_vector = rotated_quaternion.GetZAxisVector();

    if ( REAL_32_IsRoughlyZero( z_axis_vector.Z )
         && REAL_32_IsRoughlyZero( z_axis_vector.Y ) )
    {
        x_angle = 0.0f;
    }
    else
    {
        x_angle = -REAL_32_GetVectorAngle( z_axis_vector.Z, z_axis_vector.Y );
        rotated_quaternion.PostRotateAroundX( -x_angle );
    }

    x_axis_vector = rotated_quaternion.GetXAxisVector();

    if ( REAL_32_IsRoughlyZero( x_axis_vector.X )
         && REAL_32_IsRoughlyZero( x_axis_vector.Y ) )
    {
        z_angle = 0.0f;
    }
    else
    {
        z_angle = REAL_32_GetVectorAngle( x_axis_vector.X, x_axis_vector.Y );
    }
}

// ~~

VOID REAL_32_QUATERNION::GetZyxAngles(
    REAL_32 & z_angle,
    REAL_32 & y_angle,
    REAL_32 & x_angle
    ) const
{
    REAL_32_QUATERNION
        rotated_quaternion;
    REAL_32_VECTOR_3
        z_axis_vector,
        y_axis_vector;

    rotated_quaternion = *this;
    z_axis_vector = rotated_quaternion.GetZAxisVector();

    if ( REAL_32_IsRoughlyZero( z_axis_vector.Z )
         && REAL_32_IsRoughlyZero( z_axis_vector.Y ) )
    {
        x_angle = 0.0f;
    }
    else
    {
        x_angle = REAL_32_GetVectorAngle( z_axis_vector.Z, z_axis_vector.Y );
        rotated_quaternion.PostRotateAroundX( -x_angle );
    }

    z_axis_vector = rotated_quaternion.GetZAxisVector();

    if ( REAL_32_IsRoughlyZero( z_axis_vector.Z )
         && REAL_32_IsRoughlyZero( z_axis_vector.X ) )
    {
        y_angle = 0.0f;
    }
    else
    {
        y_angle = -REAL_32_GetVectorAngle( z_axis_vector.Z, z_axis_vector.X );
        rotated_quaternion.PostRotateAroundY( -y_angle );
    }

    y_axis_vector = rotated_quaternion.GetYAxisVector();

    if ( REAL_32_IsRoughlyZero( y_axis_vector.Y )
         && REAL_32_IsRoughlyZero( y_axis_vector.X ) )
    {
        z_angle = 0.0f;
    }
    else
    {
        z_angle = REAL_32_GetVectorAngle( y_axis_vector.Y, y_axis_vector.X );
    }
}

// -- OPERATIONS

VOID REAL_32_QUATERNION::SetFromQuaternion(
    const REAL_64_QUATERNION & quaternion
    )
{
    X = quaternion.X;
    Y = quaternion.Y;
    Z = quaternion.Z;
    W = quaternion.W;
}
