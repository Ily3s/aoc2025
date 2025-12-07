#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

typedef struct {
    int64_t min, max;
} range;

int comp_range(const void* a, const void* b) {
    return ((const range*)a)->min < ((const range*)b)->min ? -1 : 1;
}
int comp_fruits(const void* a, const void* b) {
    return *(const int64_t*)a < *(const int64_t*)b ? -1 : 1;
}

range ranges[1000];
int64_t fruit_ids[2000];
int ranges_nb, fruits_nb;

void parse_input() {
    ranges_nb = fruits_nb = 0;
    int64_t min, max;
    while (scanf("%" SCNd64 "-%" SCNd64 "\n", &min, &max) == 2) {
        ranges[ranges_nb].min = min;
        ranges[ranges_nb++].max = max;
    }
    do {
        fruit_ids[fruits_nb++] = min;
    } while (scanf("%" SCNd64 "\n", &min) != EOF);
}

int main() {
    parse_input();
    qsort(ranges, ranges_nb, sizeof(range), comp_range);
    qsort(fruit_ids, fruits_nb, 8, comp_fruits);

    int fresh = 0;
    int i_fruits = 0, i_ranges = 0;
    while (i_fruits < fruits_nb && i_ranges < ranges_nb) {
        int64_t fruit = fruit_ids[i_fruits];
        range range = ranges[i_ranges];
        if (fruit < range.min) {
            i_fruits++;
            continue;
        }
        if (fruit > range.max) {
            i_ranges++;
            continue;
        }
        fresh++;
        i_fruits++;
    }
    printf("part1: %d\n", fresh);

    int64_t maxfresh = 0;
    range curr_range = ranges[0];

    for (int i = 1; i < ranges_nb; i++) {
        if (ranges[i].min > curr_range.max) {
            maxfresh += curr_range.max - curr_range.min + 1;
            curr_range = ranges[i];
            continue;
        }
        if(ranges[i].max > curr_range.max)
            curr_range.max = ranges[i].max;
    }
    maxfresh += curr_range.max - curr_range.min + 1;

    printf("part2: %" PRId64 "\n", maxfresh);

    return 0;
}
