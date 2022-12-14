#include <iostream>
#include <math.h>
#include <random>
#include <ctime>

#define FIXED_BITS        64
#define FIXED_WBITS       40
#define FIXED_FBITS       24
#define MAKE_FIXED(a)     (int64_t)((a*(1 << FIXED_FBITS)))
#define MAKE_FLOAT(a)     (double )((double)a/(double) (1<< FIXED_FBITS))


static int64_t Mul(int64_t a, int64_t b) {
    return (((int64_t) a * (int64_t) b) >> FIXED_FBITS);
}

static int64_t Div(int64_t a, int64_t b) {
    return ((int64_t) a << FIXED_FBITS / (int64_t) b);
}

static int64_t Add(int64_t a, int64_t b) {
    return (((int64_t) a + (int64_t) b));
}

static int64_t Sub(int64_t a, int64_t b) {
    return (((int64_t) a - (int64_t) b));
}
template <typename T>
T ADC_to_sensor(T sensor_value) {
    auto result= (sensor_value * 10 / 1023);
    return result;
}

template <typename T>
T calc_pressure_pascal(T value) {
    T pressure;
    T power;
    power = 1.25 * value - 10.75;
    pressure = std::pow(10, power);
    return pressure;
}

static int64_t
newton_poly_interpolation(int64_t x, int64_t x1, int64_t x2, int64_t x3, int64_t f1, int64_t f2, int64_t f3) {
    int64_t b1 = f1;
    int64_t b2 = Div(Sub(f2, f1), Sub(x2, x1));
    int64_t b3 = Div(Sub(Div(Sub(f3, f2), Sub(x3, x2)), Div(Sub(f2, f1), Sub(x2, x1))), Sub(x3, x1));
    int64_t result = Add(b1, Add(Mul(b2, Sub(x, x1)), Mul(b3, Mul(Sub(x, x1), Sub(x, x2)))));
    return result;
}

template <typename T>
int64_t calculating_pressure(T value) {
    int64_t result = 0;
    if (value >= 1.96 && value <= 3.0) {
        auto number = 1.96 + static_cast<float>(rand()) * static_cast<float>(value - 1.96) / RAND_MAX;
        auto pressure = calc_pressure_pascal(number);
        result = newton_poly_interpolation(MAKE_FIXED(value), MAKE_FIXED(1.96), MAKE_FIXED(number), MAKE_FIXED(3.0),
                                           MAKE_FIXED(5.0 * std::pow(10, -9)), MAKE_FIXED(pressure),
                                           MAKE_FIXED(1.0 * std::pow(10, -7)));
        return result;
    } else if (value >= 3.0 && value <= 4.6) {
        auto number = 3.0 + static_cast<float>(rand()) * static_cast<float>(value - 4.6) / RAND_MAX;
        auto pressure = calc_pressure_pascal(number);
        result = newton_poly_interpolation(MAKE_FIXED(value), MAKE_FIXED(3.0), MAKE_FIXED(number), MAKE_FIXED(4.6),
                                           MAKE_FIXED(1.0 * std::pow(10, -7)), MAKE_FIXED(pressure),
                                           MAKE_FIXED(1.0 * std::pow(10, -5)));
        return result;
    } else if (value >= 4.6 && value <= 6.2) {

        auto number = 4.6 + static_cast<float>(rand()) * static_cast<float>(value - 4.6) / RAND_MAX;
        auto pressure = calc_pressure_pascal(number);
        result = newton_poly_interpolation(MAKE_FIXED(value), MAKE_FIXED(4.6), MAKE_FIXED(number), MAKE_FIXED(6.2),
                                           MAKE_FIXED(1.0 * std::pow(10, -5)), MAKE_FIXED(pressure),
                                           MAKE_FIXED(1.0 * std::pow(10, -3)));
        return result;
    } else if (value >= 6.2 && value <= 7.8) {
        auto number = 4.6 + static_cast<float>(rand()) * static_cast<float>(value - 4.6) / RAND_MAX;
        auto pressure = calc_pressure_pascal(number);
        result = newton_poly_interpolation(MAKE_FIXED(value), MAKE_FIXED(6.2), MAKE_FIXED(number), MAKE_FIXED(7.8),
                                           MAKE_FIXED(1.0 * std::pow(10, -3)), MAKE_FIXED(pressure),
                                           MAKE_FIXED(0.1));
        return result;
    } else if (value >= 7.0 && value <= 8.6) {
        auto number = 4.6 + static_cast<float>(rand()) * static_cast<float>(value - 4.6) / RAND_MAX;
        auto pressure = calc_pressure_pascal(number);
        result = newton_poly_interpolation(MAKE_FIXED(value), MAKE_FIXED(7.0), MAKE_FIXED(number), MAKE_FIXED(8.6),
                                           MAKE_FIXED(1.0 * std::pow(10, -2)), MAKE_FIXED(pressure),
                                           MAKE_FIXED(1.0));
        return result;
    } else {
        std::cout << "The value is either underrange, there is a sensor error or it is overrange\n";
        return result;
    }

}

void Menu() {
    int ADC_value = 0;
    int choice = 0;
    std::cout << "Enter the value of your ADC value:\n";
    std::cin >> ADC_value;
    std::cout << "Choose your unit for the pressure: \n 1-Pa  2-MBar (Enter the number)";
    std::cin >> choice;
    float sensor_output = ADC_to_sensor(ADC_value);
    float resulting_pressure = MAKE_FLOAT(calculating_pressure(sensor_output));
    if (choice == 1) {
        std::cout << "The corresponding pressure value is:\n" << resulting_pressure << " Pa";
    } else if (choice == 2) {
        std::cout << "The corresponding pressure value is:\n" << resulting_pressure * 0.01 << " Mbar";
    } else {
        throw std::invalid_argument("Wrong choice number");
    }
}

int main() {
    Menu();
    return 0;
}

