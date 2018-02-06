#include <stdio.h>
int main ()
{
   float preco_fab, lucro, imp, preco_final;
   printf("Digite o preço de fabrica do veiculo:");
   scanf("%f", &preco_fab);
   printf("Digite o percentual de lucro do vendedor:");
   scanf("%f", &lucro);
   printf("Digite o percentual cobrado em impostos:");
   scanf("%f", &imp);
   preco_final = preco_fab+(preco_fab*lucro/100)+(preco_fab*imp/100);
   printf("O lucro do vendedor será de %.2f\n", preco_fab*lucro/100);
   printf("O imposto cobrado será de %.2f\n", preco_fab*imp/100);
   printf("O valor final será de %.2f\n", preco_final);
   return (0);
}
