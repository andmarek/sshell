#include <stdlib.h>
#include <stdio.h>

/* We do not need to make it a
   typedef, but it is good practice */
typedef struct book {
    char *author;
    char *title;
    int num_pages;
    int year_pub;
} book_t;


int main()
{
    book_t *b = malloc(sizeof(book_t));
    (*b).title = "A Tale of Two Cities";
    b->author = "Andrew Marek"; // This is the same thing
    printf("%s, %s",(*b).title, b->author);
    return 0;
}



