#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define F first
#define S second


int Rx;
int Ry;
int Rz;

typedef string instruction;
	

struct stack_frame{
	pair<string,int> return_addr;
	string pc; // program counter...
	map<string,int> memory;
};


int main(){
		map<string,vector<instruction> > code_section;
		FILE *fp = fopen("test","r");
		char fun[50];
		char inst[50];
		while(!feof(fp)){
			memset(fun,0,50);
			fscanf(fp,"%[^:]:\n",fun);
			string fun_name(fun);
			code_section[fun_name] = vector<instruction>(0);
			printf("%s:\n",fun);
			while(1){
				fscanf(fp,"\t%[^\n]\n",inst);
				if(strcmp(inst,"STOP") == 0 or strcmp(inst,"RET") == 0) break;
				code_section[fun_name].pb(inst);
				printf("\t%s\n",inst);
			}
		}

		// Execute code_section.... 
		stack_frame sf;
		sf.return_addr.F = "NONE";
		sf.return_addr.S = -1;
		sf.pc = "Main";
		stack<stack_frame> mystack;
		mystack.push(sf);

		while(!mystack.empty()){
			
		}
		
	return 0;
}
