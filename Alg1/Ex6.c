#include <stdio.h>
int main ()
{
   float sal_base, sal_bruto, sal_bruto_rec;
   printf("Digite o salário base:");
   scanf("%f", &sal_base);
   sal_bruto = sal_base*1.05;
   sal_bruto_rec = sal_bruto*0.93;
   printf("O salário base total é %.2f\n", sal_bruto);
   printf("O salário base a ser recebido é %.2f\n", sal_bruto_rec);
   return (0);
}
