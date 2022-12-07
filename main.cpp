#include <iostream>

float sensor_to_ADC(float sensor_value){
    return (sensor_value*1023/10);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    float ADC_measures[10]={1.96,2.2,3.0,3.8,4.6,5.4,6.2,7.0,7.8,8.6};
    float pressure_before_unit[10]={281.83829,562.341325,5623.413252,56234.13252,562341.3252,5623413.252,
                                    56234132.52,562341325.2,5623413252.0,56234132520.0};

    return 0;
}
