#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define NPTS 1000

struct Point {
    int x, y, z, r;
};
typedef struct Point Point;

int mdist(int x, int x2, int y, int y2, int z, int z2) {return abs(x - x2) + abs(y - y2) + abs(z - z2);}

int main()
{
    int i, j, k, n, index, range, inrange, div, high;
    char line[100];
    // bounds are fixed based on the approximate first 2 digits of the min and max values
    int bound[6] = {-20, 100, -20, 100, -20, 100}, pos[3] = {0};
    Point p[NPTS], pdiv[NPTS];

    i = index = range = 0;
    while (fgets(line, sizeof(line), stdin) != NULL)
    {
        sscanf(line, "pos=<%d,%d,%d>, r=%d\n", &p[i].x, &p[i].y, &p[i].z, &p[i].r);
        if (p[i].r > range)
        {
            range = p[i].r;
            index = i;
        }
        i++;
    }

    inrange = 0;
    for (i = 0; i < NPTS; i++)
    {
        if (mdist(p[i].x, p[index].x, p[i].y, p[index].y, p[i].z, p[index].z) <= range) {inrange++;}
    }
    printf("Part 1: %d\n", inrange);

    // finds the best point by looking in a subdivision first and then checking around that point
    // constantly expanding the range around that point by multiples of 10
    for (div = 1000000; div != 0; div /= 10)
    {
        high = 0;
        for (i = 0; i < NPTS; i++)
        {
            pdiv[i].x = p[i].x / div;
            pdiv[i].y = p[i].y / div;
            pdiv[i].z = p[i].z / div;
            pdiv[i].r = p[i].r / div;
            // edge case
            if (div > 1) {pdiv[i].r++;}
        }

        for (i = bound[0]; i < bound[1]; i++)
        {
            for (j = bound[2]; j < bound[3]; j++)
            {
                for (k = bound[4]; k < bound[5]; k++)
                {
                    inrange = 0;
                    for (n = 0; n < NPTS; n++)
                    {
                        if (mdist(i, pdiv[n].x, j, pdiv[n].y, k, pdiv[n].z) <= pdiv[n].r) {inrange++;}
                    }
                    if (inrange > high)
                    {
                        high = inrange;
                        pos[0] = i;
                        pos[1] = j;
                        pos[2] = k;
                    }
                }
            }
        }

        // change bounds
        printf("[%d %d %d]\n", pos[0], pos[1], pos[2]);
        for (i = 0; i < 6; i++)
        {
            bound[i] = pos[i / 2] * 10 + ((2 * (i % 2)) - 1) * 100;
            printf("%d%s", bound[i], i != 5 ? ", " : "");
        }
        printf("\n");
    }

    printf("Part 2: %d dist in range of %d points\n", abs(pos[0]) + abs(pos[1]) + abs(pos[2]), high);

    return 0;
}
