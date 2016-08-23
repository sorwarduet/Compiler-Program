#include<iostream>
#include<stack>
#include<cstring>
using namespace std;
bool isShift(stack<char>mystack4);
bool partialmatch(stack<char>mystack2);
bool isReduce(stack<char>mystack3);
bool isDigit(char a);
bool isOperator(char q);
void print(stack<char>mystack6,int d);
void DigitValue(char x,int u,stack<char>mystack5,char b);
char s='\0';
int t=0;
int p=0;
int a=0;
int u=0;
int result=0;
char inputarr[10]={'2','0','*','5','5','+','4','$'};
stack<char>mystack;
stack<char>mystack1;
stack<char>StackVal;
stack<char>StackVal1;
stack<int>value;
stack<int>value1;
char grammerarray[7][9]={"S>E$","E>E+E","E>E*E","E>(E)","E>I","I>Idigit","I>digit"};
char rightsidegrammer[7][7];
char ch;
char ar[10]={'\0'};
string str;
int temp=0;
int temp1=0;
int index=0;
char arr[10]={'\0'};
char newarr[10]={'\0'};
char lastarr[10]={'\0'};
int main()
{
    mystack.push('_');
    StackVal.push('_');
     for(int i=0;i<7;i++)//for grammer print
     {
        cout<<grammerarray[i];
        cout<<endl;
     }
     for(int i=0;i<7;i++)//for separate right side grammer
     {
         p=0;
        for( int j=2;grammerarray[i][j]!='\0';j++)
        {
            rightsidegrammer[i][p]=grammerarray[i][j];
            p++;
        }
     }
      for(int i=0;i<7;i++)//for printing right side grammer
      {
        cout<<rightsidegrammer[i];
        cout<<endl;
      }
      cout<<"\n\n\nINPUT  "<<"\t\t"<<"STATE "<<"\t"<<"Value"<<"\t"<<"Production Used ";
    cout<<"\n-------------------------------------------------------\n";
    for(int i=index;i<10;i++)
      {
        cout<<inputarr[i];
      }
      cout<<"\t";
      cout<<mystack.top()<<"\t";
      StackVal1=StackVal;
      while(StackVal1.empty()==false)
      {
          cout<<StackVal1.top();
          StackVal1.pop();
      }
for(int a=0; inputarr[a]!='\0';a++ )
{
     if(isShift(mystack))
     {
         if(mystack.size()==2 && mystack.top()==grammerarray[0][0] && inputarr[index]=='\0')
         cout<<"accepted";
        //else
        //cout<<"not accepted";
     }
     else
     {
         if(isReduce(mystack));
     }
}
}
bool partialmatch(stack<char>mystack2)//for partial such E* match shift
{
    int k=0,p=0,q=0;
    arr[k]=mystack.top();
    arr[k+1]=inputarr[index];
    for(int i=7;i>=0;i--)
     {
        for( int j=0;grammerarray[i][j]!='\0';j++)
        {
            if((rightsidegrammer[i][j]==arr[p] && rightsidegrammer[i][j+1]==arr[p+1]))
            {
                mystack.push(inputarr[index]);
                index++;
                    mystack1=mystack;
                    print(mystack1,index);
                    if(isOperator(inputarr[index-1]))
                       {
                           DigitValue(inputarr[index-1],2,mystack,s);
                       }
                    else if(inputarr[index-1]=='$')
                        {
                            DigitValue(inputarr[index-1],6,mystack,s);
                        }
                    isShift(mystack);
                    isReduce(mystack);
                return true;
            }
        }
     }
     return false;
}
bool isReduce(stack<char>mystack3)
{
    int q=0;
            mystack1=mystack;
            mystack1.pop();
            if(isDigit(mystack.top()))//for I->Idigit
            if(mystack1.top()=='I')
            {
                        string str4="";
                        str4="Idigit";
                        for(int i=7;i>=0;i--)
                        {
                        if(rightsidegrammer[i]==str4)
                         {
                            temp1=i;
                            mystack.pop();
                            mystack.pop();
                            mystack.push(grammerarray[temp1][0]);
                        }
                    }
                        mystack1=mystack;
                        print(mystack1,index);
                    if(isDigit(inputarr[index-1]))
                    {
                        DigitValue(inputarr[index-1],1,mystack,s);
                    }
                    cout<<"\tProduction  "<<grammerarray[temp1][0]<<"->"<<str4;
                    if(isShift(mystack));
            }
    int k =0;
    if(mystack.size()==4)//for E->E*E
    {
        mystack1=mystack;
        while(mystack1.top()!='_')
        {
        newarr[k]=mystack1.top();
        mystack1.pop();
        k++;
        }
    strrev(newarr);
    string str="";
         str=newarr;
         for(int i=6;i>=0;i--)
         {
            if( rightsidegrammer[i]==str )
            {
                temp=i;
                mystack.pop();
                mystack.pop();
                mystack.pop();
                mystack.push(grammerarray[i][0]);
                    mystack1=mystack;
                    print(mystack1,index);
                    s=rightsidegrammer[temp][1];
                    if(!isDigit(inputarr[index]))
                    DigitValue(inputarr[index-1],5,mystack,s);
                    cout<<"\tProduction  "<<grammerarray[temp][0]<<"->"<<rightsidegrammer[temp];
            }
         }
    }
            int e=0;
                if(mystack.size()==3 && mystack.top()=='$' )//for S->E$
                    {
                        mystack1=mystack;
                        while(mystack1.top()!='_')
                        {
                            lastarr[e]=mystack1.top();
                            mystack1.pop();
                            e++;
                        }
                        strrev(lastarr);
                        string str5="";
                        str5=lastarr;
                        for(int i=7;i>=0;i--)
                        {
                        if(rightsidegrammer[i]==str5)
                         {
                            temp1=i;
                            mystack.pop();
                            mystack.pop();
                            mystack.push(grammerarray[i][0]);
                            }
                        }
                        mystack1=mystack;
                        print(mystack1,index);
                    if( mystack.top()==grammerarray[temp1][0] )
                    DigitValue(inputarr[index-1],7,mystack,s);
                    cout<<"\tProduction  "<<grammerarray[temp1][0]<<"->"<<str5;
}
     for(int i=7;i>=0;i--)
     {
        string str1="";
         if(isDigit(mystack.top()))
         {
             str1="digit";//for I->digit
         }
         else
         {
             str1=mystack.top();//for E->I etc
         }
         mystack1=mystack;
         mystack1.pop();
            if(rightsidegrammer[i]==str1 && mystack1.top()!='I')
            {
                 temp=i;
                 mystack.pop();
                 mystack.push(grammerarray[i][0]);
                    mystack1=mystack;
                    print(mystack1,index);
                    if(isDigit(inputarr[index-1]) && temp==6)
                    {
                        if(StackVal.size()==1)
                        {
                            DigitValue(inputarr[index-1],0,mystack,s);
                        }
                        else if(StackVal.size()==2)
                        {
                            DigitValue(inputarr[index-1],3,mystack,s);
                        }
                    }
                    else
                    {
                        if( value.size()==2 && StackVal.size()==1)
                        {
                            DigitValue(inputarr[index-1],4,mystack,s);
                        }
                        else
                        {
                            DigitValue(inputarr[index-1],2,mystack,s);
                        }
                    }
                    cout<<"\tProduction   "<<grammerarray[temp][0]<<"->"<<str1;
                    if(mystack.size()==4)
                    {
                        isShift(mystack);
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
    string str2="";
    for(int i=7;i>=0;i--)
     {
         if(isDigit(inputarr[index]))
         {
             str2="digit";//for digit shift
         }
         else
         {
             str2=mystack.top();//for shit
             isReduce(mystack);
         }
            if(rightsidegrammer[i]==str2)
            {
                mystack.push(inputarr[index]);
                ++index;
                    mystack1=mystack;
                    print(mystack1,index);
                    if(isDigit(inputarr[index-1]))
                    {
                        DigitValue(inputarr[index-1],2,mystack,s);
                    }
                    if(isReduce(mystack))
                    {
                    }
                    return true;
            }
     }
     return false;
}
bool isDigit(char a)
{
    if(a>='0' && a<='9')
    return true;
    return false;
}
void DigitValue(char x, int u,stack<char>mystack5,char b)
{
    int v;
    char z=x;
    if(z=='0')
    v=0;
    else if(z=='1')
    v=1;
    else if(z=='2')
    v=2;
    else if(z=='3')
    v=3;
    else if(z=='4')
    v=4;
    else if(z=='5')
    v=5;
    else if(z=='6')
    v=6;
    else if(z=='7')
    v=7;
    else if(z=='8')
    v=8;
    else if(z=='9')
    v=9;
    int arr[10]={0};
    int p=0;
    if(u==0)
    {
        value.push(v);
        value1=value;
        cout<<"\t";
        while(value1.empty()==false)
        {
            cout<<value1.top();
            value1.pop();
        }
        while(StackVal.empty()==false)
        {
            StackVal.pop();
        }
        while(mystack5.size()-1>value.size()+StackVal.size())
        {
            StackVal.push('_');
        }
        StackVal1=StackVal;
        while(StackVal1.empty()==false)
        {
            cout<<StackVal1.top();
            StackVal1.pop();
        }
    }
    else if(u==1)
    {
        value.push(v);
        int d=0;
        for(int i=0;i<2;i++)
        {
            arr[d]=value.top();
            value.pop();
            ++d;
        }
        result=arr[1]*10+arr[0];
        value.push(result);
        value1=value;
        stack<int>value2;
        cout<<"\t";
        while(value1.empty()==false)
        {
            value2.push(value1.top());
            value1.pop();
        }
        if(value2.size()==2)
        {
            cout<<value2.top();
            value2.pop();
            while(StackVal.empty()==false)
            {
            StackVal.pop();
            }
            while(mystack5.size()-1>value.size()+StackVal.size())
            {
            StackVal.push('_');
            }
            StackVal1=StackVal;
        while(StackVal1.empty()==false)
        {
            cout<<StackVal1.top();
            StackVal1.pop();
        }
        cout<<value2.top();
            value2.pop();
        }
        else
        {
            while(value2.empty()==false)
            {
                cout<<value2.top();
                value2.pop();
            }
        }
    }
    else if(u==2)
    {
        value1=value;
        stack<int>value2;
        cout<<"\t";
        while(value1.empty()==false)
        {
            value2.push(value1.top());
            value1.pop();
        }
        if(value2.size()==2)
        {
            cout<<value2.top();
            value2.pop();
            while(StackVal.empty()==false)
            {
            StackVal.pop();
            }
            while(mystack5.size()-1>value.size()+StackVal.size())
            {
            StackVal.push('_');
            }
            StackVal1=StackVal;
            cout<<StackVal1.top();
            StackVal1.pop();
            cout<<value2.top();
            value2.pop();
            cout<<StackVal1.top();
            StackVal1.pop();
        }
        else
        {
            while(value2.empty()==false)
            {
                cout<<value2.top();
                value2.pop();
            }
            while(StackVal.empty()==false)
            {
            StackVal.pop();
            }
            while(mystack5.size()-1>value.size()+StackVal.size())
            {
            StackVal.push('_');
            }
            StackVal1=StackVal;
            while(StackVal1.empty()==false)
            {
                cout<<StackVal1.top();
                StackVal1.pop();
            }
        }
    }
    else if(u==3)
    {
        value.push(v);
        while(StackVal.empty()==false)
            {
            StackVal.pop();
            }
        value1=value;
        stack<int>value2;
        while(value1.empty()==false)
        {
            value2.push(value1.top());
            value1.pop();
        }
        cout<<"\t";
        while(value2.empty()==false)
        {
            cout<<value2.top();
            value2.pop();
            while(mystack5.size()-1>value.size()+StackVal.size())
            {
            StackVal.push('_');
            }
            StackVal1=StackVal;
        while(StackVal1.empty()==false)
        {
            cout<<StackVal1.top();
            StackVal1.pop();
        }
        cout<<value2.top();
            value2.pop();
        }
    }
    else if(u==4)
    {
        while(StackVal.empty()==false)
            {
            StackVal.pop();
            }
        value1=value;
        stack<int>value2;
        while(value1.empty()==false)
        {
            value2.push(value1.top());
            value1.pop();
        }
        cout<<"\t";
        while(value2.empty()==false)
        {
            cout<<value2.top();
            value2.pop();
            while(mystack5.size()-1>value.size()+StackVal.size())
            {
            StackVal.push('_');
            }
            StackVal1=StackVal;
        while(StackVal1.empty()==false)
        {
            cout<<StackVal1.top();
            StackVal1.pop();
        }
        cout<<value2.top();
            value2.pop();
        }
    }
    else if(u==5)
    {
        while(value.empty()==false)
        {
            arr[p]=value.top();
            value.pop();
            p++;
        }
        if(b=='*')
         result=arr[p-1] * arr[p-2];
        //else if(b=='/')
         //result=(int)(arr[p-1] / arr[p-2]);
        else if(b=='+')
         result=arr[p-1] + arr[p-2];
       // else if(b=='-')
         //result=arr[p-1] - arr[p-2];
        value.push(result);
        value1=value;
        cout<<"\t";
        while(value1.empty()==false)
        {
            cout<<value1.top();
            value1.pop();
        }
    }
    else if(u==6)
    {
        while(StackVal.empty()==false)
            {
            StackVal.pop();
            }
        value1=value;
        stack<int>value2;
        while(value1.empty()==false)
        {
            value2.push(value1.top());
            value1.pop();
        }
        cout<<"\t";
        while(value2.empty()==false)
        {
            cout<<value2.top();
            value2.pop();
            while(mystack5.size()-1>value.size()+StackVal.size())
            {
            StackVal.push('_');
            }
            StackVal1=StackVal;
        while(StackVal1.empty()==false)
        {
            cout<<StackVal1.top();
            StackVal1.pop();
        }
      }
    }
    else if(u==7)
    {
        while(StackVal.empty()==false)
            {
            StackVal.pop();
            }
        cout<<"\t";
            StackVal.push('_');
            StackVal1=StackVal;
        while(StackVal1.empty()==false)
        {
            cout<<StackVal1.top();
            StackVal1.pop();
        }
    }
}
bool isOperator(char q)
{
    if(q=='+'|| q=='-'||q=='*'|| q=='/')
    return true;
    return false;
}
void print(stack<char>mystack6,int d)
{
    mystack1=mystack6;
    stack<char>printstack;
    cout<<"\n-------------------------------------------------------\n";
                    while(mystack1.top()!='_')
                    {
                     printstack.push(mystack1.top());
                     mystack1.pop();
                    }
                    for(int i=index;inputarr[i]!='\0';i++)
                    {
                    cout<<inputarr[i];
                    }
                    if(inputarr[index]=='\0')
                    cout<<"_";

                    cout<<"\t\t";
                    while(printstack.empty()==false)
                    {
                        cout<<printstack.top();
                        printstack.pop();
                    }
}
