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

    for (int rep = 2; rep <= digits(max); rep++) {

      int digit_min = digits(min);
      int digit_base = digit_min/rep + !!(digit_min%rep);
      int64_t base = expo(10, digit_base);
      int64_t curr_base = 1;
      int64_t somme_bases = 0;
      for (int k = 1; k <= rep; k++) {
        somme_bases += curr_base;
        curr_base *= base;
      }
      int64_t min_front = min/(curr_base/base);
      int64_t candidate = (digit_min%rep ? base/10 : min_front) * somme_bases;
      if (candidate < min) candidate += somme_bases;

      while (candidate <= max) {
        while (candidate <= max && digits(candidate) == digit_base*rep) {
          int dig_candidate = digits(candidate);
          for (int prev_rep = rep-1; prev_rep >= 2; prev_rep--) {
            if (dig_candidate%prev_rep != 0) continue;
            int64_t prev_digits_base = dig_candidate/prev_rep;
            int64_t prev_base = expo(10, prev_digits_base);
            int64_t candidate_cpy = candidate;
            int64_t candidate_portion = candidate_cpy%prev_base;
            while (candidate_cpy /= prev_base) {
              if (candidate_cpy%prev_base != candidate_portion)
                goto succeed;
            }
            goto fail;
          succeed:
          }
          output += candidate;
        fail:
          candidate += somme_bases;
        }
        digit_base++;
        base *= 10;
        somme_bases *= expo(10, rep);
        candidate = base/10 * somme_bases;
      }

    }
  }
  printf("%" PRId64 "\n", output);

  return 0;
}

