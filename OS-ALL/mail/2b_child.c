#include <stdio.h>
int main(int argc, char *argv[])
{
    printf("Reversed Array:\n");
    for (int i = argc - 1; i > 0; i--)
    {
        printf("%s\n", argv[i]);
    }
    return 0;
}