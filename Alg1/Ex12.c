#include <stdio.h>
int main ()
{
   float pes, pol, jar, milhas;
   printf("Digite uma medida em pés:");
   scanf("%f", &pes);
   pol = 12*pes;
   jar = pes/3;
   milhas = jar/1760;
   printf("polegadas: %.2f\njardas: %.2f\nmilhas:%.2f\n", pol, jar, milhas);
   return (0);
}
    
