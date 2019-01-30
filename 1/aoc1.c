#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LINE 20
#define IN_LEN   1200
#define TOLR     1000

/**
 * Prints the sum of the values after one iteration over the summation list input1.txt
 * and also prints the first duplicate value from iterating over the list multiple times.
 *
 * Records the maximum sum in the list as a pivot value with some additional tolerance TOLR.
 */
int main()
{
    int i, sum, n, max, freqs[IN_LEN] = {0};
    char curline[MAX_LINE], *sumlist;

    sum = n = max = 0;
    while (fgets(curline, sizeof(curline), stdin))
    {
        freqs[n] = atoi(curline);
        if (abs(freqs[n]) > max) {max = abs(freqs[n]);}
        sum += freqs[n++];
    }
    printf("Sum of first iteration: %d\n", sum);

    max += TOLR;
    sumlist = calloc(2 * max, sizeof(sumlist));
    if (!sumlist) {printf("Not enough memory\n"); return 1;}

    sum = 0;
    while (1)
    {
        for (i = 0; i < n; i++)
        {
            sum += freqs[i];
            if (sumlist[sum + max])
            {
                printf("Duplicate: %d\n", sum);
                goto end;
            }
            sumlist[sum + max] = 1;
        }
    }

end:free(sumlist);
    return 0;
}
