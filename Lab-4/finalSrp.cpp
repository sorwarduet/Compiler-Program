#include<iostream>
#include<stack>
#include<cstring>
bool isShift(char z);
bool isReduce(char x);
using namespace std;
bool isShift(stack<char>mystack4);
bool partialmatch(stack<char>mystack2);
bool isReduce(stack<char>mystack3);
void print(stack<char>mystack6,int d);
int t=0;
int p=0;
int a=0;
char inputarr[10]={'i','*','i','+','i','$'};
stack<char>mystack;
stack<char>mystack1;
char grammerarray[6][8]={"E>E+T","E>T","T>T*F","T>F","F>(E)","F>i"};
char rightsidegrammer[6][5];
char ch;
char ar[5]={'\0'};
string str;
int temp=0;
int temp1=0;
int index=0;
char arr[10]={'\0'};
char newarr[10]={'\0'};
int main()
{
    mystack.push('$');
     for(int i=0;i<6;i++)
    {
        cout<<grammerarray[i];
        cout<<endl;
    }
     for(int i=0;i<6;i++)
     {
         p=0;
        for( int j=2;grammerarray[i][j]!='\0';j++)
        {
            rightsidegrammer[i][p]=grammerarray[i][j];
            p++;
        }
     }
      for(int i=0;i<6;i++)
      {
        cout<<rightsidegrammer[i];
        cout<<endl;
      }
      cout<<"\n\n\nSTACK  "<<"\t"<<"INPUT "<<"\t"<<"ACTION ";
    cout<<"\n-------------------------------------------------------";
    cout<<"\n"<<mystack.top()<<"\t";
    for(int i=index;i<6;i++)
      {
        cout<<inputarr[i];
      }
for(int a=0; inputarr[a]!='$';a++ )
{
     if(isShift(mystack))
     {
         if(mystack.size()==2 && mystack.top()=='E' && inputarr[index]=='$')
        cout<<"accepted";
        else
        cout<<"not accepted";
     }
     //else
     //{
       //  if(isReduce(mystack));
     //}
     //if(partialmatch(mystack))
     //{
     //}
     //else
     //{
       //  if(isReduce(mystack));
     //}
}
}
bool partialmatch(stack<char>mystack2)
{
    int k=0,p=0,q=0;
    arr[k]=mystack.top();
    arr[k+1]=inputarr[index];
   // arr[k+1]=inputarr[index];
    for(int i=6;i>=0;i--)
     {
        for( int j=0;grammerarray[i][j]!='\0';j++)
        {
            if((rightsidegrammer[i][j]==arr[p] && rightsidegrammer[i][j+1]==arr[p+1]))
            {
                cout<<"\tpartial match and shift "<<inputarr[index];
                cout<<"\n-------------------------------------------------------";
                mystack.push(inputarr[index]);
                index++;
                cout<<endl;
                    mystack1=mystack;
                    print(mystack1,index);
                    isShift(mystack);
                return true;
            }
        }
     }
     return false;
}
bool isReduce(stack<char>mystack3)
{
    int k =0;
    if(mystack.size()==4)
    {
        mystack1=mystack;
        while(mystack1.top()!='$')
        {
        newarr[k]=mystack1.top();
        mystack1.pop();
        k++;
        }
    strrev(newarr);
    string str="";
         str+=newarr;
         for(int i=6;i>=0;i--)
         {
            if( rightsidegrammer[i]==str )
            {
                temp=i;
                mystack.pop();
                mystack.pop();
                mystack.pop();
                mystack.push(grammerarray[i][0]);
                cout<<"\tReduce By  "<<grammerarray[i][0]<<"->"<<rightsidegrammer[i];
                cout<<"\n-------------------------------------------------------";
                cout<<endl;
                    mystack1=mystack;
                    print(mystack1,index);
            }
         }
    }
     for(int i=6;i>=0;i--)
     {
        string str="";
         str+=mystack.top();
            if(rightsidegrammer[i]==str)
            {
                cout<<"\tReduce By  "<<grammerarray[i][0]<<"->"<<str;
                cout<<"\n-------------------------------------------------------";
                 mystack.pop();
                 mystack.push(grammerarray[i][0]);
                 cout<<endl;
                    mystack1=mystack;
                    print(mystack1,index);
                    if(mystack.size()==4)
                    {
                        isReduce(mystack);
                    }
                if(partialmatch(mystack))
                {
                    partialmatch((mystack));
                }
                if(isShift(mystack))
                {
                    isShift(mystack);
                }
            }
     }
     return false;
}
bool isShift(stack<char>mystack4)
{
    for(int i=6;i>=0;i--)
     {
         string str="";
         str+=inputarr[index];
            if(rightsidegrammer[i]==str)
            {
                mystack.push(inputarr[index]);
                cout<<"\tShift  "<<str;
                cout<<"\n-------------------------------------------------------";
                cout<<endl;
                ++index;
                    mystack1=mystack;
                    print(mystack1,index);
                    if(isReduce(mystack))
                    {
                    }
                    return true;
            }
     }
     return false;
}
void print(stack<char>mystack6,int d)
{
    mystack1=mystack6;
    stack<char>printstack;
                    while(mystack1.empty()==false)
                    {
                     printstack.push(mystack1.top());
                     mystack1.pop();
                    }
                    while(printstack.empty()==false)
                    {
                        cout<<printstack.top();
                        printstack.pop();
                    }
                    cout<<"\t";
                    for(int i=index;inputarr[i]!='\0';i++)
                    {
                    cout<<inputarr[i];
                    }
}
