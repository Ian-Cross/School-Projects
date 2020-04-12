#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE_LENGTH 100

void eCalculation(int n, FILE *f) {
  int m = 4;
  double test = (n + 1) * 2.30258509;

  while (1) {
    m += 1;
    if (m * (log(m) - 1.0) + 0.5 * log(6.2831852 * m) > test)
      break;
  }

  int i, j, carry, temp;
  int coef[m];

  for (j = 2; j <= m; j++)
    coef[j] = 1;

  fprintf(f, "%d.", 2);
  for (i = 1; i <= m; i++) {
    carry = 0;
    for (j = m; j >= 2; j--) {
      temp = coef[j] * 10 + carry;
      carry = temp / j;
      coef[j] = temp - carry * j;
    }
    fprintf(f, "%d", carry);
  }
}

int main(int argc, char const *argv[]) {
  printf("Welcome to Euler e Estimation\n");
  printf("Please enter a file for output: \n");

  char filename[FILE_LENGTH];
  fgets(filename, FILE_LENGTH, stdin);
  FILE *f = fopen(filename, "w");

  if (f == NULL) {
    printf("File could not be opened!");
    exit(1);
  }

  eCalculation(100, f);

  fclose(f);

  return 0;
}
