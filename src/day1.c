#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int domain(int a, int n) {
  return a<0 ? (a+1)/n-1 : a/n;
}

int diff(int a, int b) {
  return a-b < 0 ? b-a : a-b;
}

int main(int argc, char** argv) {
  if (argc != 2) {
  wrong_args:
    fprintf(stderr, "usage: day part\n");
    return 1;
  }
  bool part2;
  if (!strcmp(argv[1], "1"))
    part2 = false;
  else if (!strcmp(argv[1], "2"))
    part2 = true;
  else
    goto wrong_args;

  char instr;
  int ampl;
  int dial = 50;
  int output = 0;
  while (scanf("%c%d\n", &instr, &ampl) != EOF) {
    int new_dial = dial + ((instr == 'R')*2-1)*ampl;
    if (part2)
      output += diff(domain(new_dial, 100), domain(dial, 100)) + (instr=='L')*(new_dial%100==0) - (instr=='L')*(dial%100==0);
    else
      output += new_dial%100 == 0;
    dial = new_dial;
  }
  printf("%d\n", output);
  return 0;
}
