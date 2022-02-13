#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct operate
{
    char op[10];
    float o;
    int prec;
    int u;
    int type;   //to distinguish between operator and operand
}opt;

int oprtrm=0;
int opndm=0;

void pushoprtr(opt curr,opt oprtr[])
{
    for(int i=0;i<strlen(curr.op);i++)
        oprtr[oprtrm].op[i]=curr.op[i];
    oprtr[oprtrm].prec=curr.prec;
    oprtr[oprtrm].u=curr.u;
    oprtr[oprtrm].type=curr.type;
    oprtr[oprtrm].o=curr.o;
    oprtrm++;
}
opt topoprtr(opt oprtr[])
{
    return oprtr[oprtrm-1];
}

void pushopnd(opt curr,opt opnd[])
{
    for(int i=0;i<strlen(curr.op);i++)
        opnd[opndm].op[i]=curr.op[i];
    opnd[opndm].prec=curr.prec;
    opnd[opndm].u=curr.u;
    opnd[opndm].type=curr.type;
    opnd[opndm].o=curr.o;
    opndm++;
}

opt topopnd(opt opnd[])
{
    return opnd[opndm-1];
}

int opnd_empty()
{
    if(opndm==0)
        return 1;
    return 0;
}

int oprtr_empty()
{
    if(oprtrm==0)
        return 1;
    return 0;
}

void popoprtr()
{
    oprtrm--;
}

void popopnd()
{
    opndm--;
}

float solve(float x ,float y, char k)
{
    if(k=='/')
        return x/y;
    else if(k=='-')
        return x-y;
    else if(k=='+')
        return x+y;
    else if(k=='*')
        return x*y;
    else if(k=='%')
        return fmod(x,y);
}

float precedence (char num[])
{
    if(num[0]=='/')
        return 3;
    else if(num[0]=='-')
        return 1;
    else if(num[0]=='+')
        return 1;
    else if(num[0]=='*')
        return 2;
    else if(num[0]=='%')
        return 3;
    else if(num[0]=='(')
        return -1;
    else if(num[0]==')')
        return 4;
}

int main()
{
    char num[10];
    opt oprtr;
    opt opnd;
    opt prev;
    int n,flag=0;
    scanf("%d",&n);
    prev.type=1;
    for(int i=0;i<n;i++)
    {
        scanf("%s",num);
        opt curr;
        if(isdigit(num[0]))
        {
            curr.type=0;
            for(int j=0;j<strlen(num);j++)
                curr.op[j]=num[j];
            curr.o=atoi(num);
        }
        else
        {
            for(int j=0;j<strlen(num);j++)
                curr.op[j]=num[j];
            curr.prec=precedence(num);
            curr.type=1;
        }
        if(prev.type == curr.type)
        {
            if(curr.op[0]!='(' && curr.op[0]!='-')
            {
                printf("Malformed expression");
                return 0;
            }
            if(curr.op[0]=='-')
                curr.u=1;
        }
        if(curr.type==1)
        {
            if(curr.op[0]=='(')
                pushopnd(curr,oprtr);
            else if(curr.u==1)
                pushopnd(curr,opnd);
            else if(curr.op[0]!=')')
            {
                opt temp=topopnd(opnd)
                if(!opnd_empty() && curr.prec<=temp.prec)
                {
                    opt temp2=topoprtr(oprtr);
                    float x=temp2.o;
                    popoprtr();
                    temp2=topoprtr(oprtr);
                    float y=temp2.o;
                    popoprtr();
                    char ch[10];
                    opt temp3=topopnd(opnd);
                    for(int j=0;j<strlen(temp3.op);j++)
                        ch[j]=(temp3.op[j];
                    popopnd();
                    opt sol;
                    sol.o=solve(x,y,ch[0]);
                    sol.type=0;
                    pushoprtr(sol,oprtr);
                    pushopnd(curr,opnd);
                }
                opt temp4=topopnd(opnd);
                else if(opnd_empty() || curr.prec>temp4.prec)
                    pushopnd(curr,opnd);
            }
            else if (curr.op[0]=')')
            {
                opt temp5=topopnd(opnd)
                while(!opnd_empty() && temp5.op[0]!='(')
                {
                    opt temp6=topoprtr(oprtr);
                    float x=temp6.o;
                    popoprtr();
                    temp6=topoprtr(oprtr)
                    float y=temp6.o;
                    popoprtr();
                    char ch[10];
                    opt temp7=topopnd(opnd);
                    for(int j=0;j<strlen(temp7.op);j++)
                        ch[j]=temp7.op[j];
                    popopnd();
                    opt sol;
                    sol.o=solve(x,y,ch[0]);
                    sol.type=0;
                    pushoprtr(sol,oprtr);
                }
                if(opnd_empty())
                {
                    printf("Malformed expression");
                    return 0;
                }
                popopnd();
                prev=topoprtr(oprtr);
                opt temp8=topopnd(opnd);
                while(opndm>0 && (temp8.u==1)
                {
                    opt z=topoprtr(oprtr);
                    popoprtr();
                    z.o=z.o*(-1);
                    pushoprtr(z,oprtr);
                    popopnd();
                }
                flag=1;
            }
        }
        else if(curr.type==0)
        {
            opt temp9=topopnd(opnd);
            while(opndm>0 && temp9.u==1)
            {
                curr.o=curr.o * (-1);
                popopnd();
            }
            pushoprtr(curr,oprtr);
        }
        if(flag!=1)
            prev=curr;
        flag=0;
    }
    if(prev.type!=0 && !(prev.op[0]==')'))
    {
        printf("Malformed expression");
        return 0;
    }
    while(opndm>0)
    {
        opt temp10=topopnd(opnd);
        if(temp10.op[0]='(')
        {
            printf("Malformed expression");
            return 0;
        }
        opt temp11=topoprtr(oprtr);
        float x=temp11.o;
        popoprtr();
        temp11=topoprtr(oprtr);
        float y=temp11.o;
        popoprtr();
        char ch[10];
        opt temp12=topopnd(opnd);
        for(int j=0;j<strlen(temp12.op);j++)
            ch[j]=(topopnd(opnd)).op[j];
        popopnd();
        opt sol;
        sol.o=solve(x,y,ch[0]);
        sol.type=0;
        pushoprtr(sol,oprtr);
    }
    opt temp13=topoprtr(oprtr);
    printf("%f",temp13.o);
    return 0;
}
