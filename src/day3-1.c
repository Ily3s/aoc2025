#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int greatest(int a, int b) {
  return a < b ? b : a;
}

int main() {
  char line[101];
  int output = 0;
  while (scanf("%s\n", line) != EOF) {
    int len = strlen(line);
    int max1 = 0, max_index;
    for (int i = len-2; i >= 0; i--) {
      max1 = greatest(max1, line[i] - '0');
      max_index = max1 == line[i] - '0' ? i : max_index;
    }
    int max2 = 0;
    for (int i = max_index + 1; i < len; i++)
      max2 = greatest(max2, line[i] - '0');
    output += max1*10+max2;
  }
  printf("%d\n", output);
  
}
