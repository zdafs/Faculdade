#include <stdio.h>
int main ()
{
   float hora_trab, sal_min, sal_rec;
   printf("Digite o numero de horas trabalhadas:");
   scanf("%f", &hora_trab);
   printf("Digite o valor do salário minimo:");
   scanf("%f", &sal_min);
   sal_rec = (hora_trab*sal_min/2)-((hora_trab*sal_min/2)*3/100);
   printf("O salário a receber será %.2f", sal_rec);
   return (0);
}
