// == LOCAL

// -- IMPORTS

#include "debug.hpp"
#include "real_32.hpp"
#include "real_32_matrix_12.hpp"
#include "real_32_matrix_16.hpp"
#include "real_32_matrix_9.hpp"
#include "real_32_quaternion.hpp"
#include "real_32_vector_3.hpp"
#include "void.hpp"

// == PUBLIC

// -- OPERATIONS

VOID REAL_32_MATRIX_9::SetFromMatrix(
    const REAL_32_MATRIX_12 & matrix
    )
{
    XVector.X = matrix.XVector.X;
    XVector.Y = matrix.XVector.Y;
    XVector.Z = matrix.XVector.Z;

    YVector.X = matrix.YVector.X;
    YVector.Y = matrix.YVector.Y;
    YVector.Z = matrix.YVector.Z;

    ZVector.X = matrix.ZVector.X;
    ZVector.Y = matrix.ZVector.Y;
    ZVector.Z = matrix.ZVector.Z;
}

// ~~

VOID REAL_32_MATRIX_9::SetFromMatrix(
    const REAL_32_MATRIX_16 & matrix
    )
{
    XVector.X = matrix.XVector.X;
    XVector.Y = matrix.XVector.Y;
    XVector.Z = matrix.XVector.Z;

    YVector.X = matrix.YVector.X;
    YVector.Y = matrix.YVector.Y;
    YVector.Z = matrix.YVector.Z;

    ZVector.X = matrix.ZVector.X;
    ZVector.Y = matrix.ZVector.Y;
    ZVector.Z = matrix.ZVector.Z;
}

// ~~

VOID REAL_32_MATRIX_9::SetFromQuaternion(
    const REAL_32_QUATERNION & quaternion
    )
{
    REAL_32
        wx,
        wy,
        wz,
        xx,
        yy,
        yz,
        xy,
        xz,
        zz,
        x2,
        y2,
        z2;

    x2 = quaternion.X + quaternion.X;
    y2 = quaternion.Y + quaternion.Y;
    z2 = quaternion.Z + quaternion.Z;

    xx = quaternion.X * x2;
    xy = quaternion.X * y2;
    xz = quaternion.X * z2;

    yy = quaternion.Y * y2;
    yz = quaternion.Y * z2;
    zz = quaternion.Z * z2;

    wx = quaternion.W * x2;
    wy = quaternion.W * y2;
    wz = quaternion.W * z2;

    XVector.X = 1.0f - yy - zz;
    XVector.Y = xy + wz;
    XVector.Z = xz - wy;

    YVector.X = xy - wz;
    YVector.Y = 1.0f - xx - zz;
    YVector.Z = yz + wx;

    ZVector.X = xz + wy;
    ZVector.Y = yz - wx;
    ZVector.Z = 1.0f - xx - yy;
}

// ~~

VOID REAL_32_MATRIX_9::GetXyzAngles(
    REAL_32 & x_angle,
    REAL_32 & y_angle,
    REAL_32 & z_angle
    ) const
{
    REAL_32_MATRIX_9
        rotated_matrix;
    REAL_32_VECTOR_3
        x_axis_vector,
        y_axis_vector;

    rotated_matrix = *this;
    x_axis_vector = rotated_matrix.GetXAxisVector();

    if ( REAL_32_IsRoughlyZero( x_axis_vector.X )
         && REAL_32_IsRoughlyZero( x_axis_vector.Y ) )
    {
        z_angle = 0.0f;
    }
    else
    {
        z_angle = REAL_32_GetVectorAngle( x_axis_vector.X, x_axis_vector.Y );
        rotated_matrix.PostRotateAroundZ( -z_angle );
    }

    x_axis_vector = rotated_matrix.GetXAxisVector();

    if ( REAL_32_IsRoughlyZero( x_axis_vector.X )
         && REAL_32_IsRoughlyZero( x_axis_vector.Z ) )
    {
        y_angle = 0.0f;
    }
    else
    {
        y_angle = -REAL_32_GetVectorAngle( x_axis_vector.X, x_axis_vector.Z );
        rotated_matrix.PostRotateAroundY( -y_angle );
    }

    y_axis_vector = rotated_matrix.GetYAxisVector();

    if ( REAL_32_IsRoughlyZero( y_axis_vector.Y )
         && REAL_32_IsRoughlyZero( y_axis_vector.Z ) )
    {
        x_angle = 0.0f;
    }
    else
    {
        x_angle = REAL_32_GetVectorAngle( y_axis_vector.Y, y_axis_vector.Z );
    }

    #if DEBUG_Mode
        REAL_32_MATRIX_9
            rotation_matrix;

        rotation_matrix.SetFromRotationAroundXyz( x_angle, y_angle, z_angle );

        DEBUG_Check( rotation_matrix.IsRoughlyEqual( *this ) );
    #endif
}

