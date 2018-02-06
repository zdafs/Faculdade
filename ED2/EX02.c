#include <stdio.h>

int main(int argc, char *argv[]){
	FILE *f, *fc;
	char c;

	f = fopen(argv[1], "r");
	if(f==NULL)
		printf("Erro ao abrir o arquivo");
	else{
		fc = fopen("Copia.txt", "w");
		if(fc==NULL)
			printf("Erro ao abrir o arquivo");
		else{
			while((c=fgetc(f))!=EOF)
				fputc(c, fc);
		}
	}
	fclose(f);
	fclose(fc);

	return(0);
}