// 词法分析器.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include "iostream"
#include <string.h>
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include<conio.h>
#include <string>
#include <sstream> 
#define iTAndKT 20
#define cT 21
#define sT 22
#define CT 23
#define PT 24
/*---------------------
词法分析器
---------------------*/

using namespace std;
//定义Token的结构体
struct Token
{
string state;
int token;
};
struct Token Token_T[200];
struct Token ptCache[50];
struct Token ktCache[50];
int Tokenlen = 0;      //Token的长度
int pt_Tokenlen=0;		//pt_Tokenlen的长度
int kt_Tokenlen=0;		//kt_Tokenlen的长度
static int flag=3;		//输入程序的序号
int id_kt=4;
int id_pt=10;
char *kt[6]={"int","main","void","if","else","char"};		//kt表的内容
char *pt[16]={">=","<=","==","=",">","<","+","-",".","/","{","}",",",";","(",")"};		//pt表的内容
char *it[100];			//it表的内容
char *ct[100];			//ct表的内容
bool IsEof=1;

//从.txt文件里的内容传递到字符串
void TxtToSring(char* a){
FILE *fp;
 if((fp=fopen(".//pro.txt","rt"))==NULL){
       printf("\nCannot open file strike any key exit!");
	   getch();
	   exit(1);}
 fseek(fp, SEEK_SET,0);
 fread(a,1,200,fp);
 fclose(fp);
 }

//判断字符是否在kt表
bool JudgeKt(string Word){
	for(int i=0;i<6;i++){
		if(strcmp(kt[i],Word.c_str())==0){	 
		  return 1;		 
		}
	}
	return 0;
}
//判断字符是否在pt表
bool JudgePt(string str){
for(int i=0;i<16;i++){
	if(strcmp(pt[i],str.c_str())==0){
		  return 1;		  
		}
	}
	return 0;
}
//建立当前阶段已有的kt的缓存数据
int kt_cache(string State){
	for(int i=0;i<kt_Tokenlen;i++){
		if(strcmp(State.c_str(),ktCache[i].state.c_str())==0){
			return ktCache[i].token;		
		}
	}
	return 0;
}
//建立当前阶段已有的pt的缓存数据
int pt_cache(string State){
	for(int i=0;i<pt_Tokenlen;i++){
		if(strcmp(ptCache[i].state.c_str(),State.c_str())==0){	  
		  return  ptCache[i].token;
		}	
	}
	return 0;
}

void GetToken(int Token_id,string State){
	if(Token_id==4){
		if(kt_cache(State)!=0){	
		Token_T[Tokenlen].token=kt_cache(State);
		Token_T[Tokenlen].state=State;
		Tokenlen++;
		}else{	
			Token_T[Tokenlen].token=id_kt; 
			Token_T[Tokenlen].state=State;
			ktCache[kt_Tokenlen].token =id_kt;
			ktCache[kt_Tokenlen].state =State;
			id_kt++;
			Tokenlen++;
			kt_Tokenlen++;
			}
	}else if(Token_id==5){
		if(pt_cache(State)!=0){
		Token_T[Tokenlen].token=pt_cache(State);
		Token_T[Tokenlen].state=State;
		Tokenlen++;
		}else if(pt_cache(State)==0){
				Token_T[Tokenlen].token=id_pt;  
				Token_T[Tokenlen].state=State;  
				ptCache[pt_Tokenlen].token =id_pt;
				ptCache[pt_Tokenlen].state =State;
			id_pt++;
			Tokenlen++;
			pt_Tokenlen++;
			}	
	}else if(Token_id==0){
		Token_T[Tokenlen].token=0;
		Token_T[Tokenlen].state=State;
		Tokenlen++;
	}else if(Token_id==1){
		Token_T[Tokenlen].token=1;
		Token_T[Tokenlen].state=State;
		Tokenlen++;
	}else if(Token_id==2){
		Token_T[Tokenlen].token=2;
		Token_T[Tokenlen].state=State;
		Tokenlen++;
	}else if(Token_id==3){
		Token_T[Tokenlen].token=3;
		Token_T[Tokenlen].state=State;	
		Tokenlen++;
	}

}
//获得下一个字符
char GetNextChar(char *a){
	
	char ch;
	ch=a[flag];
	if(ch=='\0'){
	
	 return ch;
	}
	else{
	
		flag++;
	return ch;
	}
}
//退倒上一个字符
void GetBackChar(){
      flag--;
}
//判断该字符是否为空字符
bool JudgeKongOrTab(char a){
	if(a==' '){
	  return 1;
	}else if(a=='/t'){
		return 1;
	}else if(a=='/n'){
		return 1;
	}
	else
		return 0;
}

//判断该字符是否为数字
bool JudgeNumber(char c){
	if(c>=48&&c<=58){
	   return 1;
	}else
	{
	return 0;
	}
}
//判断该字符是否为英文字母
bool JudgeLetter(char a){
	if(isalpha(a)==1||isalpha(a)==2){
	return 1;
	}
	else
		return 0;
}

