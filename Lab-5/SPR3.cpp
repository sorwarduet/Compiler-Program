#include<conio.h>
#include<iostream>
#include<string.h>
#include<cstdio>
using namespace std;

struct grammer{
    char pro[20];
    char prod[20];
}gra[10];

int main()
{
    int i,stpos,j,k,l,m,o,p,f,r;
    int np,tspos,cr;

    freopen("in.txt","r",stdin);
    cin>>np;

    char sc,ts[10];
    for(i=0;i<np;i++)
    {
        cin>>ts;
        strncpy(gra[i].pro,ts,1);
        strcpy(gra[i].prod,&ts[3]);
    }

    char input[10];

    cin>>input;

    int lip=strlen(input);

    char stack[10];

    stpos=0;
    i=0;

    //moving input
    sc=input[i];
    stack[stpos]=sc;
    i++;stpos++;

    cout<<"\n\nStack\tInput\tAction";
    do
    {
        r=1;
        while(r!=0)
        {
            cout<<"\n";
            for(p=0;p<stpos;p++)
            {
                cout<<stack[p];
            }
            cout<<"\t";
            for(p=i;p<lip;p++)
            {
                cout<<input[p];
            }

            if(r==2)
            {
                cout<<"\tReduced";
            }
            else
            {
                cout<<"\tShifted";
            }
            r=0;

            //try reducing
            getch();
            for(k=0;k<stpos;k++)
            {
                f=0;

                for(l=0;l<10;l++)
                {
                    ts[l]='\0';
                }

                tspos=0;
                for(l=k;l<stpos;l++) //removing first caharcter
                {
                    ts[tspos]=stack[l];
                    tspos++;
                }

                //now compare each possibility with production
                for(m=0;m<np;m++)
                {
                    cr = strcmp(ts,gra[m].prod);

                    //if cr is zero then match is found
                    if(cr==0)
                    {
                        for(l=k;l<10;l++) //removing matched part from stack
                        {
                            stack[l]='\0';
                            stpos--;
                        }

                        stpos=k;

                        //concatinate the string
                        strcat(stack,gra[m].pro);
                        stpos++;
                        r=2;
                    }
                }
            }
        }

        //moving input
        sc=input[i];
        stack[stpos]=sc;
        i++;stpos++;

    }while(strlen(stack)!=1 && stpos!=lip);

    if(strlen(stack)==1)
    {
        cout<<"\n String Accepted";
    }
    else
    {
        cout<<"\n Error";
    }


}
