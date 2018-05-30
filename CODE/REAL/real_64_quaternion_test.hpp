// == LOCAL

// -- IMPORTS

#include "int_64.hpp"
#include "native.hpp"
#include "real_64.hpp"
#include "real_64_matrix_12.hpp"
#include "real_64_matrix_16.hpp"
#include "real_64_matrix_9.hpp"
#include "real_64_quaternion.hpp"
#include "void.hpp"

// == GLOBAL

// -- TYPES

struct REAL_64_QUATERNION_TEST
{
    // == PUBLIC

    // -- FUNCTIONS

    template <typename _MATRIX_>
    static VOID CheckProduct(
        const REAL_64_QUATERNION & quaternion,
        const _MATRIX_ & matrix
        )
    {
        _MATRIX_
            quaternion_matrix;

        quaternion_matrix.SetFromQuaternion( quaternion );

        NATIVE_Dump( quaternion );
        NATIVE_Dump( quaternion_matrix );
        NATIVE_Dump( matrix );
        NATIVE_Check( quaternion_matrix.IsRoughlyEqual( matrix ) );
    }

    // ~~

    template <typename _MATRIX_>
    static VOID CheckProduct(
        const INT_64 first_angle_index,
        const INT_64 last_angle_index,
        const INT_64 angle_step
        )
    {
        INT_64
            angle_index,
            x_angle_index,
            y_angle_index,
            z_angle_index;
        REAL_64
            angle,
            x_angle,
            y_angle,
            z_angle;
        REAL_64_QUATERNION
            quaternion;
        _MATRIX_
            matrix;

        NATIVE_ForEachIntervalIndex( angle_index, first_angle_index, last_angle_index )
        {
            angle = ( angle_index * angle_step ) * REAL_64_Degree;

            quaternion.SetFromRotationAroundX( angle );
            matrix.SetFromRotationAroundX( angle );

            REAL_64_DumpAngle( x_angle );
            CheckProduct( quaternion, matrix );

            quaternion.SetFromRotationAroundY( angle );
            matrix.SetFromRotationAroundY( angle );

            REAL_64_DumpAngle( y_angle );
            CheckProduct( quaternion, matrix );

            quaternion.SetFromRotationAroundZ( angle );
            matrix.SetFromRotationAroundZ( angle );

            REAL_64_DumpAngle( z_angle );
            CheckProduct( quaternion, matrix );
        }

        NATIVE_ForEachIntervalIndex( x_angle_index, first_angle_index, last_angle_index )
        {
            x_angle = ( x_angle_index * angle_step ) * REAL_64_Degree;

            NATIVE_ForEachIntervalIndex( y_angle_index, first_angle_index, last_angle_index )
            {
                y_angle = ( y_angle_index * angle_step ) * REAL_64_Degree;

                NATIVE_ForEachIntervalIndex( z_angle_index, first_angle_index, last_angle_index )
                {
                    z_angle = ( z_angle_index * angle_step ) * REAL_64_Degree;

                    quaternion.SetFromRotationAroundXyz( x_angle, y_angle, z_angle );
                    matrix.SetFromRotationAroundXyz( x_angle, y_angle, z_angle );

                    REAL_64_DumpAngle( x_angle );
                    REAL_64_DumpAngle( y_angle );
                    REAL_64_DumpAngle( z_angle );
                    CheckProduct( quaternion, matrix );

                    quaternion.SetFromRotationAroundXzy( x_angle, z_angle, y_angle );
                    matrix.SetFromRotationAroundXzy( x_angle, z_angle, y_angle );

                    REAL_64_DumpAngle( x_angle );
                    REAL_64_DumpAngle( z_angle );
                    REAL_64_DumpAngle( y_angle );
                    CheckProduct( quaternion, matrix );

                    quaternion.SetFromRotationAroundYxz( y_angle, x_angle, z_angle );
                    matrix.SetFromRotationAroundYxz( y_angle, x_angle, z_angle );

                    REAL_64_DumpAngle( y_angle );
                    REAL_64_DumpAngle( x_angle );
                    REAL_64_DumpAngle( z_angle );
                    CheckProduct( quaternion, matrix );

                    quaternion.SetFromRotationAroundYzx( y_angle, z_angle, x_angle );
                    matrix.SetFromRotationAroundYzx( y_angle, z_angle, x_angle );

                    REAL_64_DumpAngle( y_angle );
                    REAL_64_DumpAngle( z_angle );
                    REAL_64_DumpAngle( x_angle );
                    CheckProduct( quaternion, matrix );

                    quaternion.SetFromRotationAroundZxy( z_angle, x_angle, y_angle );
                    matrix.SetFromRotationAroundZxy( z_angle, x_angle, y_angle );

                    REAL_64_DumpAngle( z_angle );
                    REAL_64_DumpAngle( x_angle );
                    REAL_64_DumpAngle( y_angle );
                    CheckProduct( quaternion, matrix );

                    quaternion.SetFromRotationAroundZyx( z_angle, y_angle, x_angle );
                    matrix.SetFromRotationAroundZyx( z_angle, y_angle, x_angle );

                    REAL_64_DumpAngle( z_angle );
                    REAL_64_DumpAngle( y_angle );
                    REAL_64_DumpAngle( x_angle );
                    CheckProduct( quaternion, matrix );
                }
            }
        }
    }

