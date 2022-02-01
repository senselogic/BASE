// == LOCAL

// -- IMPORTS

#include "real_32.hpp"
#include "real_32_matrix_12.hpp"
#include "real_32_matrix_16.hpp"
#include "real_32_matrix_9.hpp"
#include "real_32_quaternion.hpp"
#include "void.hpp"

// == PUBLIC

// -- OPERATIONS

VOID REAL_32_MATRIX_16::SetFromMatrix(
    const REAL_32_MATRIX_9 & matrix
    )
{
    XVector.X = matrix.XVector.X;
    XVector.Y = matrix.XVector.Y;
    XVector.Z = matrix.XVector.Z;
    XVector.W = 0.0f;

    YVector.X = matrix.YVector.X;
    YVector.Y = matrix.YVector.Y;
    YVector.Z = matrix.YVector.Z;
    YVector.W = 0.0f;

    ZVector.X = matrix.ZVector.X;
    ZVector.Y = matrix.ZVector.Y;
    ZVector.Z = matrix.ZVector.Z;
    ZVector.W = 0.0f;

    WVector.X = 0.0f;
    WVector.Y = 0.0f;
    WVector.Z = 0.0f;
    WVector.W = 1.0f;
}

// ~~

VOID REAL_32_MATRIX_16::SetFromMatrix(
    const REAL_32_MATRIX_12 & matrix
    )
{
    XVector.X = matrix.XVector.X;
    XVector.Y = matrix.XVector.Y;
    XVector.Z = matrix.XVector.Z;
    XVector.W = 0.0f;

    YVector.X = matrix.YVector.X;
    YVector.Y = matrix.YVector.Y;
    YVector.Z = matrix.YVector.Z;
    YVector.W = 0.0f;

    ZVector.X = matrix.ZVector.X;
    ZVector.Y = matrix.ZVector.Y;
    ZVector.Z = matrix.ZVector.Z;
    ZVector.W = 0.0f;

    WVector.X = matrix.WVector.X;
    WVector.Y = matrix.WVector.Y;
    WVector.Z = matrix.WVector.Z;
    WVector.W = 1.0f;
}

// ~~

VOID REAL_32_MATRIX_16::SetFromQuaternion(
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
    XVector.W = 0.0f;

    YVector.X = xy - wz;
    YVector.Y = 1.0f - xx - zz;
    YVector.Z = yz + wx;
    YVector.W = 0.0f;

    ZVector.X = xz + wy;
    ZVector.Y = yz - wx;
    ZVector.Z = 1.0f - xx - yy;
    ZVector.W = 0.0f;

    WVector.X = 0.0f;
    WVector.Y = 0.0f;
    WVector.Z = 0.0f;
    WVector.W = 1.0f;
}
