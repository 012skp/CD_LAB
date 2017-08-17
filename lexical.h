#include<bits/stdc++.h>
using namespace std;

class lexical_analyser{
	char filename[20];	
	FILE* fp;
	char *delimeter;
	vector<char*> keywords;
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



