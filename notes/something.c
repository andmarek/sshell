#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
    int i = 5; /* Instantiates a variable and assigns value */

    int j; /* Instantiates variable, but doesn't assign */
    j = 5; /* Initializes variable */

    int x;
    x = j - i; /* Arithmetic.  0 - 5 = -5 */

    printf("i: %d, j: %d, abs(x): %d\n", i, j, abs_val(x));
    /* Returning 0 = success.  It's a formality, and you might run
       into programs returning something else */
    return 0;
}

