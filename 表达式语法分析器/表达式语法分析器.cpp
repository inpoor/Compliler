// 表达式语法分析器.cpp : 定义控制台应用程序的入口点。
//
 #include<iostream>
#include "stack.h"  
#include <string>
#include "stdlib.h"
#include "ctype.h"
#include<conio.h>
#include <string>
#include "stdafx.h"
#include <sstream> 
using namespace std;

/*--------------------------
LL（1）方法的表达式分析器
---------------------------*/

int flag =0;
const int VN_LEN=5;   //VN字符的数目
const int VT_lEN=21;  //VT字符的数目
string VN[10]={"E","E1","T","T1","F"};   //VN字符集合
string VT[22]={"a","b","c","d","e","+","*","-","/","0","1","2","3","4","5","6","7","8","9","(",")"};    //VT字符集合
 //LL表
const int TableLL[5][6]={
  1,0,0,1,0,0,
  0,2,0,0,3,3,
  4,0,0,4,0,0,
  0,6,5,0,6,6,
  7,0,0,8,0,0
};  
//判断字符串是否是VN
bool BelongVN(string str){
		
	for(int i=0;i<VN_LEN;i++){
		if(VN[i]==str){
			return 1;
		}
	}
	return 0;
}
//判断字符串是否是VT
bool BelongVT(string str){
		
	for(int i=0;i<VT_lEN;i++){
		if(VT[i]==str){
			return 1;
		}	
	}
	return 0;
}

//获取下一位字符
char GetNextChar(char *a){
	char ch;
	ch=a[flag];
	if(ch=='/0'){
	}
	else{
			flag++;
	return ch;
	}
}
//判断字符串是否是“+”OR“-”
bool Omega0(string a){
	if(a=="+"||a=="-"){
		return 1;
	}
	else{
		return 0;
	}
}
//判断字符串是否是“*”OR“/”
bool Omega1(string a){
	if(a=="*"||a=="/"){
		return 1;
	}
	else{
		return 0;
	}
}
//判断字符串是否数字
bool JudgeNumber(string a){
	char c=a[0];
	if(c>=48&&c<=58){
	   return 1;
	}else
	{
	return 0;
	}
}
//判断字符串是否字母
bool JudgeLetter(string a){
	char c=a[0];
	if(isalpha(c)==1||isalpha(c)==2){
	return 1;
	}
	else
		return 0;

}
 //查LL(1)分析表
void CheckTableLL(string &x,string &w,Stack<string> &a,bool &flag_error){
	int i=0,j=0;
	if(x=="E"){
		i=0;
	}else if(x=="E1"){
		i=1;
	}else if(x=="T"){
		i=2;
	}else if(x=="T1"){
		i=3;
	}else if(x=="F"){
		i=4;
	}else{
		cerr<<"CUOWU1"<<endl;
		flag_error=1;
	}
		if(JudgeNumber(w)||JudgeLetter(w)){
		j=0;
		}else if(Omega0(w)){
		j=1;
	}else if(Omega1(w)){
		j=2;
	}else if(w=="("){
		j=3;
	}else if(w==")"){
		j=4;
	}else if(w=="#"){
		j=5;
	}else{
		cerr<<"CUOWU2"<<endl;
	}
	if(TableLL[i][j]==1){
		a.push("E1");
		a.push("T");
	
	}else if(TableLL[i][j]==2){
		a.push("E1");
		a.push("T");
		a.push(w);
	}else if(TableLL[i][j]==3){
	}else if(TableLL[i][j]==4){
		a.push("T1");
		a.push("F");
	}else if(TableLL[i][j]==5){
		a.push("T1");
		a.push("F");
		a.push(w);
	}else if(TableLL[i][j]==6){
	}else if(TableLL[i][j]==7){
		a.push(w);
	}else if(TableLL[i][j]==8){
		a.push(")");
		a.push("E");
		a.push("(");
	}else{
			cerr<<"CUOWU3"<<endl;
			flag_error=1;
			
	}

}
//LL(1)分析法控制程序人口
bool S(char BDS[]){
 	Stack<string> a; 
	bool flag_error=0;
	int i=0;	
	string x=" ";
	string w=" ";
	a.push("#");
	a.push("E");
	tt:	w=GetNextChar(BDS);	
	pp:	a.pop(x);
	if(BelongVT(x)==1){
			if(x==w){
			goto tt;
			}else{
				flag_error=1;			
			}
		}else if(BelongVT(x)==0){
			if(BelongVN(x)==1){
				CheckTableLL(x,w,a,flag_error);
				goto pp;
			}else if(BelongVN(x)==0){

			
				if(x==w){
				cout<<"这个表达式正确"<<endl;
				return 0;
				}else{
				cerr<<"这个表达式有错误！"<<endl;
				return 0;
				}
		}

		}
			if(flag_error){
				cerr<<"这个表达式有错误！"<<endl;
				return 0;
				}

	return 1;
}


int main()
{	
	char BDS[20]="((a+c)+2)/5#";
	cout<<BDS<<endl;
	S(BDS);
	system ("pause");
	return 0;
}

