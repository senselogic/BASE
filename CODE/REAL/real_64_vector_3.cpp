// == LOCAL

// -- IMPORTS

#include "real_32_vector_3.hpp"
#include "real_64_vector_3.hpp"
#include "void.hpp"

// == GLOBAL

// -- OPERATIONS

VOID REAL_64_VECTOR_3::SetFromVector(
    const REAL_32_VECTOR_3 & vector
    )
{
    X = vector.X;
    Y = vector.Y;
    Z = vector.Z;
}
