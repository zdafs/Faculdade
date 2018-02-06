#include <stdio.h>

int main(){
	FILE *fin, *fout;
	int n1, n2;
	char c;

	fin = fopen("arq.in", "r");
	if(fin==NULL)
		printf("Erro\n");
	else{
		fout = fopen("arq.out", "w");
		if(fout==NULL)
			printf("Erro\n");
		else{
			fscanf(fin, "%d %d", &n1, &n2);
			c=fgetc(fin);
			while(c!=EOF){
				fprintf(fout, "%d %d %d\n", n1, n2, n1+n2);
				fscanf(fin, "%d %d", &n1, &n2);
				c=fgetc(fin);
			}
			fprintf(fout, "%d %d %d", n1, n2, n1+n2);
			fclose(fout);
		}
		fclose(fin);
	}

	return(0);
}