    // ~~

    template <typename _MATRIX_>
    static VOID CheckAngles(
        const REAL_64_QUATERNION & quaternion,
        const REAL_64_QUATERNION & angle_quaternion,
        const _MATRIX_ & matrix,
        const _MATRIX_ & angle_matrix
        )
    {
        NATIVE_Dump( quaternion );
        NATIVE_Dump( angle_quaternion );
        NATIVE_Dump( matrix );
        NATIVE_Dump( angle_matrix );

        NATIVE_Check( angle_quaternion.IsRoughlyEquivalent( quaternion ) );
        NATIVE_Check( angle_matrix.IsRoughlyEqual( matrix ) );
    }

    // ~~

    template <typename _MATRIX_>
    static VOID CheckAngles(
        const INT_64 first_angle_index,
        const INT_64 last_angle_index,
        const INT_64 angle_step
        )
    {
        INT_64
            angle_index,
            x_angle_index,
            y_angle_index,
            z_angle_index;
        REAL_64
            angle,
            matrix_x_angle,
            matrix_y_angle,
            matrix_z_angle,
            quaternion_x_angle,
            quaternion_y_angle,
            quaternion_z_angle,
            x_angle,
            y_angle,
            z_angle;
        REAL_64_QUATERNION
            angle_quaternion,
            quaternion;
        _MATRIX_
            angle_matrix,
            matrix;

        NATIVE_ForEachIntervalIndex( x_angle_index, first_angle_index, last_angle_index )
        {
            x_angle = ( x_angle_index * angle_step ) * REAL_64_Degree;

            NATIVE_ForEachIntervalIndex( y_angle_index, first_angle_index, last_angle_index )
            {
                y_angle = ( y_angle_index * angle_step ) * REAL_64_Degree;

                NATIVE_ForEachIntervalIndex( z_angle_index, first_angle_index, last_angle_index )
                {
                    z_angle = ( z_angle_index * angle_step ) * REAL_64_Degree;

                    quaternion.SetFromRotationAroundXyz( x_angle, y_angle, z_angle );
                    quaternion.GetXyzAngles( quaternion_x_angle, quaternion_y_angle, quaternion_z_angle );
                    angle_quaternion.SetFromRotationAroundXyz( quaternion_x_angle, quaternion_y_angle, quaternion_z_angle );

                    matrix.SetFromRotationAroundXyz( x_angle, y_angle, z_angle );
                    matrix.GetXyzAngles( matrix_x_angle, matrix_y_angle, matrix_z_angle );
                    angle_matrix.SetFromRotationAroundXyz( x_angle, y_angle, z_angle );

                    REAL_64_DumpAngle( x_angle );
                    REAL_64_DumpAngle( y_angle );
                    REAL_64_DumpAngle( z_angle );
                    REAL_64_DumpAngle( quaternion_x_angle );
                    REAL_64_DumpAngle( quaternion_y_angle );
                    REAL_64_DumpAngle( quaternion_z_angle );
                    REAL_64_DumpAngle( matrix_x_angle );
                    REAL_64_DumpAngle( matrix_y_angle );
                    REAL_64_DumpAngle( matrix_z_angle );
                    CheckAngles( quaternion, angle_quaternion, matrix, angle_matrix );

                    quaternion.SetFromRotationAroundXzy( x_angle, z_angle, y_angle );
                    quaternion.GetXzyAngles( quaternion_x_angle, quaternion_z_angle, quaternion_y_angle );
                    angle_quaternion.SetFromRotationAroundXzy( x_angle, z_angle, y_angle );

                    matrix.SetFromRotationAroundXzy( x_angle, z_angle, y_angle );
                    matrix.GetXzyAngles( matrix_x_angle, matrix_z_angle, matrix_y_angle );
                    angle_matrix.SetFromRotationAroundXzy( x_angle, z_angle, y_angle );

                    REAL_64_DumpAngle( x_angle );
                    REAL_64_DumpAngle( z_angle );
                    REAL_64_DumpAngle( y_angle );
                    REAL_64_DumpAngle( quaternion_x_angle );
                    REAL_64_DumpAngle( quaternion_z_angle );
                    REAL_64_DumpAngle( quaternion_y_angle );
                    REAL_64_DumpAngle( matrix_x_angle );
                    REAL_64_DumpAngle( matrix_z_angle );
                    REAL_64_DumpAngle( matrix_y_angle );
                    CheckAngles( quaternion, angle_quaternion, matrix, angle_matrix );

                    quaternion.SetFromRotationAroundYxz( y_angle, x_angle, z_angle );
                    quaternion.GetYxzAngles( quaternion_y_angle, quaternion_x_angle, quaternion_z_angle );
                    angle_quaternion.SetFromRotationAroundYxz( y_angle, x_angle, z_angle );

                    matrix.SetFromRotationAroundYxz( y_angle, x_angle, z_angle );
                    matrix.GetYxzAngles( matrix_y_angle, matrix_x_angle, matrix_z_angle );
                    angle_matrix.SetFromRotationAroundYxz( y_angle, x_angle, z_angle );

                    REAL_64_DumpAngle( y_angle );
                    REAL_64_DumpAngle( x_angle );
                    REAL_64_DumpAngle( z_angle );
                    REAL_64_DumpAngle( quaternion_y_angle );
                    REAL_64_DumpAngle( quaternion_x_angle );
                    REAL_64_DumpAngle( quaternion_z_angle );
                    REAL_64_DumpAngle( matrix_y_angle );
                    REAL_64_DumpAngle( matrix_x_angle );
                    REAL_64_DumpAngle( matrix_z_angle );
                    CheckAngles( quaternion, angle_quaternion, matrix, angle_matrix );

                    quaternion.SetFromRotationAroundYzx( y_angle, z_angle, x_angle );
                    quaternion.GetYzxAngles( quaternion_y_angle, quaternion_z_angle, quaternion_x_angle );
                    angle_quaternion.SetFromRotationAroundYzx( y_angle, z_angle, x_angle );

                    matrix.SetFromRotationAroundYzx( y_angle, z_angle, x_angle );
                    matrix.GetYzxAngles( matrix_y_angle, matrix_z_angle, matrix_x_angle );
                    angle_matrix.SetFromRotationAroundYzx( y_angle, z_angle, x_angle );

                    REAL_64_DumpAngle( y_angle );
                    REAL_64_DumpAngle( z_angle );
                    REAL_64_DumpAngle( x_angle );
                    REAL_64_DumpAngle( quaternion_y_angle );
                    REAL_64_DumpAngle( quaternion_z_angle );
                    REAL_64_DumpAngle( quaternion_x_angle );
                    REAL_64_DumpAngle( matrix_y_angle );
                    REAL_64_DumpAngle( matrix_z_angle );
                    REAL_64_DumpAngle( matrix_x_angle );
                    CheckAngles( quaternion, angle_quaternion, matrix, angle_matrix );

                    quaternion.SetFromRotationAroundZxy( z_angle, x_angle, y_angle );
                    quaternion.GetZxyAngles( quaternion_z_angle, quaternion_x_angle, quaternion_y_angle );
                    angle_quaternion.SetFromRotationAroundZxy( z_angle, x_angle, y_angle );

                    matrix.SetFromRotationAroundZxy( z_angle, x_angle, y_angle );
                    matrix.GetZxyAngles( matrix_z_angle, matrix_x_angle, matrix_y_angle );
                    angle_matrix.SetFromRotationAroundZxy( z_angle, x_angle, y_angle );

                    REAL_64_DumpAngle( z_angle );
                    REAL_64_DumpAngle( x_angle );
                    REAL_64_DumpAngle( y_angle );
                    REAL_64_DumpAngle( quaternion_z_angle );
                    REAL_64_DumpAngle( quaternion_x_angle );
                    REAL_64_DumpAngle( quaternion_y_angle );
                    REAL_64_DumpAngle( matrix_z_angle );
                    REAL_64_DumpAngle( matrix_x_angle );
                    REAL_64_DumpAngle( matrix_y_angle );
                    CheckAngles( quaternion, angle_quaternion, matrix, angle_matrix );

                    quaternion.SetFromRotationAroundZyx( z_angle, y_angle, x_angle );
                    quaternion.GetZyxAngles( quaternion_z_angle, quaternion_y_angle, quaternion_x_angle );
                    angle_quaternion.SetFromRotationAroundZyx( z_angle, y_angle, x_angle );

                    matrix.SetFromRotationAroundZyx( z_angle, y_angle, x_angle );
                    matrix.GetZyxAngles( matrix_z_angle, matrix_y_angle, matrix_x_angle );
                    angle_matrix.SetFromRotationAroundZyx( z_angle, y_angle, x_angle );

                    REAL_64_DumpAngle( z_angle );
                    REAL_64_DumpAngle( y_angle );
                    REAL_64_DumpAngle( x_angle );
                    REAL_64_DumpAngle( quaternion_z_angle );
                    REAL_64_DumpAngle( quaternion_y_angle );
                    REAL_64_DumpAngle( quaternion_x_angle );
                    REAL_64_DumpAngle( matrix_z_angle );
                    REAL_64_DumpAngle( matrix_y_angle );
                    REAL_64_DumpAngle( matrix_x_angle );
                    CheckAngles( quaternion, angle_quaternion, matrix, angle_matrix );
                }
            }
        }
    }

    // ~~

    static VOID Run(
        )
    {
        INT_64
            angle_step,
            first_angle_index,
            last_angle_index;

        first_angle_index = -12;
        last_angle_index = 12;
        angle_step = 30;

        CheckAngles<REAL_64_MATRIX_9>( first_angle_index, last_angle_index, angle_step );
        CheckProduct<REAL_64_MATRIX_9>( first_angle_index, last_angle_index, angle_step );
        CheckProduct<REAL_64_MATRIX_12>( first_angle_index, last_angle_index, angle_step );
        CheckProduct<REAL_64_MATRIX_16>( first_angle_index, last_angle_index, angle_step );
    }
};
