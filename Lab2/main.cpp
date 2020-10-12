#include <iostream>
#include "calculator.h"

int main()
{
    Calculator calculator;

    double a = 7.4;
    int b = 99;

    std::cout << "a + b = " << calculator.Add(a, b) << std::endl;
    std::cout << "a - b = " << calculator.Sub(a, b) << std::endl;
    std::cout << "a * b = " << calculator.Mul(a, b) << std::endl;
    std::cout << "a / b = " << calculator.Div(a, b) << std::endl;

    return 0;
}