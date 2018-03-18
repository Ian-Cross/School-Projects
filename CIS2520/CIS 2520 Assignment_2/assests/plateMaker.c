#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]) {
  srand(time(NULL));

  for (int i = 0; i <= 35; i++) {
    printf("%c",rand() % 26 + 65);
    printf("%c",rand() % 26 + 65);
    printf("%c",rand() % 26 + 65);
    printf("%c",rand() % 26 + 65);
    printf("-%d",rand() % 9);
    printf("%d",rand() % 9);
    printf("%d",rand() % 9);

    printf(" %07d\n",rand() % 300000 + 50000);
  }

  for (int i = 0; i < 23; i++) {
    printf("%c",rand() % 26 + 65);
    printf("%c",rand() % 26 + 65);
    printf("%c",rand() % 26 + 65);
    printf("%c",rand() % 26 + 65);
    printf("-%d",rand() % 9);
    printf("%d",rand() % 9);
    printf("%d",rand() % 9);

    printf(" %07d",rand() % 300000 + 50000);

    printf(" 17%02d%02d\n",rand() % 11 + 1, rand() % 27 + 1);
  }


    for (int i = 0; i < 17; i++) {
      printf("%c",rand() % 26 + 65);
      printf("%c",rand() % 26 + 65);
      printf("%c",rand() % 26 + 65);
      printf("%c",rand() % 26 + 65);
      printf("-%d",rand() % 9);
      printf("%d",rand() % 9);
      printf("%d",rand() % 9);

      printf(" %07d",rand() % 300000 + 50000);
      printf(" 17%02d%02d\n",rand() % 11 + 1, rand() % 27 + 1);
    }


  return 0;
}
