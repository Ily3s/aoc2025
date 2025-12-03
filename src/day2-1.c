#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>

int digits(int64_t nb) {
  return nb ? 1+digits(nb/10) : 0;
}

int64_t expo(int64_t x, int n) {
  if (n == 0) return 1;
  int64_t rec = expo(x, n/2);
  return n%2 ? x*rec*rec : rec*rec;
}

int64_t greatest(int64_t a, int64_t b) {
  return a < b ? b : a;
}

int main() {
  int64_t output = 0;
  int64_t min, max;
  while(scanf("%" SCNd64 "-%" SCNd64, &min, &max) != EOF) {
    scanf(",");

    int digit_base = digits(min)/2 + digits(min)%2;
    int64_t base = expo(10, digit_base);
    int64_t candidate = (digits(min)%2 ? base/10 : min/base + (min%base > min/base)) * (base+1);

    while (candidate <= max) {
      while (candidate <= max && digits(candidate) == digit_base*2) {
        output += candidate;
        candidate += base+1;
      }
      digit_base++;
      base *= 10;
      candidate = base/10 * (base+1);
    }
  }
  printf("%" PRId64 "\n", output);

  return 0;
}
