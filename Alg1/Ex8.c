#include <stdio.h>
int main ()
{
   float deposito, juros, rendimento, total_rendimento;
   printf("Digite o valor do depósito:");
   scanf("%f", &deposito);
   printf("Digite o valor percentual do rendimento:");
   scanf("%f", &juros);
   rendimento = deposito*(juros/100);
   total_rendimento = deposito*(1+juros/100);
   printf("o valor do rendimento será %.2f\n", rendimento);
   printf("o valor total depois do rendimento será %.2f\n", total_rendimento);
   return (0);
}
