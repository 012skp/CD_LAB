#include<lexical.h>
extern int TOKEN_LEN;


	lexical_analyser::lexical_analyser(char *file_name){
		delimeter = (char*)"+-/*%^&|~ \n\t=;,(){}[]\"\'.!<>";
		memset(filename,0,20);
		if(!file_name){
			printf("file_name is NULL\n");
			fp = NULL;
			return;
		}
		strcpy(filename,file_name);
		fp = fopen(filename,"r");
		if(!fp){
			printf("Error: file not found\n");
		}
		// Set previous_token as non void-space.
		previous_token = '0';
	}

	char* lexical_analyser::get_next_token(char *token){
		if(!fp) return NULL;
		start:
		memset(token,0,TOKEN_LEN);
		if(next_token(token) == NULL) return NULL;
		

		// If " is incountered..???
		if(token[0] == '\"'){
			if(till_quote(token)) return token;
			else return NULL;
		}

		// If comment with "//"  or "/*" are incountered pass whole line as token
		if(token[0] == '/'){		
			char ch;
			if(!feof(fp)) 
				ch = fgetc(fp);
			if(ch == '/'){
				fseek(fp,-2,SEEK_CUR);
				whole_line(token);
				goto start;
			}
			if(ch == '*'){
				handle_multiline_comments(token);
				goto start;
			}
			// else do nothing..

		}
		/* If previous_token was non void-space
		   then register this token in previous_token
		   and send the token.
		*/
		if(previous_token == '0'){

			// If this token is void-space store it.
			if(token[0] == ' ' || token[0] == '\t' || token[0] == '\n') 
				previous_token = token[0]; 
			else
				previous_token = '0';
			return token;
		}
		else{
			// If previous_token was void-space and this is also 
			// void-space then don't pass delimeter.
			if(token[0] == ' ' || token[0] == '\t' || token[0] == '\n'){
				// this token is void-space don't pass it.
				goto start;
			}
			else{
				// this token is non void-space pass it.
				previous_token = '0';
				return token;
			}
			
		}



	}

	char* lexical_analyser::next_token(char *token){
		
		int idx = 0;
		while(!feof(fp)){
			char ch = fgetc(fp);
			if(is_delimeter(ch)){
				// If idx > 0 
				if(idx){
					if(ch == '\"' and token[idx-1] == '\\'){
						token[idx++] = ch;
						continue;
					}
					fseek(fp,-1,SEEK_CUR);
					return token;
				}
				else{
					token[0] = ch;
					return token;
				}
			}
			if(ch == '#'){
				if(idx){
					// return the token made till this time.
					fseek(fp,-1,SEEK_CUR);
					return token;
				}
				else{
					fseek(fp,-1,SEEK_CUR);
					return whole_line(token);
				}
			}

			token[idx++] = ch;
			if(idx == TOKEN_LEN){
				printf("TOKEN_LEN size error....\n");
				return NULL;
			}
		}
		
		if(idx > 1) return token;
		else return NULL;
	
	}
	
	char* lexical_analyser::whole_line(char *token){
		int idx = 0;
		while(1){
			char ch = (char)fgetc(fp);
			if(ch == '\n') return token;
			if(feof(fp) == EOF) return token;
			token[idx++] = ch;
		}

		token[idx] = '\n';
	
	}

	bool lexical_analyser::till_quote(char *token){
		token[0] = '\"';
		char ch = '0';
		int idx = 1;
		char pch = '0';
		while(!feof(fp) && !(ch == '\"' &&  pch != '\\')  && idx < TOKEN_LEN){
			pch = ch;
			ch = (char)fgetc(fp);
			token[idx++] = ch;
		}
		if(idx == TOKEN_LEN){
			printf("TOKEN_LEN size errro...\n");
			return false;
		}

		// EOF reached without encountering '"';
		if(ch != '\"'){
			printf("SYNTAX ERROR: \" not found \n");
			return false;
		}

		return true;

	}

	char* lexical_analyser::handle_multiline_comments(char *token){
		token[0] = '/';
		token[1] = '*';
		int idx = 2;
		char ch = '0', pch = '0';
		while(!feof(fp) && !(ch == '/' && pch == '*') && idx < TOKEN_LEN){
			pch = ch;
			ch = fgetc(fp);
			token[idx++] = ch;
		}
		if(idx == TOKEN_LEN){
			printf("TOKEN_LEN size error...\n");
			return NULL;
		}

		// EOF reached without encounterinhg '*/'
		// then it's fine.
		
		return token;


	}

	int lexical_analyser::is_delimeter(char ch){
		int len = strlen(delimeter);
		for(int i=0;i<len;i++) if(ch == delimeter[i]) return 1;
		return 0;
	}

	lexical_analyser::~lexical_analyser(){
		if(fp) fclose(fp);
	}

	char* lexical_analyser::get_delimeter(){
		return delimeter;
	}



// Driver Program..


/*
int main(int argc, char* argv[]){
	if(argc < 2){
		printf("usage %s <filename>\n",argv[0]);
		exit(1);
	}
	lexical_analizer la(argv[1]);
	char *del = la.get_delimeter();
	for(int i=0;i<strlen(del);i++){
		printf("del = @%c@\n",del[i]);
	}

	char token[TOKEN_LEN];
	while(la.get_next_token(token)) printf("token = %s\n",token);

	return 0;
}

*/
