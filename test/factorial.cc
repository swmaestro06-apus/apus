#include "factorial.h"

// Returns the factorial value of a specified input integer.
int factorial (int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result = result * i;
    }
    return result;
}
