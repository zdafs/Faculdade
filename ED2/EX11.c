#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	FILE *p;
	long int tam;
	char *buffer;

	p = fopen(argv[1], "r");
	if(p!=NULL){
		fseek(p,0,SEEK_END);
		tam = ftell(p);
		rewind(p);
		buffer = (char *)malloc(tam+1);
		fread(buffer,1,tam,p);
		buffer[tam] = '\0';
		puts(buffer);
		fclose(p);
	}

	return(0);
}