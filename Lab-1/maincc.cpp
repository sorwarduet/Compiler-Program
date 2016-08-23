#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
using namespace std;

// Golobal declaration
char operators[]={'<','>','+','-','/','*','%','=','^','!','~','?','&'};
char specialsymbols[]={'(',')','{','}','[',']',',','?',':',';'};
char *double_operators[]={"<=",">=","==","+=","-=","/=","*=","%=","&&",">>","<<","!=","++","--"};
char *keywords[32]={"int","float","double","char","do","for","while","switch","case",
                   "default","return","void","break","const","continue","else","if",
                   "enum","extern","goto","long","register","short","signed","sizeof",
                   "static","typedef","union","unsigned","volatile","struct","auto"};

char *idenfier[15]={"stdio.h","printf","scanf","string.h","conio.h","include","main","stdlib.h","define"};




//Function Phototype
void LexicalAnalyzer();
bool check_operator(char key);
int check_doubleoperator(char *key);
int check_keyword(char *key);
int check_identifier(char *iden);
bool specialsymbol(char ch);


int check_doubleoperator(char *key)
{
    int flag=0;
    for(int i=0;i<14;i++)
    {
        if(strcasecmp(key,double_operators[i])==0)
        {
            flag=1;
            break;
        }
        else
            continue;
    }
    if(flag==1)
        return 1;
    else
        return 0;
}
bool check_operator(char key)
{


    for(int i=0;i<14;i++)
    {
        if(key==operators[i])
            return true;
        else
            continue;
    }

        return false;
}
int check_identifier(char *iden)
{
    int flag=0;
    for(int i=0;i<9;i++)
    {
        if(strcasecmp(iden,idenfier[i])==0)
        {
            flag=1;
            break;
        }
        else
            continue;
    }
    if(flag==1)
        return 1;
    else
        return 0;
}
int check_keyword(char *key)
{
    int flag=0;
    for(int i=0;i<32;i++)
    {
        if(strcasecmp(key,keywords[i])==0)
        {
            flag=1;
            break;
        }
        else
            continue;
    }
    if(flag==1)
        return 1;
    else
        return 0;
}
bool specialsymbol(char ch)
{
    for(int i=0;i<11;i++)
    {
        if(ch==specialsymbols[i])
            return true;
        else
            continue;
    }

        return false;
}


void LexicalAnalyzer()
{
    FILE *f1,*f2;  //File pointer
    char input_ch,temp;
    int string_coun=0,constant_initial=0,doperator_flag=0;
    int index=0;
    int s_comment_flag=0,i=0;
    char make_identifier[35],constant[30],double_operator[5],singlecomment[1000];


    f1=fopen("input.c","r");
    f2=fopen("output.txt","w");
    make_identifier[0]='\0';

    while((input_ch=getc(f1))!=EOF)
    {
        if(input_ch=='"' || string_coun==1)// Check String line
        {
                if(input_ch=='"')
                    string_coun++;
                make_identifier[index++]=input_ch;
                if(string_coun==2)
                {
                    make_identifier[index]='\0';
                    index=0;

                   fprintf(f2,"%s  =String\n",make_identifier);
                    cout<<make_identifier<<" = String .\n"<<endl;

                    string_coun=0;
                }
        }
        else if((isalpha(input_ch) || input_ch=='.' || input_ch=='_' || isalnum(input_ch)) && string_coun==0)
        {
            if(  (isdigit(input_ch)|| input_ch=='.') && index==0)
            {
                constant[constant_initial]=input_ch;
                constant_initial++;
            }
            else if(isalnum(input_ch) || input_ch=='.' || input_ch=='_')
            {
                make_identifier[index]=input_ch;
                index++;
            }
            if(doperator_flag==1)
            {
                if(check_operator(temp) )

                {
                     fprintf(f2,"%c  =Operator\n",temp);

                    cout<<temp<<" = Operator.\n";

                }
                doperator_flag=0;
            }

        }
        else if((isspace(input_ch) || check_operator(input_ch) || specialsymbol(input_ch) || input_ch=='\n')  && string_coun==0)
        {
            if(index>0)
            {
                make_identifier[index]='\0';
                if(check_identifier(make_identifier)) // Check for Identifier
                {

                fprintf(f2,"%s  =Identifier \n",make_identifier);

                    cout<<make_identifier<<" = Identifier\n"<<endl;
                }
                else if(check_keyword(make_identifier)) // Check for Keyword
                {
                    fprintf(f2,"%s  =Keywords \n",make_identifier);

                    cout<<make_identifier<<" = Keyword\n"<<endl;
                }
                else        //Check For variable or User defined function
                {
                     fprintf(f2,"%s  =Identifier \n",make_identifier);

                    cout<<make_identifier<<" = Identifier\n"<<endl;
                }
            }
            if(constant_initial>0)                     //Check constant value
            {
                constant[constant_initial]='\0';
                 fprintf(f2,"%s  =Constant \n",constant);

                cout<<constant<<" =Constant\n"<<endl;
                constant_initial=0;
            }

            if(specialsymbol(input_ch))                     // Check if it is a special Character
            {
                fprintf(f2,"%c  =Special Character \n",constant);

                cout<<input_ch<<" = Special Character\n\n";
            }

            else if (input_ch=='\n')
            {
                if(doperator_flag==1)
                {


                   cout<<temp<<" = Operator.\n"<<endl;
                    doperator_flag=0;
                }
            }
            else if(check_operator(input_ch))  //Check for double and single operator
            {
                if(doperator_flag==0)
                {
                    temp=input_ch;
                    double_operator[doperator_flag]=input_ch;
                    doperator_flag++;
                }
                else if(doperator_flag==1)
                {
                    double_operator[doperator_flag]=input_ch;
                    doperator_flag++;
                    double_operator[doperator_flag]='\0';
                    if(check_doubleoperator(double_operator)) // if Operator is a double symbol
                    {

                        cout<<double_operator<<" = Operators.\n\n";
                        doperator_flag=0;
                    }
                    else if(strcasecmp(double_operator,"//")==0) // Check for comments
                    {
                        while((input_ch=getc(f1))!='\n')
                        {
                            fseek(f1,0,1);
                        }
                        doperator_flag=0;
                    }
                    else                                        // Single Operator
                    {
                        doperator_flag=0;

                        cout<<temp<<" = Operator.\n\n";
                        double_operator[doperator_flag]=input_ch;
                        temp=input_ch;
                        doperator_flag++;
                    }
                }
            }
                index=0;
        }
        else if(input_ch=='#')
        {

                 cout<<input_ch<<" = Special Symbol\n"<<endl;
        }


    }
    fclose(f1);
    fclose(f2);


}




int main()
{
    LexicalAnalyzer();


    return 0;


}
