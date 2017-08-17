#include<bits/stdc++.h>
using namespace std;

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"



class lexical_analyser{
	char filename[20];	
	FILE* fp;
	char *delimeter;
	vector<char*> keywords;
	vector<char*> int_suffix;
	// if previous token was space previous_taken is set to space.
	// else previous_token is set to '0';
	char previous_token;
public:
	lexical_analyser(char *file_name);
	char *get_next_token(char *token);
	char* get_delimeter();
	~lexical_analyser();
private:
	char *validate(char *token);
	char* next_token(char *token);
	char* whole_line(char *token);
	bool till_quote(char *token);
	char* handle_multiline_comments(char *token);
	int is_delimeter(char ch);
	char* is_keyword(char* token);
	char* is_identifier(char* token);
	char* is_string_literal(char* token);
	char* is_numeric_constant(char* token);
};



