#include <stdio.h>
#include <stdlib.h>

int i_square(int n);
double square(double x);



int main()
{
    int (*fp)(); // pointer to function that returns int
    double (*fptr)(); //

    /* Can assign pointers to functions because
       calling a function references the function - is a pointer
       to the function
    */

    fp = i_square;

    fptr = square;

    // accessing the functions
    m = (*fp)(n);
    y = (*fptr)(x);


    return 0;
}
