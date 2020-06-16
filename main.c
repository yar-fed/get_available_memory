#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long findNumber(char *s);
void test(long size);

int main(void)
{
    FILE *meminfo = fopen("/proc/meminfo", "r");
    char buffFree[64];
    char buffAvailable[64];
    char buffCached[64];
    fgets(buffFree, 64, meminfo);
    fgets(buffFree, 64, meminfo);
    fgets(buffAvailable, 64, meminfo);
    fgets(buffCached, 64, meminfo);
    fgets(buffCached, 64, meminfo);
    fclose(meminfo);

    long memFree = findNumber(buffFree);
    long memAvailable = findNumber(buffAvailable);
    long memCached = findNumber(buffCached);
    printf("%ld kB free\n", memFree);
    test(memFree);
    printf("\n%ld kB available(kernel estimate)\n", memAvailable);
    test(memAvailable);
    printf("\n%ld kB cached + free\n", memCached + memFree);
    test(memCached+memFree);

    return 0;
}

long findNumber(char *s)
{
    while (*s < 48 || *s > 57)
        s++;
    return strtol(s, NULL, 10);
}

void test(long size)
{
    void *testPtr = malloc(size*1024 + 1024*1024);
    if (testPtr == NULL) {
        printf("Test %ld*1024 + 1024*1024 > %ld kB failed\n", size, size);
    } else {
        free(testPtr);
        printf("Test %ld*1024 + 1024*1024 > %ld kB success\n", size, size);
    }

    testPtr = malloc(size*1024);
    if (testPtr == NULL) {
        printf("Test %ld*1024 == %ld kB failed\n", size, size);
    } else {
        free(testPtr);
        printf("Test %ld*1024 == %ld kB success\n", size, size);
    }
}
