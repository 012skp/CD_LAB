#include<lexical.h>
#define pb push_back
#define COLOR_S \x1b[32m%d\x1b[0m)\x1b[32m
#define COLOR_E \x1b[0m: \x1b[32m%s\x1b[0m
extern int TOKEN_LEN;


	lexical_analyser::lexical_analyser(char *file_name){
		delimeter = (char*)"+-/*%^&|~ \n\t=;:,(){}[]\"\'.!<>";
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
		// Initialise keywords.
		keywords.pb((char*)("auto"));
		keywords.pb((char*)("double"));
		keywords.pb((char*)("int"));
		keywords.pb((char*)("struct"));
		keywords.pb((char*)("break"));
		keywords.pb((char*)("else"));
		keywords.pb((char*)("switch"));
		keywords.pb((char*)("long"));
		keywords.pb((char*)("case"));
		keywords.pb((char*)("enum"));
		keywords.pb((char*)("register"));	
		keywords.pb((char*)("typedef"));
		keywords.pb((char*)("char"));
		keywords.pb((char*)("return"));
		keywords.pb((char*)("extern"));
		keywords.pb((char*)("union"));
		keywords.pb((char*)("const"));
		keywords.pb((char*)("float"));
		keywords.pb((char*)("short"));
		keywords.pb((char*)("unsigned"));
		keywords.pb((char*)("continue"));
		keywords.pb((char*)("for"));
		keywords.pb((char*)("signed"));
		keywords.pb((char*)("void"));
		keywords.pb((char*)("default"));
		keywords.pb((char*)("goto"));
		keywords.pb((char*)("sizeof"));
		keywords.pb((char*)("volatile"));
		keywords.pb((char*)("do"));
		keywords.pb((char*)("if"));
		keywords.pb((char*)("static"));
		keywords.pb((char*)("while"));

		// Initialise int_suffix.
		int_suffix.pb((char*)("l"));
		int_suffix.pb((char*)("L"));
		int_suffix.pb((char*)("ll"));
		int_suffix.pb((char*)("LL"));
		int_suffix.pb((char*)("lU"));
		int_suffix.pb((char*)("lu"));
		int_suffix.pb((char*)("LU"));
		int_suffix.pb((char*)("Lu"));
		int_suffix.pb((char*)("llU"));
		int_suffix.pb((char*)("llu"));
		int_suffix.pb((char*)("LLu"));
		int_suffix.pb((char*)("LLU"));
		int_suffix.pb((char*)("u"));
		int_suffix.pb((char*)("U"));
		int_suffix.pb((char*)("ul"));
		int_suffix.pb((char*)("Ul"));
		int_suffix.pb((char*)("uL"));
		int_suffix.pb((char*)("UL"));
		int_suffix.pb((char*)("ull"));
		int_suffix.pb((char*)("Ull"));
		int_suffix.pb((char*)("uLL"));
		int_suffix.pb((char*)("ULL"));
		
	}
	

	// Validates the token is a valid token.
	char* lexical_analyser::validate(char *token){
		if(is_delimeter(token[0]) && strlen(token) == 1){
			if(token[0] == ' ' or token[0] == '\t' or token[0] == '\n') 
				printf("void-space ");
			else printf("symbol ");
			return token;
		}
		// Else it is either keyword, or identifier, or string literal, or numeric constant.
		if(is_keyword(token)){
			printf("keyword "); 
			return token;
		}
		else if(is_identifier(token)){
			printf("identifier ");
			return token;
		}
		else if(is_string_literal(token)){
			printf("constant ");
			return token;
		}
		else if(is_numeric_constant(token)){
			printf("constant ");
			return token;
		}
		else{
			printf(ANSI_COLOR_RED "Invalid token " ANSI_COLOR_RESET);
			return token;
		}
	}

	char* lexical_analyser::get_next_token(char *token){
		if(!fp) return NULL;
		start:
		memset(token,0,TOKEN_LEN);
		if(next_token(token) == NULL) return NULL;
		

		// If " is incountered...
		// Handle string constansts...
		if(token[0] == '\"'){
			if(till_quote(token)) return validate(token);
			else return NULL;
		}

		// If comment with "//"  or "/*" are incountered ignore till comments end.
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
		
		// No validation required.
		// Compiler will validate.
		if(token[0] == '#') return token;


		//Ignore multiple spaces like ' ', '\n', '\t'
		// If previous token was not space, return this token whatever it is.
		if(previous_token == '0'){
	
			// If this token is space store it.
			if(token[0] == ' ' || token[0] == '\t' || token[0] == '\n') 
				previous_token = token[0]; 
			else
				previous_token = '0';
			return validate(token);
		}
		// If previous token was space.
		else{
			// If this token is also space then don't return this token.
			if(token[0] == ' ' || token[0] == '\t' || token[0] == '\n'){
				goto start;
			}
			else{
				// this token is not space pass it.
				previous_token = '0';
				return validate(token);
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
					// Handle cases for +-. in numeric constant.
					if(ch == '.'){
						// Check is it part of a float else if identifier leave it.
						if(isdigit(token[0]) && token[0] != '0');
						else{
							fseek(fp,-1,SEEK_CUR);
							return token;
						}
						for(int i=1;i<idx;i++){
							if(!isdigit(token[i])){
								fseek(fp,-1,SEEK_CUR);
								return token;
							}
						}
						// If everything is fine include . in token
						token[idx++] = ch;
						continue;
				
					}
					if(ch == '+' or ch == '-'){
						// Check if it is part of numeric constant like int 343E-5;
						if(token[idx-1] == 'e' or token[idx-1] == 'E');
						else{
							fseek(fp,-1,SEEK_CUR);
							return token;
						}
						// It can starts with 0 or 0x or 123
						if(strncmp(token,"0x",2) == 0 or isdigit(token[0]) ){
							int i=0;
							if(strncmp(token,"0x",2)==0) i = 2; 
							for(int j=i;j<idx-1;j++){
								if(isdigit(token[j]) or token[j] == '.');
								else{
									fseek(fp,-1,SEEK_CUR);
									return token;
								}
							}

							// If everything is fine include +- in token.
							token[idx++] = ch;
							continue;
						}
				
					}

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
					printf("directive ");
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

	char* lexical_analyser::is_keyword(char *token){
		for(int i=0;i<keywords.size();i++) 
			if(strcmp(token,keywords[i]) == 0) 
				return token;
		return NULL;
	}

	char * lexical_analyser::is_identifier(char *token){
		// first char should be '_' or '{a-z}' or '{A-Z}'.
		char fc = token[0];
		if(fc == '_' or (fc>=65 and fc<=90) or (fc<=122 and fc >= 97) );
		else return NULL;
		
		// Rest of char now may contain '{0-9}'.
		for(int i=1;i<strlen(token);i++){
			fc = token[i];
			if(fc == '_' or  (fc<= 57 and fc>= 48) or (fc>=65 and fc<=90) or (fc<=122 and fc >= 97) );
			else return NULL;
		}

		return token;
		
	}

	char* lexical_analyser::is_string_literal(char *token){
		// First char must be '"'
		char fc = token[0];
		if(fc == '\"') return token;
		else return NULL;
	}

	char* lexical_analyser::is_numeric_constant(char *token){
		int idx = 0;
		if(token[0] == '-' || token[0] == '+') idx++;
		if(token[idx] == '.') goto FLOAT;
		if(strncmp(token+idx,"0x",2) == 0) goto HEX;
		else if(strncmp(token+idx,"0.",2) == 0) { idx+=1; goto FLOAT;}
		else if(token[idx] == '0') goto OCTAL;
		else goto DECIMAL;


DECIMAL:	// DECIMAL Starts.	
		
		// This may contain float.
		int i;
		for(i=idx;i<strlen(token);i++){
			if(token[i] <= 57 and token[i] >= 48);
			else break;	
		}
		if(i == strlen(token)) return token;
		else if(token[i] == '.'){ idx = i; goto FLOAT;}
		else if(token[i] == 'E' or token[i] == 'e'){ idx = i; goto EXPONENT;}
		else if(token[i] == 'u' or token[i] == 'U' or token[i] == 'l' or token[i] == 'L'){
			idx = i;
			goto INT_SUFFIX;
		}
		else return NULL;
		// DECIMAL Ends.

HEX:		// HEX Starts.
		
		for(i=idx+2;i<strlen(token);i++){
			// Either 0-9 or a-f or A-F.
			if((token[i] <= 57 and token[i] >= 48) or (token[i]<=70 and token[i]>= 65) or (token[i]<=102 and token[i]>= 97) );
			else break;
		}
		if(i == strlen(token)) return token;
		else if(token[i] == 'u' or token[i] == 'U' or token[i] == 'l' or token[i] == 'L'){
			idx = i;
			goto INT_SUFFIX;
		}
		else return NULL;
		// HEX Ends.

OCTAL:		// OCTAL Starts.
		for(i=idx+1;i<strlen(token);i++){
			// Either 0-9 or a-f or A-F.
			if(token[i] <= 55 and token[i] >= 48 );
			else break;
		}
		if(i == strlen(token)) return token;
		else if(token[i] == 'E' or token[i] == 'e'){idx = i; goto EXPONENT;}
		else if(token[i] == 'u' or token[i] == 'U' or token[i] == 'l' or token[i] == 'L'){
			idx = i;
			goto INT_SUFFIX;
		}
		else return NULL;
		// OCTAL Ends.

FLOAT:		// FLOAT Starts.

		// Return err for 234. cases.
		if(strlen(token) == idx+1) return NULL;
		for(i=idx+1;i<strlen(token);i++){
			if(token[i] <= 57 and token[i] >= 48);
			else break;	
		}
		if(i == strlen(token)) return token;
		else if(token[i] == 'E' or token[i] == 'e'){
			idx = i;
			goto EXPONENT;		
		}


FLOAT_SUFFIX:	// FLOAT_SUFFIX Starts.
		// Pointer(idx) at the start of suffix.
		i  = idx;
		if(token[i] == 'f' or token[i] == 'F' or token[i] == 'l' or token[i] == 'L'){
			// Float suffix is either f|F or l|L not both. So this must be end of token.
			if(i==strlen(token)-1) return token;
			else return NULL;
		}
		else return NULL;
		// FLOAT_SUFFIX Ends.


INT_SUFFIX:	// INT_SUFFIX Starts.
		// Pointer(idx) at the start of suffix.
		for(int i=0;i<int_suffix.size();i++){
			if(strcmp(token+idx,int_suffix[i]) == 0) return token;
		}
		return NULL;

		// INT_SUFFIX Ends.


EXPONENT:	// EXPONENT Starts. Exponent make a constant to float.
		// Pointer(idx) at pos 'e' or 'E'
		idx++;
		char fc = token[idx];
		if(fc == '+' || fc == '-') idx++;
		if(strlen(token) == idx) return NULL;
		for(i=idx;i<strlen(token);i++){
			if(token[i] <= 57 and token[i] >= 48);
			else break;
		}
		if(i==strlen(token)) return token;
		else if(token[i] == 'f' or token[i] == 'F' or token[i] == 'l' or token[i] == 'L'){
			idx = i;
			goto FLOAT_SUFFIX;
		}
		else return NULL;
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
