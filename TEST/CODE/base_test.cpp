// == LOCAL

// -- IMPORTS

#include "char_8.hpp"
#include "int_32.hpp"
#include "real_32_quaternion_test.hpp"
#include "real_64_quaternion_test.hpp"

// == GLOBAL

// -- FUNCTIONS

INT_32 main(
    INT_32 argument_count,
    CHAR_8 * argument_array[]
    )
{
    REAL_32_QUATERNION_TEST::Run();
    REAL_64_QUATERNION_TEST::Run();

    return 0;
}
