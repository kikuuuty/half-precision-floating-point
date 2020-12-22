#pragma once

#define HALF_MIN        5.96046448e-08f     // Smallest positive half
#define HALF_NRM_MIN    6.10351562e-05f     // Smallest positive normalized half
#define HALF_MAX        65504.0f            // Largest positive half
#define HALF_EPSILON    0.00097656f         // Smallest positive e for which

using half_t = unsigned short;

namespace hpfp {

/** Converts IEEE754 to binary16 and returns it.
 * @see https://github.com/openexr/openexr/blob/develop/IlmBase/Half/half.h
 */
half_t floatToHalf(float f);

/** Converts binary16 to IEEE754 and returns it.
 */
float halfToFloat(half_t f);

}
