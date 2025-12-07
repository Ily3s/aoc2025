#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

int problems_nb;
int64_t problems[4000][10];
char problems_ops[4000];

void parse_input() {
  char input[10][4000];
  int line_nb = 0;
  while (scanf("%3999[^\n]", input[line_nb++]) != EOF)
    fgetc(stdin);
  line_nb--;
  for (int j = 0, col = 0; input[0][j]; j++, col++) {
    int64_t curr_nb = 0;
    bool is_nb = false;
    for (int i = 0; i < line_nb - 1; i++) {
      if (input[i][j] != ' ') {
        is_nb = true;
        curr_nb = curr_nb * 10 + input[i][j] - '0';
      }
    }
    if (!is_nb) {
      problems_nb++;
      col = -1;
      continue;
    }
    problems[problems_nb][col+1] = curr_nb;
    problems[problems_nb][0] = col+1;
  }
  problems_nb++;
  char* line  = input[line_nb-1];
  for (int k = 0, i = 0; line[k] != '\0'; k++) {
    if (line[k] == '+' || line[k] == '*')
      problems_ops[i++] = line[k];
  }
}

int main() {
  parse_input();
  int64_t output = 0;
  for (int i = 0; i < problems_nb; i++) {
    int problems_size = problems[i][0];
    int64_t answer = problems_ops[i] == '+' ? 0 : 1;
    for (int j = 1; j < problems_size+1; j++) {
      if (problems_ops[i] == '+')
        answer += problems[i][j];
      else // problems_ops[i] == '*'
        answer *= problems[i][j];
    }
    output += answer;
  }
  printf("%" PRId64 "\n", output);
  return 0;
}
