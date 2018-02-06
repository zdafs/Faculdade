#include <stdio.h>

int main()
{
   float salario_atual,novo_salario;
   printf("Digite o salário atual: ");
   scanf("%f", &salario_atual);
   if(salario_atual<=1000)
      novo_salario=salario_atual*1.2;
   else
      novo_salario=salario_atual*1.1;
   printf("seu novo salário é %.2f\n", novo_salario);
   return (0);
} 
