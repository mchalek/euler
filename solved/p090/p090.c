#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

void enum_cubes(int face, uint16_t current, int last_face, int *ncubes, uint16_t cubes[])
{
    if(face == 6) {
        cubes[(*ncubes)++] = current;
        return;
    }

    int i;
    for(i = (1 + last_face); i < 10; i++) {
        enum_cubes(1 + face, current | (1 << i), i, ncubes, cubes);
    }
}

bool satisfied(uint32_t target, uint16_t c0, uint16_t c1)
{
    if(((target >> 16) & c0) && (target & c1))
        return true;

    if(((target >> 16) & c1) && (target & c0))
        return true;

    return false;
}

bool test(uint16_t c0, uint16_t c1)
{
    uint32_t s1 = ((1 << 0) << 16) | (1 << 1);
    if(!satisfied(s1, c0, c1))
        return false;
    
    uint32_t s4 = ((1 << 0) << 16) | (1 << 4);
    if(!satisfied(s4, c0, c1))
        return false;
    
    uint32_t s9a = ((1 << 0) << 16) | (1 << 9);
    uint32_t s9b = ((1 << 0) << 16) | (1 << 6);
    if(!(satisfied(s9a, c0, c1) | satisfied(s9b, c0, c1)))
        return false;
    
    uint32_t s16a = ((1 << 1) << 16) | (1 << 6);
    uint32_t s16b = ((1 << 1) << 16) | (1 << 9);
    if(!(satisfied(s16a, c0, c1) | satisfied(s16b, c0, c1)))
        return false;
    
    uint32_t s25 = ((1 << 2) << 16) | (1 << 5);
    if(!satisfied(s25, c0, c1))
        return false;
    
    uint32_t s36a = ((1 << 3) << 16) | (1 << 6);
    uint32_t s36b = ((1 << 3) << 16) | (1 << 9);
    if(!(satisfied(s36a, c0, c1) | satisfied(s36b, c0, c1)))
        return false;
    
    uint32_t s49a = ((1 << 4) << 16) | (1 << 9);
    uint32_t s49b = ((1 << 4) << 16) | (1 << 6);
    if(!(satisfied(s49a, c0, c1) | satisfied(s49b, c0, c1)))
        return false;

    uint32_t s64a = ((1 << 6) << 16) | (1 << 4);
    uint32_t s64b = ((1 << 9) << 16) | (1 << 4);
    if(!(satisfied(s64a, c0, c1) | satisfied(s64b, c0, c1)))
        return false;

    uint32_t s81 = ((1 << 8) << 16) | (1 << 1);
    if(!satisfied(s81, c0, c1))
        return false;

    return true;
}

int main()
{
    int ncubes = 0;
    uint16_t cubes[210];

    enum_cubes(0, 0, -1, &ncubes, cubes);

    printf("found %d cubes\n", ncubes);

    int i, j;
    int count = 0;
    for(i = 0; i < ncubes; i++) {
        for(j = i; j < ncubes; j++) {
            count += test(cubes[i], cubes[j]);
        }
    }

    printf("%d arrangements\n", count);

    return 0;
}
