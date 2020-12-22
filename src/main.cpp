#include <tchar.h>
#include <iostream>

extern int print_half_to_float_lookup_table();
extern int print_sign_and_exponent_conversion_lookup_table();

int _tmain(int, _TCHAR* []) {
    print_sign_and_exponent_conversion_lookup_table();

    std::cout << std::endl;
    
    print_half_to_float_lookup_table();
    return 0;
}
