/* This program parses assembly code written in test file 
/* To differenciate between a routine and a label, all label must start with '_'
/* You can write even complex assembly code like loops using lables 
/* Not all types of jumps have been implemented */

#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define pb push_back
#define F first
#define S second


int Rx;
int Ry;
int Rz;
int Rtemp;

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
			
			if(strncmp(lvar,"Rx",2) == 0) lval = Rx;
			else if(strncmp(lvar,"Ry",2) == 0) lval = Ry;
			else if(strncmp(lvar,"Rz",2) == 0) lval = Rz;
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
		printf("lval = %d rval = %d\n",lval, rval);
		if(opr == '+') return lval+rval;
		if(opr == '-') return lval-rval;

	}
	else{ // If there is no operation + or -, rhs may be const or Registers or variable...
		char rvar[10];
		memset(rvar, 0 , 10);
		sscanf(inst.c_str(),"\t%*[^=]=%s",rvar);
		// check whether rvar is constant..
		if(rvar[0] <= '9' and rvar[0] >= '0') return atoi(rvar);
		else if(strncmp(rvar,"Rx",2) == 0) return Rx;
		else if(strncmp(rvar,"Ry",2) == 0) return Ry;
		else if(strncmp(rvar,"Rz",2) == 0) return Rz;
		else return memory[rvar];
	}

}


int handle_jump(string inst){
	// Only JMLT is implemented...
	if(strncmp(inst.c_str(),"JMLT",4) == 0) return Rtemp < 0?3:0;
	else if(strncmp(inst.c_str(),"JMGT",4) == 0) return Rtemp > 0?3:0;
	else if(strncmp(inst.c_str(),"JMEQ",4) == 0) return Rtemp == 0?3:0;
	else printf("Undefined JUMP instruction %s\n",inst.c_str());
	exit(1);
}

int parse(map<string,int> &memory, instruction inst){
	printf("parsing the instruction: %s\n",inst.c_str());
	sleep(1);
	if(strncmp(inst.c_str(),"Call",4)==0) return 1;
	if(strncmp(inst.c_str(),"RET",3) ==0) return -1;
	if(strncmp(inst.c_str(),"STOP",4)==0){
		exit(0);
	}
	if(strncmp(inst.c_str(),"print",5)==0) return 2;

	// Handle JUMP
	if(strncmp(inst.c_str(),"JM",2) == 0){
		return handle_jump(inst);
	}
	// Handle assignment..
	int rhs = get_rhs(memory,inst);
	Rtemp = rhs;

	char lvar[10];
	memset(lvar,0,10);
	sscanf(inst.c_str(),"%s",lvar);
	if(strncmp(lvar,"Rx",2) == 0) Rx = rhs; 
	else if(strncmp(lvar,"Ry",2) == 0) Ry = rhs; 
	else if(strncmp(lvar,"Rz",2) == 0) Rz = rhs;
	else {memory[lvar] = rhs; printf("new var %s created with val = %d\n",lvar,memory[lvar]);}
	printf("Rx = %d, Ry = %d, Rz = %d\n",Rx,Ry,Rz);
	return 0;
}



void print_code_section(map<string,vector<instruction> > &code_section){
	auto it = code_section.begin();
	while(it != code_section.end()){
		vector<instruction> &inst_set = it->S;
		cout<<it->F<<endl;
		for(int i=0;i<inst_set.size();i++) cout<<"	"<<inst_set[i]<<endl; cout<<endl;
		it++;
	}

}

int main(){
		map<string,vector<instruction> > code_section;
		FILE *fp = fopen("test","r");
		char fun[50];
		char inst[50];
		//system("cat test");
		while(!feof(fp)){
			memset(fun,0,50);
			fscanf(fp,"%[^:]:\n",fun);
			string fun_name(fun);
			code_section[fun_name] = vector<instruction>(0);
			//printf("%s:\n",fun);
			while(1){
				fscanf(fp,"\t%[^\n]\n",inst);
				if(strcmp(inst,"STOP") == 0 or strcmp(inst,"RET") == 0){
					code_section[fun_name].pb(inst);
					// But if this is RET and next is ELSE:
					// put all of them in same routine.
					if(feof(fp)) break;
					char ch = fgetc(fp);
					if(ch == '_'){ // this is some label ...
						fscanf(fp,"%[^:]:\n",inst);
					}
					else { fseek(fp,-1,SEEK_CUR); break; }
				}
				code_section[fun_name].pb(inst);
				//printf("\t%s\n",inst);
			}
		}

		print_code_section(code_section);

		// Execute code_section.... 
		stack_frame sf;
		sf.return_addr.F = "NONE";
		sf.return_addr.S = -1;
		sf.pc.F = "Main";
		sf.pc.S = 0;
		stack<stack_frame> mystack;
		mystack.push(sf);

		while(!mystack.empty()){
			stack_frame &current_stack = mystack.top();
			string &routine = current_stack.pc.F;
			
			auto it = code_section.find(routine);
			if(it == code_section.end()){
				printf("Undefined reference to %s\n",routine.c_str());
				exit(1);
			}

			vector<instruction> &inst_set = it->S;
			map<string,int> &memory = current_stack.memory;
			printf("Executing Routine %s form inst no: %d\n",routine.c_str(), current_stack.pc.S);
			// Execute each instruction..
			for(int i=current_stack.pc.S;i<inst_set.size();i++){
				
				int ret_type = parse(memory,inst_set[i]);

				if(ret_type == 0) continue; // normal.

				else if (ret_type == 1){ // Call
					// Save current state of programe execution..
					current_stack.pc.S = i+1;
					
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
					string label;
					char labell[10];memset(labell,0,10);
					sscanf(inst_set[i].c_str(),"%*s%s",labell);
					label = labell;
					printf("JUMP inst found finding label %s\n",labell);
					int j = 0;
					while(inst_set[j] != label and j < inst_set.size()) j++;
					
					printf("found the label is %s\n",inst_set[j].c_str());
					i = j; // next instruction in that label..
				}

			}


		}
		
	return 0;
}