//词法分析的自动机
void DFA(char Pro[]){
		
	bool IsSave;
	char c;
	int Token_id=0;	
	string  CurrentToken="";
	string  TokenStr="";
	int CurrentState=1;
	while(CurrentState!=0){
		c=GetNextChar(Pro);
		if(c=='\0')
		{
			IsEof=0;
			return;
		}
		IsSave=true;
	    switch(CurrentState){
		case 1:
			if(JudgeNumber(c)){
				CurrentState=3;
			}else if(JudgeLetter(c)){
				CurrentState=2;
			}else if(c==' '||c=='\t'||c=='\n'){
				IsSave=false;
			}else if(c=='\''){
                CurrentState=9;
			}else if(c=='\"'){
                CurrentState=11;
			}else if(c=='>'){
                CurrentState=4;
			}else if(c=='<'){
                CurrentState=5;
			}else if(c=='='){
                CurrentState=6;
			}else{
                CurrentState=18;
			}
			break;
        case 2:
            if(!JudgeLetter(c)&&!JudgeNumber(c)){
			
                CurrentState=20;
                GetBackChar();
                IsSave=false;			
            }
			break;
	 	case iTAndKT:
			
			if(JudgeKt(TokenStr)){
				Token_id=4;			
			}
			else{
				
			  Token_id=0;
			}
			CurrentState=0;
			 GetBackChar();
             IsSave=false;
			break;
			 
        case 3:
            if(c=='.'){
                 CurrentState=8;
            }
            else if(!JudgeNumber(c)&&c!='.'){
                CurrentState=23;
                GetBackChar();
                IsSave=false;
            }
			break;
        case 8:
            if(JudgeNumber(c)){
                CurrentState=7;
				
            }
			break;
        case 7:
            if(!JudgeNumber(c)){
                CurrentState=23;
                GetBackChar();
                IsSave=false;
            }
			break;
		case CT:
			
			Token_id=3;
			CurrentState=0;
		    GetBackChar();
            IsSave=false;
			break;
			 
        case 9:
            if(JudgeLetter(c)){
                CurrentState=10;
				
            }
			break;
        case 10:
            if(c=='\''){
                CurrentState=16;				
            }
			break;
        case 16:           
                CurrentState=cT;
                GetBackChar();
                IsSave=false;
				break;
		case cT:
			
			Token_id=1;
			CurrentState=0;
		    GetBackChar();
            IsSave=false;
			break;
			 

        case 11:
            if(JudgeLetter(c)){
                CurrentState=12;
			
            }
			break;
        case 12:
            if(c=='\"'){
                CurrentState=17;
            }else if(JudgeLetter(c)){
                CurrentState=12;
            }
			break;
        case 17:
            
				CurrentState=sT;
                GetBackChar();
                IsSave=false;
				break;
		case sT:
			Token_id=2;
			CurrentState=0;
		    GetBackChar();
            IsSave=false;
			break;
         case 4:
            if(c=='='){
                CurrentState=13;
            }else{
			   CurrentState=PT;
               GetBackChar();
               IsSave=false;
            }
			break;
         case 13:
            
               CurrentState=PT;
               GetBackChar();
               IsSave=false;
               break;

		 case PT:
			 if(JudgePt(TokenStr)){
				Token_id=5;
			
			}
			 CurrentState=0;
			 GetBackChar();
             IsSave=false;
			 break;

         case 5:
             if(c=='='){
                CurrentState=14;
             }else {
              CurrentState=PT;
              GetBackChar();
              IsSave=false;
             }
			 break;
         case 14:
               CurrentState=PT;
               GetBackChar();
               IsSave=false;
               break;
         case 6:
             if(c=='='){
                CurrentState=15;
             }
             else{
              CurrentState=PT;
              GetBackChar();
              IsSave=false;
             }
			 break;
         case 15:
              CurrentState=PT;
              GetBackChar();
              IsSave=false;
              break;
         case 18:
			 CurrentState=PT;
             GetBackChar();
             IsSave=false;
             break;


        default:
            cout<<"error"<<endl;
            break;
	    }
        if(IsSave){
			TokenStr.push_back(c);
        }	
		if(CurrentState==0){
			CurrentToken=TokenStr;
			GetToken(Token_id,CurrentToken);
		       }	
	}
}

//词法分析的入口函数
void Scanning(){
	char Pro[200]={0};
	TxtToSring(Pro);
	while(IsEof){
    DFA(Pro);	
	}
}
//打印Token
void print_Token(){
	int a=Tokenlen;
 int i=0;
 while(a){
	 cout<<Token_T[i].token<<"     ->        "<<Token_T[i].state<<endl;
	 a--;
	 i++;
 }

}
int main()
{
 Scanning();
 print_Token();
 system ("pause");
}
