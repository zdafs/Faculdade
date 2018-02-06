#include <stdio.h>

int main(int argc, char *argv[]){
	FILE *p;
	long int t;

	p = fopen(argv[1], "r");
	if(p!=NULL){
		fseek(p,0,SEEK_END);
		t = ftell(p);
		fclose(p);
		printf("%ld\n", t);
	}

	return(0);
}