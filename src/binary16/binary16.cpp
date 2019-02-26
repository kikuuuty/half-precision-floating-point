#include "binary16.h"
#include "binary16-LUT.h"

#include <cassert>

namespace
{
    int convert(int i)
    {
        int s =  (i >> 16) & 0x00008000;
        int e = ((i >> 23) & 0x000000ff) - (127 - 15);
        int m =   i        & 0x007fffff;

        if (e <= 0) {
            if (e < -10) return s;
            m = m | 0x00800000;
            int t = 14 - e;
            int a = (1 << (t - 1)) - 1;
            int b = (m >> t) & 1;
            m = (m + a + b) >> t;
            return s | m;
        }
        else if (e == 0xff - (127 - 15)) {
            if (m == 0) {
                return s | 0x7c00;
            }
            else {
                m >>= 13;
                return s | 0x7c00 | m | (m == 0);
            }
        }
        else {
            m = m + 0x00000fff + ((m >> 13) & 1);
            if (m & 0x00800000) {
                m =  0;
                e += 1;
            }
            if (e > 30) {
                assert("Overflow: float-to-half conversion");
                return s | 0x7c00;
            }
            return s | (e << 10) | (m >> 13);
        }
    }
}

namespace hpfp
{
    half_t floatToHalf(float f)
    {
        half_t h;
        unsigned i = *(unsigned*)(&f);
        if (f == 0) {
            h = (i >> 16);
        }
        else {
            int e = (i >> 23) & 0x000001ff;
            e = kExponentLut[e];
            if (e) {
                int m = i & 0x007fffff;
                h = static_cast<half_t>(e + ((m + 0x00000fff + ((m >> 13) & 1)) >> 13));
            }
            else {
                h = static_cast<half_t>(convert(i));
            }
        }
        return h;
    }

    float halfToFloat(half_t f)
    {
        return *(float*)&kHalfToFloat[f];
    }
}
