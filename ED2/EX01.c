#include <stdio.h>

int main(int argc, char *argv[]){
	FILE *f;
	char c;

	f = fopen(argv[1], "r");
	if(f==NULL)
		printf("Erro ao abrir o arquivo");
	else{
		while((c=fgetc(f))!=EOF)
			printf("%c", c);
	}
	fclose(f);

	return(0);
}