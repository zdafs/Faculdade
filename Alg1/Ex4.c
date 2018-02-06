#include <stdio.h>
int main ()
{
   float ant_sal, novo_sal;
   printf("Digite o salário atual:");
   scanf("%f", &ant_sal);
   novo_sal = ant_sal*1.25;
   printf("O novo salário será %.2f", novo_sal);
   return (0);
}
