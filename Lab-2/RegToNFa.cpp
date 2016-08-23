#include<iostream>
#include<algorithm>
#include<cstdio>
#include<stack>
#include<cstring>
#include<ctype.h>

using namespace std;
int opernCheck(char C);
int PriorityCheck(char C);
int opCheck(char input1);
void  RegToNfa();
char withDot[]="";
char input[100];
string prefix="";
int startSt=0,endst=1;
int States[50][50]={0};



void Adddot()
{
    int i=0,j=0;
    for(i=0,j=0;i<strlen(input)-1;i++)
    {
        if(!opCheck(input[i])&&!opCheck(input[i+1]))
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

      strcpy(input,withDot);

      cout<<"\nWith Dot\n";
      cout<<input;
}




void InfixToPrefix()
{
    stack<char> Stak;

    strrev(input);
   // cout<<input;
    for(int i=0;i<strlen(input);i++)
    {
        if(opernCheck(input[i]))
        {
            prefix+=input[i];
        }
        else if(input[i]==')')
        {
            Stak.push(input[i]);
        }
        else if(opCheck(input[i]))
        {
            while(!Stak.empty() && Stak.top()!=')' && PriorityCheck(Stak.top()) > PriorityCheck(input[i]))
            {
                prefix+=Stak.top();
                Stak.pop();
            }
            Stak.push(input[i]);
        }
        else if(input[i]=='(')
        {
            while(!Stak.empty() && Stak.top()!=')')
            {
                prefix+=Stak.top();
                Stak.pop();
            }
            Stak.pop();
        }
    }
    while(!Stak.empty())
    {
        prefix+=Stak.top();
        Stak.pop();
    }

    //cout<<prefix;

    strcpy(input,prefix.c_str());
    strrev(input);

    cout<<"\nPrefix \n";
    cout<<input;
}




int opCheck(char input1)
{
    if(input1=='+' || input1=='.' || input1=='*' || input1=='|')
        return 1;
    else
        return 0;
}

int opernCheck(char C)
{
    if(C>='0' && C<='9') return 1;
    if(C>='a' && C<='z') return 1;
    if(C>='A' && C<='Z') return 1;
    return 0;
}

int PriorityCheck(char C)
{
    switch(C)
    {
    case '|': return 1;
    case '.': return 2;
    case '+': return 3;
    case '*': return 4;
    }
}


void  RegToNfa()
{

    stack<char> regEx;
    stack<int> StartTemp;
    stack<int> LastTemp;

    char f1,f2,L1,L2;

    for(int i=0;i<strlen(input);i++)
    {
        //cout<<input[i];
        regEx.push(input[i]);
    }

    while(!regEx.empty())
    {


        if(isalnum(regEx.top()))
        {
            cout<<"\nread: "<<regEx.top()<<"\n";
            States[startSt][endst]=regEx.top();
            StartTemp.push(startSt);
            LastTemp.push(endst);
            startSt=endst+1;
            endst+=2;
        }




        else if(opCheck(regEx.top()))
        {
            if(regEx.top()=='|')
            {
                cout<<"read: "<<regEx.top()<<"\n";
                f1=StartTemp.top();
                StartTemp.pop();
                f2=StartTemp.top();
                StartTemp.pop();
                L1=LastTemp.top();
                LastTemp.pop();
                L2=LastTemp.top();
                LastTemp.pop();

                States[L1][endst]='e';
                States[L2][endst]='e';

                States[startSt][f1]='e';
                States[startSt][f2]='e';

                LastTemp.push(endst);
                StartTemp.push(startSt);

                startSt=endst+1;
                endst+=2;
            }
            else if(regEx.top()=='.')
            {
                cout<<"read: "<<regEx.top()<<"\n";
                f1=StartTemp.top();
                StartTemp.pop();
                f2=StartTemp.top();
                StartTemp.pop();
                L1=LastTemp.top();
                LastTemp.pop();
                L2=LastTemp.top();
                LastTemp.pop();
                States[L1][f2]='e';
                StartTemp.push(f1);
                LastTemp.push(L2);
            }
            else if(regEx.top()=='+')
            {
                cout<<"read: "<<regEx.top()<<"\n";
                f1=StartTemp.top();
                L1=LastTemp.top();
                States[L1][f1]='e';
            }
            else if(regEx.top()=='*')
            {
                cout<<"read: "<<regEx.top()<<"\n";
                f1=StartTemp.top();//2
                L1=LastTemp.top();//1
                States[L1][f1]='e';
                StartTemp.pop();
                LastTemp.pop();

                States[startSt][f1]='e';
                StartTemp.push(startSt);
                States[L1][endst]='e';
                LastTemp.push(endst);
                States[startSt][endst]='e';

                startSt=endst+1;
                endst+=2;
            }



        }
        regEx.pop();
    }


cout<<"Output Regular Expression:\n";


    for(int counterR=0;counterR<=endst;counterR++)
    {
        for(int counterC=0;counterC<=endst;counterC++)
        {
            if(isalnum(States[counterR][counterC]))
            {
                cout<<counterR<<"-------->";
                cout<<counterC<<":";
                printf("%c",States[counterR][counterC]);
                cout<<"\n";


            }
        }
    }

}



int main()
{
    cout<<"Enter a Regular Expression: ";
    scanf("%s",input);
    Adddot();
    InfixToPrefix();
    RegToNfa();


    return 0;





}
