#include"lexical.h"

int TOKEN_LEN = 1000;


int main(int argc, char* argv[]){
	if(argc < 2){
		printf("usage %s <filename>\n",argv[0]);
		exit(0);
	}

	lexical_analyser la(argv[1]);
	char token[TOKEN_LEN];

	while(la.get_next_token(token)) printf( ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET "\n",token);

	return 0;
}



