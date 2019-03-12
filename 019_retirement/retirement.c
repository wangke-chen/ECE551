#include <stdio.h>
#include <stdlib.h>

typedef struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
} retire_info_t;

double saving_calcul(double initial, double contribut, double rate_return) {
  double money_return;

  money_return = initial * rate_return;
  initial = initial + contribut + money_return;

  return initial;
}

void retirement(int startAge, double initial, retire_info_t working, retire_info_t retired) {
  for (int i = 0; i < working.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, initial);
    startAge++;
    initial = saving_calcul(initial, working.contribution, working.rate_of_return);
  }

  for (int i = 0; i < retired.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, initial);
    startAge++;
    initial = saving_calcul(initial, retired.contribution, retired.rate_of_return);
  }
}

int main(void) {
  int startAge = 327;
  double initial = 21345.00;
  retire_info_t working;
  retire_info_t retired;

  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  retirement(startAge, initial, working, retired);

  return 0;
}
