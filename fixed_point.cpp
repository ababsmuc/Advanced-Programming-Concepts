#include <iostream>
#include <complex>
#include "fixed_point.h"

// This function performs the multiplication of two fixed point numbers.
int64_t fixed_point::fixed_multiplication(int64_t a, int64_t b) {
    return (((int64_t) a * (int64_t) b) >> FIXED_FRACTIONAL_BITS);
}

// This function performs the division of two fixed point numbers.
int64_t fixed_point::fixed_division(int64_t a, int64_t b) {
    return ((int64_t) a << FIXED_FRACTIONAL_BITS / (int64_t) b);
}

// This function performs the addition of two fixed point numbers.
int64_t fixed_point::fixed_addition(int64_t a, int64_t b) {
    return (((int64_t) a + (int64_t) b));
}

// This function performs the subtraction of two fixed point numbers.
int64_t fixed_point::fixed_subtraction(int64_t a, int64_t b) {
    return (((int64_t) a - (int64_t) b));
}

// This function converts the 10-bit ADC value into an analogue signal value
template<typename T>
T ADC_to_sensor(T ADC_value) {
    auto result = (ADC_value * 10 / 1023);
    return result;
}

// This function calculates the corresponding pressure value of an analogue signal value (in Pa unit)
template<typename T>
T calc_pressure_pascal(T analogue_value) {
    T pressure;
    T power;
    power = 1.25 * analogue_value - 10.75;
    pressure = std::pow(10, power);
    return pressure;
}

// This function perform the quadratic piecewise interpolation using the newton interpolation method
int64_t newton_poly_interpolation(int64_t x, int64_t x1, int64_t x2, int64_t x3, int64_t f1, int64_t f2, int64_t f3) {
    int64_t b1 = f1;
    int64_t b2 = fixed_point::fixed_division(fixed_point::fixed_subtraction(f2, f1),
                                             fixed_point::fixed_subtraction(x2, x1));
    int64_t b3 = fixed_point::fixed_division(
            fixed_point::fixed_subtraction(fixed_point::fixed_division(fixed_point::fixed_subtraction(f3, f2),
                                                                       fixed_point::fixed_subtraction(x3, x2)),
                                           fixed_point::fixed_division(fixed_point::fixed_subtraction(f2, f1),
                                                                       fixed_point::fixed_subtraction(x2, x1))),
            fixed_point::fixed_subtraction(x3, x1));
    int64_t result = fixed_point::fixed_addition(b1, fixed_point::fixed_addition(
            fixed_point::fixed_multiplication(b2, fixed_point::fixed_subtraction(x, x1)),
            fixed_point::fixed_multiplication(b3,
                                              fixed_point::fixed_multiplication(
                                                      fixed_point::fixed_subtraction(x,
                                                                                     x1),
                                                      fixed_point::fixed_subtraction(x,
                                                                                     x2)))));
    return result;
}

// This function calculates the corresponding pressure value using the polynomial interpolation function
template<typename T>
int64_t calculating_pressure(T value) {
    int64_t result = 0;
    if (value >= 1.96 && value <= 3.0) {
        auto number = 1.96 + static_cast<float>(rand()) * static_cast<float>(value - 1.96) / RAND_MAX;
        auto pressure = calc_pressure_pascal(number);
        result = newton_poly_interpolation(CONVERT_TO_FIXED(value), CONVERT_TO_FIXED(1.96), CONVERT_TO_FIXED(number),
                                           CONVERT_TO_FIXED(3.0),
                                           CONVERT_TO_FIXED(5.0 * std::pow(10, -9)), CONVERT_TO_FIXED(pressure),
                                           CONVERT_TO_FIXED(1.0 * std::pow(10, -7)));
        return result;
    } else if (value >= 3.0 && value <= 4.6) {
        auto number = 3.0 + static_cast<float>(rand()) * static_cast<float>(value - 4.6) / RAND_MAX;
        auto pressure = calc_pressure_pascal(number);
        result = newton_poly_interpolation(CONVERT_TO_FIXED(value), CONVERT_TO_FIXED(3.0), CONVERT_TO_FIXED(number),
                                           CONVERT_TO_FIXED(4.6),
                                           CONVERT_TO_FIXED(1.0 * std::pow(10, -7)), CONVERT_TO_FIXED(pressure),
                                           CONVERT_TO_FIXED(1.0 * std::pow(10, -5)));
        return result;
    } else if (value >= 4.6 && value <= 6.2) {

        auto number = 4.6 + static_cast<float>(rand()) * static_cast<float>(value - 4.6) / RAND_MAX;
        auto pressure = calc_pressure_pascal(number);
        result = newton_poly_interpolation(CONVERT_TO_FIXED(value), CONVERT_TO_FIXED(4.6), CONVERT_TO_FIXED(number),
                                           CONVERT_TO_FIXED(6.2),
                                           CONVERT_TO_FIXED(1.0 * std::pow(10, -5)), CONVERT_TO_FIXED(pressure),
                                           CONVERT_TO_FIXED(1.0 * std::pow(10, -3)));
        return result;
    } else if (value >= 6.2 && value <= 7.8) {
        auto number = 4.6 + static_cast<float>(rand()) * static_cast<float>(value - 4.6) / RAND_MAX;
        auto pressure = calc_pressure_pascal(number);
        result = newton_poly_interpolation(CONVERT_TO_FIXED(value), CONVERT_TO_FIXED(6.2), CONVERT_TO_FIXED(number),
                                           CONVERT_TO_FIXED(7.8),
                                           CONVERT_TO_FIXED(1.0 * std::pow(10, -3)), CONVERT_TO_FIXED(pressure),
                                           CONVERT_TO_FIXED(0.1));
        return result;
    } else if (value >= 7.0 && value <= 8.6) {
        auto number = 4.6 + static_cast<float>(rand()) * static_cast<float>(value - 4.6) / RAND_MAX;
        auto pressure = calc_pressure_pascal(number);
        result = newton_poly_interpolation(CONVERT_TO_FIXED(value), CONVERT_TO_FIXED(7.0), CONVERT_TO_FIXED(number),
                                           CONVERT_TO_FIXED(8.6),
                                           CONVERT_TO_FIXED(1.0 * std::pow(10, -2)), CONVERT_TO_FIXED(pressure),
                                           CONVERT_TO_FIXED(1.0));
        return result;
    } else {
        std::cout << "The value is either underrange, there is a sensor error or it is overrange\n";
        return result;
    }

}

void fixed_point::run() {

    std::cout << "IKR 270 Gauge\n";
    int ADC_value = 0;
    int choice = 0;
    std::cout << "Enter the value of your ADC value:\n";
    std::cin >> ADC_value;
    std::cout << "Choose your unit for the pressure: \n 1-Pa  2-MBar (Enter the number):";
    std::cin >> choice;

    float sensor_output = ADC_to_sensor(ADC_value);
    float resulting_pressure = CONVERT_TO_FLOAT(calculating_pressure(sensor_output));


    switch (choice) {
        case 1:
            std::cout << "The corresponding pressure value is:\n" << resulting_pressure << " Pa.";
        case 2:
            std::cout << "The corresponding pressure value is:\n" << resulting_pressure * 0.01 << " Mbar.";
        default:
            std::cout << "Try again.";
    }


}