#include <stdio.h>
int main ()
{
   float sal, novo_sal;
   printf("Digite o salário base:");
   scanf("%f", &sal);
   novo_sal = sal*0.9+50;
   printf("o salário a ser recebido é %.2f", novo_sal);
   return (0);
}
