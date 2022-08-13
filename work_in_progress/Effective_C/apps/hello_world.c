#include <stdio.h>
#include <stdlib.h>

int main(void) {
    if(EOF == puts("Hello, world!"))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;

}
