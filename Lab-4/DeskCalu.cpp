#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
char gra[10][10];
char inputStr[15];
char stack[20];
char value[10]="";
char action[20];
char op;
int i=0,j=0,k=0,m=0,v=0,s=0;
char n1[10],n2[10];
int length,num1,num2,result,ipLength;

int isDigit(char ch)
{
    if(ch>='0' && ch<='9')
    return 1;
    else
    return 0;
}
int Operator(char ch)
{
    if(ch=='+' || ch=='-' || ch=='/' || ch=='*')
        return 1;
    else
    return 0;
}

void checkGra(char ch)
{
    if(isDigit(ch))
    {
        if(stack[j-1]=='I')
        {
            j=j-1;
            strcpy(action,"Reduce by I->ID");
            stack[j]='I';
            stack[j+1]='\0';
            value[v]=ch;
            value[v+1]='\0';
            v++;
        }
        else
        {
            strcpy(action,"Reduce by I->D");
            stack[j]='I';
            value[v]=ch;
            value[v+1]='\0';
            v++;
        }
        cout<<endl<<inputStr<<"\t\t"<<stack<<"\t"<<value<<"\t"<<action;

        if((Operator(inputStr[i+1]) || inputStr[i+1]=='$') && stack[j]=='I')
        {
            strcpy(action,"Reduce by E->I");
            stack[j]='E';
            cout<<endl<<inputStr<<"\t\t"<<stack<<"\t"<<value<<"\t"<<action;
        }

        if((strcmp(stack,"E*E")==0)||(strcmp(stack,"E+E")==0))
        {
            int x,y,z;m=0;
         strcpy(action,"Reduce by E->E*E");
          j=0;
          stack[j]='E';
          stack[j+1]='\0';
          length=strlen(value);
          for(x=0,y=0,z=0;x<length;x++)
          {
              if(!Operator(value[x]) && m==0)
              {
                n1[y++]=value[x];
                continue;
              }
              else if(Operator(value[x]))
              {
                  n1[y]='\0';
                  op=value[x];
                  num1=atoi(n1);
                  m=1;
                  continue;
              }
              if(m==1)
              {
                  n2[z++]=value[x];
              }
          }
          n2[z]='\0';
          num2=atoi(n2);
          if(op=='*')result=num1*num2;
          if(op=='+')result=num1+num2;
          itoa(result,value,10);
          v=strlen(value);
          cout<<endl<<inputStr<<"\t\t"<<stack<<"\t"<<value<<"\t"<<action;
        }
        if(strcmp(stack,"E")==0 && inputStr[ipLength-1]=='$' && inputStr[ipLength-2]==' ')
        {
            strcpy(action,"Shift-> $");
            stack[j+1]='$';
            stack[j+2]='\0';
            strcpy(inputStr,"");
            cout<<endl<<inputStr<<"\t\t"<<stack<<"\t"<<value<<"\t"<<action;
        }
        if(strcmp(stack,"E$")==0)
           {
               strcpy(stack,"S");
               cout<<endl<<inputStr<<"\t\t"<<stack<<"\t"<<value<<"\t"<<action;
           }
        j++;

    }

    if(Operator(ch))
    {
        value[v]=ch;
        value[v+1]='\0';
        v++;
    }
}


int main()
{
    int np;
    char ch;
    freopen("input.txt","r",stdin);
    cin>>np;
    for(i=0;i<np;i++)
    {
        cin>>gra[i];
    }
    cin>>inputStr;

    ipLength=strlen(inputStr);
    cout<<"  input \tstack \tvalue \taction";
    for(i=0;inputStr[i]!='$';i++)
    {
        if(isDigit(inputStr[i]))
        {
            strcpy(action,"Shift->Digit");
            ch=inputStr[i];
            stack[j]=inputStr[i];
            stack[j+1]='\0';
            inputStr[i]=' ';
            cout<<endl<<inputStr<<"\t\t"<<stack<<"\t"<<value<<"\t"<<action;
            checkGra(ch);
        }
        else if(Operator(inputStr[i]))
        {
            strcpy(action,"Shift->Operator");
            ch=inputStr[i];
            stack[j]=inputStr[i];
            stack[j+1]='\0';
            inputStr[i]=' ';
            j++;
            cout<<endl<<inputStr<<"\t\t"<<stack<<"\t"<<value<<"\t"<<action;
            checkGra(ch);
        }
}
return 0;
}



