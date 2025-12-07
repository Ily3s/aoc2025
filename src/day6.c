#include <stdio.h>
#include <inttypes.h>

int problems_nb, problems_size;
int64_t problems[4000][10];
char problems_ops[4000];

void parse_input() {
    problems_nb = problems_size = 0;
    char line[4000];
    while (scanf("%3999[^\n]", line) != EOF) {
        int i = 0;
        char* line_stream = line;
        int off;
        while (sscanf(line_stream, "%" SCNd64 "%n", &problems[i++][problems_size], &off) == 1)
            line_stream += off;
        if (--i == 0) break;
        problems_size++;
        problems_nb = i;
        fgetc(stdin);
    }
    for (int k = 0, i = 0; line[k] != '\0'; k++) {
        if (line[k] == '+' || line[k] == '*')
            problems_ops[i++] = line[k];
    }
}

int main() {
    parse_input();
    int64_t output = 0;
    for (int i = 0; i < problems_nb; i++) {
        int64_t answer = problems_ops[i] == '+' ? 0 : 1;
        for (int j = 0; j < problems_size; j++) {
            if (problems_ops[i] == '+')
                answer += problems[i][j];
            else // problems_ops[i] == '*'
                answer *= problems[i][j];
        }
        output += answer;
    }
    printf("%" PRId64 "\n", output);
}
