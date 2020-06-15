#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long findNumber(char *s);
int main(void)
{
    FILE *meminfo = fopen("/proc/meminfo", "r");
    char buff[64];
    fgets(buff, 64, meminfo);
    fgets(buff, 64, meminfo);
    fclose(meminfo);
    long int a;
    printf("%ld kB\n", findNumber(buff));

    return 0;
}

long findNumber(char *s)
{
    while (*s < 48 || *s > 57)
        s++;
    return strtol(s, NULL, 10);
}