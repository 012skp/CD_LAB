#include<bits/stdc++.h>

class lexical_analyser{
	char filename[20];	
	FILE* fp;
	char *delimeter;
	char previous_token;
	bool quote_start;
public:
	lexical_analyser(char *file_name);
	char *get_next_token(char *token);
	char* get_delimeter();
	~lexical_analyser();
private:
	char* next_token(char *token);
	char* whole_line(char *token);
	bool till_quote(char *token);
	char* handle_multiline_comments(char *token);
	int is_delimeter(char ch);
};



