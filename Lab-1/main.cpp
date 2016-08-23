#include<iostream>
#include<stack>
#include<cstring>
using namespace std;

void NP_parsing();
int row=6,col=7;
string LRP_table[6][7]={{"","I","+","*","(",")","$"},
                            {"E","TA","","","TA","",""},        //E'=A
                            {"A","","+TA","","","e","e"},
                            {"T","FB","","","FB","",""},        //T'=B
                            {"B","","e","*FB","","e","e"},
                            {"F","I","","","(E)","",""}
                            };


char input[20];

int main()
{

    cout<<"Enter the sting with $:";
    cin>>input;

    for (int x = 0; x < row; x++)
    {
        for(int y=0;y<col;y++)
	    cout << LRP_table[x][y]<<"\t";

        cout<<"\n";
    }
    cout<<"\n\n\n";

    NP_parsing();


    return 0;
}


int Terminal(char key)
{
    if(key=='I' || key=='*' || key=='+' || key=='(' || key==')' )
        return 1;
    else
        return 0;
}

void NP_parsing()
{
    stack<char>Stack;
    int r,c;
    int counter=0;
    string result="";
    char value1;
    char value2;

    Stack.push('$');
    Stack.push('E');


    while(Stack.top()!='$')
    {

        value1=Stack.top();
        switch(value1)
        {
            case 'E':
                r=1;
                break;
            case 'A':
                r=2;
                break;
            case 'T':
                r=3;
                break;
            case 'B':
                r=4;
                break;
            case 'F':
                r=5;
                break;
        }

    value2=input[counter];

        switch(value2)
        {
            case 'I':
                c=1;
                break;
            case '+':
                c=2;
                break;
            case '*':
                c=3;
                break;
            case'(':
                c=4;
                break;
            case ')':
                c=5;
                break;
            case '$':
                c=5;
                break;
        }

        if(Stack.top()==input[counter])
            {

                Stack.pop();

                result.append(sizeof(char),input[counter]);

                cout<<result<<"\n";
                counter++;

            }
        else if(Terminal(Stack.top()))
            {

                cout<<"Input is Error";

            }
        else
            {
                char in[20]={0};
                string temp;
                int lenth;
                temp=LRP_table[r][c];
                lenth=temp.size();
                //cout<<lenth;
                strncpy(in, temp.c_str(),sizeof(in));
                if(in[lenth-1]=='e')
                {
                    Stack.pop();
                }

                else
                {
                    //cout<<Stack.top();
                     Stack.pop();

                    for(int i=lenth-1;i>=0;i--)
                        Stack.push(in[i]);
                }

            }



    }



    if(Stack.top()==input[counter])
        cout<<"Input is Correct";
    else
    {
        cout<<"Input String is Incorrect";
    }


}
