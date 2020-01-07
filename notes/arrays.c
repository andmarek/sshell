#include <stdlib.h>
#include <stdio.h>

int main()
{
    // type array_name [arraysize];
    int a[50];
    int b[5] = {1, 2, 3, 4, 5};
    int *c; /* Effectively the same thing,
             But you're not specifying a size.
             We can use malloc for this */

    c = (int *) malloc(sizeof (int) * 50);

    a[0] = 5;
    c[0] = 6; /* Arrays are really just pointers to the first element
              in that contiguous block of "n" elements */
    printf("a[0] %d, c[0] %d\n", a[0], c[0]);
    return 0;
}


