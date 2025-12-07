#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#define N 137
char map[N][N];
int neighb_map[N][N];
int offset[] = { 1, -1, N, -N, N+1, N-1, -N+1, -N-1 };
int x, y;

int compute_neighb(int i, int j) {
    neighb_map[i][j] = 0;
    for (int k = 0; k < 8; k++) {
        if (map[i][j+offset[k]] == '@')
            neighb_map[i][j]++;
    }
    return neighb_map[i][j];
}

int remove_paper(int i, int j) {
    if (map[i][j] != '@') return 0;
    if (neighb_map[i][j] >= 4) return 0;
    map[i][j] = 'x';
    for (int k = 0; k < 8; k++)
        neighb_map[i][j+offset[k]]--;
    int sum = 0;
    for (int k = 0; k < 8; k++)
        sum += remove_paper(i, j+offset[k]);
    return 1 + sum;
}

int main() {
    for (int i = 0; i < N*N; i++)
        neighb_map[0][i] = -1;
    x = 0; y = 1;
    while (scanf("%s\n", map[y]+1) != EOF) {
        map[y][0] = 0;
        y++;
    }
    y++;
    x = strlen(map[1]+1) + 2;
    for (int i = 0; i < x; i++)
        map[0][i] = map[y-1][i] = 0;

    int output1 = 0;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (map[i][j] != '@') continue;
            if (compute_neighb(i, j) < 4)
                output1++;
        }
    }
    printf("part1 : %d\n", output1);

    int output2 = 0;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++)
            output2 += remove_paper(i, j);
    }
    printf("part2 : %d\n", output2);

    return 0;
}
