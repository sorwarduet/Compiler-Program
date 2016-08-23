#include<bits/stdc++.h>
using namespace std;
char operators[]="|*+.";
char withDot[]="";
//char input[]= "abc";
char input[]= "(a|b)*abc";
char prefixArray[]="";
char forNfa[200][200];
void Adddot();
void infixToPrefix();
int priority(char element);
void regularToNfa();
int state=0,final_State;

int main()
{
    Adddot();
    //printf("%s\n",withDot);
    strcpy(input,withDot);
    infixToPrefix();
    //printf("%s\n",prefixArray);
    regularToNfa();
            for(int k=0;k<=state;k++)
            {
                for(int j=0;j<=state;j++)
                {
                    if(forNfa[k][j]=='a' || forNfa[k][j]=='b' || forNfa[k][j]=='c' || forNfa[k][j]=='0' || forNfa[k][j]=='1' )
                    {
                         printf("%d - %d  :%c",k,j,forNfa[k][j]);
                         printf("\n");
                    }
                    else if(forNfa[k][j]=='&')
                    {
                        printf("%d - %d  :%c",k,j,238);
                        printf("\n");
                    }
                }
            }
    printf("final State = %d",final_State);
    return 0;
}
void regularToNfa()
{
    int top=0,bleow,j;
     //printf(" ");
    for(int i=0;i<=strlen(prefixArray)-1;i++)
    {
        //printf("%d",!isalnum(prefixArray[0]));
        if(isalnum(prefixArray[i]) || strlen(prefixArray)==1 && !isalnum(prefixArray[0]) )
        {

            //printf("1 ");
                i--;
                if(prefixArray[i]=='|')
                {
                    state=top;
                    forNfa[state][state+1]='&';
                    forNfa[state+2][state+3]=prefixArray[i+1];
                    forNfa[state+4][state+5]=prefixArray[i+2];
                    forNfa[state+1][state+2]='&';
                    forNfa[state+1][state+4]='&';
                    forNfa[state+3][state+6]='&';
                    forNfa[state+5][state+6]='&';
                    forNfa[state+6][state+7]='&';
                    top=state+7;
                    bleow=state;
                    for(j=i;j<strlen(prefixArray)-3;j++)
                    {
                        prefixArray[j]=prefixArray[j+3];
                    }
                    prefixArray[j]='\0';
                    final_State=state+7;
                   // printf("1 ");
                    i--;
                    if(i<0)
                    break;
                   // printf("%s\n",prefixArray);
                }
                else if(prefixArray[i]=='*')
                {
                    forNfa[top][bleow]='&';
                    forNfa[bleow+1][top-1]='&';
                    for(j=i;j<strlen(prefixArray)-1;j++)
                    {
                        prefixArray[j]=prefixArray[j+1];
                    }
                    prefixArray[j]='\0';
                    final_State=top;
                    i--;

                  // printf("%s\n",prefixArray);

                }
                else if(prefixArray[i]=='+')
                {
                    forNfa[top][bleow]='&';
                    //forNfa[bleow][top]='&';
                    for(j=i;j<strlen(prefixArray)-1;j++)
                    {
                        prefixArray[j]=prefixArray[j+1];
                    }
                    prefixArray[j]='\0';
                    final_State=top;
                    i--;

                  // printf("%s\n",prefixArray);

                }
                else if(prefixArray[i]=='.')
                {
                    //printf("%d",i);
                    state=top;
                    //forNfa[state][state+1]='&';
                    forNfa[state][state+1]=prefixArray[i+1];
                    //printf("%c\n",forNfa[state+1][state+2]);
                    //forNfa[state+2][state+3]='&';
                    top=state+1;
                    bleow=state;
                    for(j=i;j<strlen(prefixArray)-2;j++)
                    {
                        prefixArray[j]=prefixArray[j+2];
                    }
                    prefixArray[j]='\0';
                    //printf("%s\n",prefixArray);
                    final_State=top;
                    if(prefixArray[i-1]=='*')
                    {
                        //printf("rrrrrrrrr\n");
                        state=top;
                        //forNfa[state][state+1]='&';
                        forNfa[state+1][state+2]=prefixArray[i];
                        top=state+2;
                        bleow=state;
                        for(j=i;j<strlen(prefixArray)-1;j++)
                        {
                            prefixArray[j]=prefixArray[j+1];
                        }
                        prefixArray[j]='\0';
                        final_State=top;
                       //printf("%c\n",forNfa[state+1][state+2]);
                    }

                    i--;
//                    printf("%s\n",prefixArray);
                }

            }
            if(isalnum(prefixArray[0])&&prefixArray[1]=='\0')
                break;
                int flag=0;
            for(int k=0;k<=strlen(prefixArray)-1;k++)
            {
                if(isalnum(prefixArray[k]))
                   flag=1;
            }
            if(flag==0)
                break;
    }
    state=top;
    if(isalnum(prefixArray[0])&&prefixArray[1]=='\0' )
    {
        //forNfa[state][state+1]='&';
        forNfa[state][state+1]=prefixArray[0];
        state=state+1;
        final_State=state;
    }

}
int operatorCheck(char input1)
{
    for(int i=0;i<strlen(operators);i++)
    {
        if(operators[i]==input1)
            return 1;
    }
    return 0;
}
void Adddot()
{
    int i=0,j=0;
    for(i=0,j=0;i<strlen(input)-1;i++)
    {
        if(!operatorCheck(input[i])&&!operatorCheck(input[i+1]))
        {
            if(input[i]=='(' || input[i+1]==')')
                withDot[j++]=input[i];
            else
            {
              withDot[j++]=input[i];
                withDot[j++]='.';
            }
        }
        else
            withDot[j++]=input[i];
    }
      withDot[j++]=input[i];
      withDot[j++]='\0';
}

void infixToPrefix()
{
    strrev(input);
   // printf("%d\n",strlen(input));
    char stackArray[20];
    stackArray[0]='#';
    //printf("%c\n",input[10]);
    int i,j=0,k=0;
    for(i=0;i<strlen(input);i++)
    {
        if(isalnum(input[i]))
            prefixArray[j++]=input[i];
        else if(input[i]==')')
        {
            k++;
            stackArray[k]=input[i];
        }
        else if(operatorCheck(input[i]))
        {
            while(stackArray[k]!='#' && stackArray[k]!=')' && (priority(stackArray[k])> priority(input[i])))
            {
                prefixArray[j++] = stackArray[k];
                k--;
            }
            k++;
            stackArray[k]=input[i];
            stackArray[k+1]='\0';
            //printf("%s\n",stackArray);
        }
        else if(input[i]=='(')
            {
                while(stackArray[k]!= ')')
                {
                   prefixArray[j++] = stackArray[k--];
                }
                k--;
            }
    }
    while(stackArray[k]!='#')
    {
        prefixArray[j++] = stackArray[k--];
    }
    prefixArray[j]='\0';
    strrev(prefixArray);
}
int priority(char element)
{
    switch(element)
    {
    case '#': return 0;
    case '|': return 1;
    case '.': return 2;
    case '+': return 3;
    case '*': return 4;
    }
}
