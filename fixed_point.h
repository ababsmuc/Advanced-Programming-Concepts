#ifndef APC_FIXED_POINT_H
#define APC_FIXED_POINT_H

#include <cstdint>

#define FIXED_BITS        64
#define FIXED_WBITS       40
#define FIXED_FBITS       24
#define MAKE_FIXED(a)     (int64_t)((a*(1 << FIXED_FBITS)))
#define MAKE_FLOAT(a)     (double )((double)a/(double) (1<< FIXED_FBITS))

class fixed_point {
public:
    static int64_t Mul(int64_t a, int64_t b);
    void Run();
    static int64_t Add(int64_t a, int64_t b);
    static int64_t Sub(int64_t a, int64_t b);
    static int64_t Div(int64_t a, int64_t b);
};


#endif //APC_FIXED_POINT_H
