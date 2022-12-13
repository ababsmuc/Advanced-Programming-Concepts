#include <iostream>
#define FIXED_BITS        64
#define FIXED_WBITS       56
#define FIXED_FBITS       8
//#define FIXED_TO_INT(a)   ((a) >> FIXED_FBITS)
//#define FIXED_FROM_INT(a) (int64_t)((a) << FIXED_FBITS)
#define FIXED_MAKE(a)     (int64_t)((a*(1 << FIXED_FBITS)))

static int64_t FIXED_Mul(int64_t a, int64_t b) {
    return(((int64_t)a*(int64_t)b) >> FIXED_FBITS);
}

static int64_t FIXED_Div(int64_t a, int64_t b) {
    return((int64_t)a<< FIXED_FBITS/ (int64_t)b);
}

static int64_t FIXED_Add(int64_t a, int64_t b) {
    return(((int64_t)a+(int64_t)b));
}

static int64_t FIXED_Sub(int64_t a, int64_t b) {
    return(((int64_t)a-(int64_t)b));
}

float sensor_to_ADC(float sensor_value){
    return (sensor_value*1023/10);
}
//maybe use templates
int main() {

   const int ADC_measures[10]={FIXED_MAKE(1.96), FIXED_MAKE(2.2),FIXED_MAKE(3.0), FIXED_MAKE(3.8), FIXED_MAKE(4.6)
                          , FIXED_MAKE(5.4), FIXED_MAKE(6.2), FIXED_MAKE(7.0), FIXED_MAKE(7.8), FIXED_MAKE(8.6)};
   const int_fast64_t pressure_before_unit[10]={FIXED_MAKE(281.83829),FIXED_MAKE(562.341325)
                                  ,FIXED_MAKE(5623.413252), FIXED_MAKE(56234.13252),
                                  FIXED_MAKE(562341.3252),FIXED_MAKE(5623413.252),
                                  FIXED_MAKE(56234132.52),FIXED_MAKE(562341325.2)
                                  ,FIXED_MAKE(5623413252.0),FIXED_MAKE(56234132520.0)};
    for(int i=0; i<10; i++) {
        std::cout << ADC_measures[i] << "\n";
    }
    for(int i=0; i<10; i++){
        std::cout<< pressure_before_unit[i]<< "\n";
    }

    return 0;
}
