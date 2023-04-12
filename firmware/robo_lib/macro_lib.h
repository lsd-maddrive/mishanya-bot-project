#ifndef MACRO_LIB_H
#define MACRO_LIB_H

#define PI                                        3.1415926535F
#define DEG2RAD                                   0.0174532925F
#define RAD2DEG                                   57.2957795131F

#define FROUND(x)                                 (float)(((x) >= 0)?(int32_t)((x) + 0.5):(int32_t)((x) - 0.5))
#define CHECK_IN_RANGE(x, min_lim, max_lim)       (uint8_t)((x) >= (min_lim) && (x) <= (max_lim) ? 1 : 0)

#endif //MACRO_LIB_H
