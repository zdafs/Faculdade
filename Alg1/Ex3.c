#include <stdio.h>
int main ()
{
   float n1, n2, n3, p1, p2, p3, media;
   printf("Digite as tres notas:");
   scanf("%f %f %f", &n1, &n2, &n3);
   printf("Digite o peso de cada nota respectivamnte:");
   scanf("%f %f %f", &p1, &p2, &p3);
   media = (n1*p1+n2*p2+n3*p3)/(p1+p2+p3);
   printf("A média é %.2f", media);
   return (0);
}
