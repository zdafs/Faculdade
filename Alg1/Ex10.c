#include <stdio.h>
#define PI 3.14
int main ()
{
   float raio, area, circu;
   printf("DIgite o raio da circunferencia:");
   scanf("%f", &raio);
   area = PI*raio*raio;
   circu = 2*PI*raio;
   printf("A area é %.2f\n", area);
   printf("A circunferencia é %.2f\n", circu);
   return (0);
}
