#include <stdio.h>
int main ()
{
   float sal, aumento, qnt_aumentada, novo_sal;
   printf("Digite o salário atual:");
   scanf("%f", &sal);
   printf("Digite o aumento percentual:");
   scanf("%f", &aumento);
   qnt_aumentada = sal*(aumento/100);
   novo_sal = sal*(1+aumento/100);
   printf("O valor de aumento do salário foi de %.2f\n", qnt_aumentada);
   printf("O novo salário é de %.2f\n", novo_sal);
   return (0);
}