// ~~

VOID REAL_32_MATRIX_9::GetXzyAngles(
    REAL_32 & x_angle,
    REAL_32 & z_angle,
    REAL_32 & y_angle
    ) const
{
    REAL_32_MATRIX_9
        rotated_matrix;
    REAL_32_VECTOR_3
        x_axis_vector,
        z_axis_vector;

    rotated_matrix = *this;
    x_axis_vector = rotated_matrix.GetXAxisVector();

    if ( REAL_32_IsRoughlyZero( x_axis_vector.X )
         && REAL_32_IsRoughlyZero( x_axis_vector.Z ) )
    {
        y_angle = 0.0f;
    }
    else
    {
        y_angle = REAL_32_GetVectorAngle( x_axis_vector.X, x_axis_vector.Z );
        rotated_matrix.PostRotateAroundY( -y_angle );
    }

    x_axis_vector = rotated_matrix.GetXAxisVector();

    if ( REAL_32_IsRoughlyZero( x_axis_vector.X )
         && REAL_32_IsRoughlyZero( x_axis_vector.Y ) )
    {
        z_angle = 0.0f;
    }
    else
    {
        z_angle = -REAL_32_GetVectorAngle( x_axis_vector.X, x_axis_vector.Y );
        rotated_matrix.PostRotateAroundZ( -z_angle );
    }

    z_axis_vector = rotated_matrix.GetZAxisVector();

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

VOID REAL_32_MATRIX_9::GetYxzAngles(
    REAL_32 & y_angle,
    REAL_32 & x_angle,
    REAL_32 & z_angle
    ) const
{
    REAL_32_MATRIX_9
        rotated_matrix;
    REAL_32_VECTOR_3
        y_axis_vector,
        x_axis_vector;

    rotated_matrix = *this;
    y_axis_vector = rotated_matrix.GetYAxisVector();

    if ( REAL_32_IsRoughlyZero( y_axis_vector.Y )
         && REAL_32_IsRoughlyZero( y_axis_vector.X ) )
    {
        z_angle = 0.0f;
    }
    else
    {
        z_angle = REAL_32_GetVectorAngle( y_axis_vector.Y, y_axis_vector.X );
        rotated_matrix.PostRotateAroundZ( -z_angle );
    }

    y_axis_vector = rotated_matrix.GetYAxisVector();

    if ( REAL_32_IsRoughlyZero( y_axis_vector.Y )
         && REAL_32_IsRoughlyZero( y_axis_vector.Z ) )
    {
        x_angle = 0.0f;
    }
    else
    {
        x_angle = -REAL_32_GetVectorAngle( y_axis_vector.Y, y_axis_vector.Z );
        rotated_matrix.PostRotateAroundX( -x_angle );
    }

    x_axis_vector = rotated_matrix.GetXAxisVector();

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

VOID REAL_32_MATRIX_9::GetYzxAngles(
    REAL_32 & y_angle,
    REAL_32 & z_angle,
    REAL_32 & x_angle
    ) const
{
    REAL_32_MATRIX_9
        rotated_matrix;
    REAL_32_VECTOR_3
        y_axis_vector,
        z_axis_vector;

    rotated_matrix = *this;
    y_axis_vector = rotated_matrix.GetYAxisVector();

    if ( REAL_32_IsRoughlyZero( y_axis_vector.Y )
         && REAL_32_IsRoughlyZero( y_axis_vector.Z ) )
    {
        x_angle = 0.0f;
    }
    else
    {
        x_angle = REAL_32_GetVectorAngle( y_axis_vector.Y, y_axis_vector.Z );
        rotated_matrix.PostRotateAroundX( -x_angle );
    }

    y_axis_vector = rotated_matrix.GetYAxisVector();

    if ( REAL_32_IsRoughlyZero( y_axis_vector.Y )
         && REAL_32_IsRoughlyZero( y_axis_vector.X ) )
    {
        z_angle = 0.0f;
    }
    else
    {
        z_angle = -REAL_32_GetVectorAngle( y_axis_vector.Y, y_axis_vector.X );
        rotated_matrix.PostRotateAroundZ( -z_angle );
    }

    z_axis_vector = rotated_matrix.GetZAxisVector();

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

VOID REAL_32_MATRIX_9::GetZxyAngles(
    REAL_32 & z_angle,
    REAL_32 & x_angle,
    REAL_32 & y_angle
    ) const
{
    REAL_32_MATRIX_9
        rotated_matrix;
    REAL_32_VECTOR_3
        z_axis_vector,
        x_axis_vector;

    rotated_matrix = *this;
    z_axis_vector = rotated_matrix.GetZAxisVector();

    if ( REAL_32_IsRoughlyZero( z_axis_vector.Z )
         && REAL_32_IsRoughlyZero( z_axis_vector.X ) )
    {
        y_angle = 0.0f;
    }
    else
    {
        y_angle = REAL_32_GetVectorAngle( z_axis_vector.Z, z_axis_vector.X );
        rotated_matrix.PostRotateAroundY( -y_angle );
    }

    z_axis_vector = rotated_matrix.GetZAxisVector();

    if ( REAL_32_IsRoughlyZero( z_axis_vector.Z )
         && REAL_32_IsRoughlyZero( z_axis_vector.Y ) )
    {
        x_angle = 0.0f;
    }
    else
    {
        x_angle = -REAL_32_GetVectorAngle( z_axis_vector.Z, z_axis_vector.Y );
        rotated_matrix.PostRotateAroundX( -x_angle );
    }

    x_axis_vector = rotated_matrix.GetXAxisVector();

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

VOID REAL_32_MATRIX_9::GetZyxAngles(
    REAL_32 & z_angle,
    REAL_32 & y_angle,
    REAL_32 & x_angle
    ) const
{
    REAL_32_MATRIX_9
        rotated_matrix;
    REAL_32_VECTOR_3
        z_axis_vector,
        y_axis_vector;

    rotated_matrix = *this;
    z_axis_vector = rotated_matrix.GetZAxisVector();

    if ( REAL_32_IsRoughlyZero( z_axis_vector.Z )
         && REAL_32_IsRoughlyZero( z_axis_vector.Y ) )
    {
        x_angle = 0.0f;
    }
    else
    {
        x_angle = REAL_32_GetVectorAngle( z_axis_vector.Z, z_axis_vector.Y );
        rotated_matrix.PostRotateAroundX( -x_angle );
    }

    z_axis_vector = rotated_matrix.GetZAxisVector();

    if ( REAL_32_IsRoughlyZero( z_axis_vector.Z )
         && REAL_32_IsRoughlyZero( z_axis_vector.X ) )
    {
        y_angle = 0.0f;
    }
    else
    {
        y_angle = -REAL_32_GetVectorAngle( z_axis_vector.Z, z_axis_vector.X );
        rotated_matrix.PostRotateAroundY( -y_angle );
    }

    y_axis_vector = rotated_matrix.GetYAxisVector();

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
