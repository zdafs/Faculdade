#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]){
	FILE *f;
	char c;
	int flag=0, letras=0, palavras=0;

	f = fopen(argv[1], "r");
	if(f==NULL)
		printf("Erro ao abrir o arquivo\n");
	else{
		while((c=fgetc(f))!=EOF){
			if(isalpha(c)){
				flag = 1;
				letras++;
			}
			if(flag && !isalpha(c)){
				flag = 0;
				palavras++;
			}
		}
		printf("letras: %d\npalavras: %d\n", letras, palavras);
		fclose(f);
	}

	return(0);
}