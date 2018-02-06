#include <stdio.h>
int main ()
{
   float num;
   printf("Digite um numero maior que 0:");
   scanf("%f", &num);
   if (num<0)
   {
      printf("O numero digitado é negativo\n");
   }
   else
   {
      printf("O quadrado do numero é %.2f\n", num*num);
      printf("O cubo do numero é %.2f\n", num*num*num);
   }
   return (0);
} 
