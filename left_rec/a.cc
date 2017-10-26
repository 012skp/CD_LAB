#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

string get_token(string rule, int &idx){
	string ans;
	while(idx < rule.length() and rule[idx] != '|'){
		ans.push_back(rule[idx]);
		idx++;
	}
	idx++;
	return ans;
}


void eleminate_left_rec(string rule){
	vector<string> v1,v2;
	const char *str = rule.c_str();
	char start;
	start = rule[0];
	int idx = 3;
	int n = rule.length();
	bool flag = true;
	while(idx<n){
		int pidx = idx;
		string sss;
		sss = get_token(rule,idx);
		if(rule[pidx] == start){ // if first char matches..
			v1.push_back(sss);
			flag = false;
		}
		else
			v2.push_back(sss); 
	}
	
	if(flag){
		printf("There is no left recursion in rule: %s\n",rule.c_str());
		return;
	}

	// remove left char from each rule and append left char + '
	// Bab -> abB'

	for(int i=0;i<v1.size();i++) v1[i].erase(0,1), v1[i].push_back(start), v1[i].push_back('\'');
	for(int i=0;i<v2.size();i++) v2[i].push_back(start), v2[i].push_back('\'');
	
	char ans1[100],ans2[100],ans3[100];
	memset(ans1,0,100);
	memset(ans2,0,100);
	memset(ans3,0,100);
	
	strncpy(ans1,str,3);
	for(int i=0;i<v1.size();i++){
		strcat(ans1,v1[i].c_str());
		strcat(ans1,"|");
	}
	
	ans2[0] = start;
	strcat(ans2,"'->");
	for(int i=0;i<v2.size();i++){
		strcat(ans2,v2[i].c_str());
		strcat(ans2,"|");
	}

	ans1[strlen(ans1)-1] = 0;
	ans2[strlen(ans2)-1] = 0;
	
	ans3[0] = start;
	strcat(ans3,"'->EPSILON");
	printf("RULE:\n%s\n\n",rule.c_str());
	printf("ANSWER:\n");
	printf("%s\n%s\n%s\n",ans1,ans2,ans3);
}


int main(){
	int n;
	cin>>n;
	vector<string> rules(n);
	for(int i=0;i<n;i++) cin>>rules[i];
	for(int i=0;i<n;i++) eleminate_left_rec(rules[i]);
	return 0;
}
