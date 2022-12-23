#ifndef APC_FIXED_POINT_H
#define APC_FIXED_POINT_H

#include <cstdint>


class fixed_point {
private:
#define FIXED_TOTAL_BITS        64
#define FIXED_WHOLE_BITS       40
#define FIXED_FRACTIONAL_BITS       24
#define CONVERT_TO_FIXED(a)     (int64_t)((a*(1 <<  FIXED_FRACTIONAL_BITS )))
#define CONVERT_TO_FLOAT(a)     (double )((double)a/(double) (1<<  FIXED_FRACTIONAL_BITS ))
public:
    static int64_t fixed_multiplication(int64_t a, int64_t b);

    void run();

    static int64_t fixed_addition(int64_t a, int64_t b);

    static int64_t fixed_subtraction(int64_t a, int64_t b);

    static int64_t fixed_division(int64_t a, int64_t b);
};


#endif //APC_FIXED_POINT_H
