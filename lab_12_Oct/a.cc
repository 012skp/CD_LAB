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
	// program_counter
	pair<string,int> pc;
	// variable,value
	map<string,int> memory;
};

int get_rhs(map<string,int> &memory, instruction inst){
	bool op = false;
	for(int i=0;i<inst.length();i++) 
		if(inst[i] == '+' or inst[i] == '-'){ 
			op = true;
			break;
		}
	
	if(op){
		char lvar[10],rvar[10];
		memset(lvar,0,10);
		memset(rvar,0,10);
		char opr;
		// scan left var, operator, right var...
		sscanf(inst.c_str(),"%*[^=]=%s %c %s",lvar,&opr,rvar);
		printf("lvar = %s, opr = %c, rvar = %s\n",lvar,opr,rvar);
		int lval,rval;
		if(lvar[0] <= '9' and lvar[0] >= '0') lval = atoi(lvar);
		else{
			// It may be either var or Register...
			
			if(strcmp(rvar,"Rx")==0) rval = Rx;
			else if(strcmp(rvar,"Ry")==0) rval = Ry;
			else if(strcmp(rvar,"Rz")==0) rval = Rz;
			else{
				auto it = memory.find(lvar);
				if(it == memory.end()){
					printf("Undefined reference to variable_left %s\n",lvar);
					exit(1);
				}
				lval = it->S;
			}
		}
		if(rvar[0] <= '9' and rvar[0] >= '0') rval = atoi(rvar);
		else{
			// It may be either var or Register...
			
			if(strcmp(rvar,"Rx")==0) rval = Rx;
			else if(strcmp(rvar,"Ry")==0) rval = Ry;
			else if(strcmp(rvar,"Rz")==0) rval = Rz;
			else{
				auto it = memory.find(rvar);
				if(it == memory.end()){
					printf("Undefined reference to variable_right %s\n",rvar);
					exit(1);
				}
				else rval = it->S;
			}
		}

		if(opr == '+') return lval+rval;
		if(opr == '-') return lval-rval;

	}
	else{
		return atoi(inst.c_str());
	}

}


int parse(map<string,int> &memory, instruction inst){
	printf("parsing the instruction %s\n",inst.c_str());
	if(strncmp(inst.c_str(),"Call",4)==0) return 1;
	if(strncmp(inst.c_str(),"RET",3) ==0) return -1;
	if(strncmp(inst.c_str(),"STOP",4)==0){
		exit(0);
	}
	if(strncmp(inst.c_str(),"print",5)==0) return 2;
	// Handle JMLT
	
	// Handle assignment..
	int rhs = get_rhs(memory,inst);
	
	char lvar[10];
	memset(lvar,0,10);
	sscanf(inst.c_str(),"%s",lvar);

	memory[lvar] = rhs;
	
	return 0;
}

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
		sf.pc.F = "Main";
		sf.pc.S = 0;
		stack<stack_frame> mystack;
		mystack.push(sf);

		while(!mystack.empty()){
			stack_frame current_stack = mystack.top();
			string routine = current_stack.pc.F;
			
			auto it = code_section.find(routine);
			if(it == code_section.end()){
				printf("Undefined reference to %s\n",routine.c_str());
				exit(1);
			}

			vector<instruction> &inst_set = it->S;
			map<string,int> &memory = current_stack.memory;

			// Execute each instruction..
			for(int i=current_stack.pc.S;i<inst_set.size();i++){

				int ret_type = parse(memory,inst_set[i]);

				if(ret_type == 0) continue; // normal.

				else if (ret_type == 1){ // Call
					// Save current state of programe execution..
					current_stack.pc.S = i;
					
					// create new_stack frame for function call..
					stack_frame new_sf;
					char new_routine[20];
					memset(new_routine,0,20);
					sscanf(inst_set[i].c_str(),"%*s%s",new_routine);
					new_sf.pc.F = new_routine;
					new_sf.pc.S = 0;
					mystack.push(new_sf);
					break;
				}
				else if(ret_type == -1){// RET
					mystack.pop();
					break;
				}
				else if(ret_type == 2){// print instruction
					const char* str = inst_set[i].c_str();
					char var[5]; memset(var,0,5);
					sscanf(str,"%*s%s",var);
					auto itr = memory.find(var);
					if(itr == memory.end()){
						printf("Undefined reference to variable1 %s\n",var);
						exit(1);
					}
					printf("%s = %d\n",var,memory[var]);
				}
				else if(ret_type == 3){ // JMP
				
				}

			}


		}
		
	return 0;
}
