#include <stdio.h>
int main ()
{
   int n1, n2, n3, n4, soma;
   printf("Digite 4 números inteiros:");
   scanf("%d %d %d %d", &n1, &n2, &n3, &n4);
   soma = n1+n2+n3+n4;
   printf("A soma dos números é %d\n", soma);
   return (0);
}
