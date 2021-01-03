#include <stdio.h>

int main(int argc, char **argv)
{
    printf("running...\n");

    int i;
    for(i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    printf("done");
    return 0;
}
