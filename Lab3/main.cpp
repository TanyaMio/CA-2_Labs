#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "calculator.h"

static int help_flag;
static int int_flag;
static int float_flag;
static int const_flag;
static int list_flag;
static int add_flag;
static int sub_flag;
static int div_flag;
static int mul_flag;
static std::string help_message = "List of options:\n--help -h\n    Displays this message.\n"
                            "--integer -i\n    Makes calculation results displayed as integer.\n"
                            "--float -f\n    Makes calculation results displayed as float.\n"
                            "--constant -C\n    Sets a constant.\n"
                            "--list -L\n    Sets a list.\n"
                            "--add -A\n    Adds all the given values.\n"
                            "--subtract -S\n    Subtracts all the given values from the first one.\n"
                            "--divide -D\n    Sequentially divides all the values.\n"
                            "--multiply -M\n    Multiplies all the values.\n\n";
static std::string const_val;
static std::string list_val;
static std::string add_val;
static std::string sub_val;
static std::string div_val;
static std::string mul_val;

int main(int argc, char **argv)
{
    Calculator calculator;

    int curr_opt;
    static struct option long_options[] = {
            {"help", no_argument, 0, 'h'},
            {"integer", no_argument, 0, 'i'},
            {"float", no_argument, 0, 'f'},
            {"constant", required_argument, 0, 'C'},
            {"list", required_argument, 0, 'L'},
            {"add", required_argument, 0, 'A'},
            {"subtract", required_argument, 0, 'S'},
            {"divide", required_argument, 0, 'D'},
            {"multiply", required_argument, 0, 'M'},
            {0,0,0,0}
    };
    int option_index = 0;

    while((curr_opt = getopt_long(argc, argv, "hifC:L:A:S:D:M:", long_options, &option_index)) != -1) {

        switch (curr_opt) {
            case 'h':
                if(!help_flag) {
                    puts("Found -h key.");
                    help_flag = 1;
                }
                break;
            case 'i':
                if(!int_flag){
                    puts("Found -i key.");
                    int_flag = 1;
                }
                break;
            case 'f':
                if(!float_flag){
                    puts("Found -f key.");
                    float_flag = 1;
                }
                break;
            case 'C':
                if(!const_flag){
                    printf("Found -C key with value '%s'\n", optarg);
                    const_val = optarg;
                    const_flag = 1;
                }
                break;
            case 'L':
                if(!list_flag) {
                    printf("Found -L key with value '%s'\n", optarg);
                    list_val = optarg;
                    list_flag = 1;
                }
                break;
            case 'A':
                if(!add_flag){
                    printf("Found -A key with value '%s'\n", optarg);
                    add_val = optarg;
                    add_flag = 1;
                }
                break;
            case 'S':
                if(!sub_flag){
                    printf("option -S with value '%s'\n", optarg);
                    sub_val = optarg;
                    sub_flag = 1;
                }
                break;
            case 'D':
                if(!div_flag){
                    printf("option -D with value '%s'\n", optarg);
                    div_val = optarg;
                    div_flag = 1;
                }
                break;
            case 'M':
                if(!mul_flag){
                    printf("option -M with value '%s'\n", optarg);
                    mul_val = optarg;
                    mul_flag = 1;
                }
                break;
            case '?':
                break;
            default:
                abort();
        }
    }

    if (help_flag)
        std::cout << help_message;
    if(int_flag && !float_flag)
        puts("Results will be displayed as integers.");
    else
        puts("Results will be displayed as floats.");
    if(const_flag){
        if(int_flag && !float_flag)
            printf("Constant value given is %i\n", (int)std::stod(const_val));
        else
            printf("Constant value given is %f\n", std::stod(const_val));
    }
    if(list_flag){
        puts("List of values given is [ ");
        size_t pos;
        while ((pos = list_val.find(",")) != std::string::npos) {
            if(int_flag && !float_flag)
                printf("%i, ", (int)std::stod(list_val.substr(0, pos)));
            else
                printf("%f, ", std::stod(list_val.substr(0, pos)));
            list_val.erase(0, pos + 1);
        }
        std::cout << list_val << " ]\n";
    }
    if(add_flag){
        double res = 0;
        size_t pos;
        while ((pos = add_val.find(",")) != std::string::npos) {
            res = calculator.Add(res, std::stod(add_val.substr(0, pos)));
            add_val.erase(0, pos + 1);
        }
        res = calculator.Add(res, std::stod(add_val));
        if(int_flag && !float_flag)
            printf("Addition result is %i\n", (int)res);
        else
            printf("Addition result is %f\n", res);
    }
    if(sub_flag){
        bool first = true;
        double res = 0;
        size_t pos;
        while ((pos = sub_val.find(",")) != std::string::npos) {
            if(first){
                res = std::stod(sub_val.substr(0, pos));
                first = false;
            } else {
                res = calculator.Sub(res, std::stod(sub_val.substr(0, pos)));
            }
            sub_val.erase(0, pos + 1);
        }
        res = calculator.Sub(res, std::stod(sub_val));
        if(int_flag && !float_flag)
            printf("Subtraction result is %i\n", (int)res);
        else
            printf("Subtraction result is %f\n", res);
    }
    if(div_flag){
        bool first = true;
        double res = 0;
        size_t pos;
        while ((pos = div_val.find(",")) != std::string::npos) {
            if(first){
                res = std::stod(div_val.substr(0, pos));
                first = false;
            } else {
                res = calculator.Div(res, std::stod(div_val.substr(0, pos)));
            }
            div_val.erase(0, pos + 1);
        }
        res = calculator.Div(res, std::stod(div_val));
        if(int_flag && !float_flag)
            printf("Division result is %i\n", (int)res);
        else
            printf("Division result is %f\n", res);
    }
    if(mul_flag){
        double res = 1;
        size_t pos;
        while ((pos = mul_val.find(",")) != std::string::npos) {
            res = calculator.Mul(res, std::stod(mul_val.substr(0, pos)));
            mul_val.erase(0, pos + 1);
        }
        res = calculator.Mul(res, std::stod(mul_val));
        if(int_flag && !float_flag)
            printf("Multiplication result is %i\n", (int)res);
        else
            printf("Multiplication result is %f\n", res);
    }

    return 0;
}
