#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

int64_t greatest(int64_t a, int64_t b) {
  return a < b ? b : a;
}

int main() {
  char line[101];
  int64_t output = 0;
  while (scanf("%s\n", line) != EOF) {
    int64_t len = strlen(line);
    int64_t PAWA = 0;
    int64_t max, max_index = -1;
    for (int64_t k = 0; k < 12; k++) {
      max = 0;
      int64_t max_index_save = max_index;
      for (int i = len-12+k; i > max_index_save; i--) {
        max = greatest(max, line[i] - '0');
        max_index = max == line[i] - '0' ? i : max_index;
      }
      PAWA = PAWA*10 + max;
    }
    output += PAWA;
  }
  printf("%" PRId64 "\n", output);
}
