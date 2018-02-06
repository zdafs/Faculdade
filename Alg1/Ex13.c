#include <stdio.h>
int main ()
{
   int ano_nasc, idade_atual, idade_2050;
   printf("Digite o ano de nascimeto:");
   scanf("%d", &ano_nasc);
   idade_atual = 2016-ano_nasc;
   idade_2050 = 2050-ano_nasc;
   printf("A sua idade é de %d anos\nEm 2050 voce tera %d anos\n", idade_atual, idade_2050);
   return (0);
}
