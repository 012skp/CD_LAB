#include<bits/stdc++.h>

int main(){

	char str[] = "	printf Rx";
	char var[5]; memset(var,0,5);
	sscanf(str,"%*s%s",var);
	printf("%s\n",var);
}