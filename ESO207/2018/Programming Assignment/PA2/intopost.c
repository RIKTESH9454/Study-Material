#include <stdio.h>

typedef struct stack
{
    int top;//denoting the top of stack i.e. the last element of array
    char op[1000];
}st;

void push(st* ops, char c)//standard push operation
{
    ops->top = (ops->top) + 1;
    ops->op[(ops->top)] = c;
}

char pop(st* ops)//standard pop
{
    if(ops->top == -1) return "$";
    else return ops->op[(ops->top)--];
}
//the functions isDigit, isOp, prec are the part of the 'TOKENIZER'
int isDigit(char c)
{
    if((c>='0')&&(c<='9'))
        return 1;
    else return 0;
}

int isOp(char c)
{
    if((c=='-')||(c=='*')||(c=='+')||(c=='/')||(c=='^')||(c=='%'))
        return 1;
    else return 0;
}

int prec(char c)
{
    if((c=='-')||(c=='+')) return 1;
    else if(c=='*') return 2;
    else if((c=='/')||(c=='%')) return 3;
    else if(c=='^') return 4;
    else return 0;
}

int error(char* str)// all the cases which give an error are listed here
{
    int left=0, right=0,sign=0,digit=0;
    for(int i=0;i<strlen(str);i++)
    {
        if((isOp(str[i])) && ((isOp(str[i+2])) || (isOp(str[i+3]))))
            return 1;
        if(((isDigit(str[i])) && (str[i+1] == ' ')) && ((isDigit(str[i+2]))||(isDigit(str[i+3]))))
            return 1;
        if((isDigit(str[i]) && (str[i+2] == '(')) || (isDigit(str[i+2]) && (str[i] == ')')))
            return 1;
        if((str[i]=='(' && str[i+2]==')') || ( str[i]==')' && str[i+2]=='('))
            return 1;
        if((isOp(str[i]) && (str[i+2]==')')) || (isOp(str[i+2]) && (str[i]=='(')))
            return 1;
        if(str[i]=='(')
            left++;
        if(str[i]==')')
            right++;
        if(isOp(str[i]))
            sign++;
        if(isDigit(str[i]))
            digit++;
    }
    if(left!=right)//if the no. of opening and closing brackets is not equal
        return 1;
    if(sign>=digit)//if no. of operands greater than digits
        return 1;
    return 0;
}

void intopost()
{
    char str[1000],post[1000];
    gets(str);
    if(error(str))
    {
        printf("INVALID\n");
        return;
    }
    st* ops=(st*)malloc(sizeof(st));
    ops->top=-1;//initialising
    int i=0,j=0;
    int len=strlen(str);
    //printf("%d",len);
    while(i<len)
    {
        //printf("%d",i);
        if(str[i]==' ')
        {
            i++;
            continue;
        }
        else if(str[i]=='(')
        {
            push(ops,str[i]);
            i++;
            continue;
        }
        else if(isDigit(str[i]))//I have written the code for numbers<1000. Extra conditions would be needed for nos. greater than 1000.
        {
            post[j++]=str[i++];
            if(isDigit(str[i]))
            {
                post[j++]=str[i++];
                if(isDigit(str[i]))
                {
                    post[j++]=str[i++];
                    post[j++]=' ';
                }
                else post[j++]=' ';
            }
            else post[j++]=' ';
            continue;
        }
        else if(str[i]==')')
        {
            while(((ops->top)>-1)&&(ops->op[ops->top] != '('))
            {
                post[j++]=pop(ops);
                post[j++]=' ';
            }
            if(ops->op[ops->top] != '(')
            {
                printf("INVALID\n");
                return;
            }
            pop(ops);
            i++;
            continue;
        }
        else if(isOp(str[i]))
        {
            if((ops->top==-1)||(ops->op[ops->top] == '(') || (prec(ops->op[ops->top])<prec(str[i])))
                push(ops,str[i++]);

            else if(prec(ops->op[ops->top])==prec(str[i]))
            {
                if(str[i]=='^')//if operator has right associativity
                    push(ops,str[i++]);
                else{//if left associative
                    post[j++]=pop(ops);
                    post[j++]=' ';
                    push(ops,str[i++]);
                }
            }
            else if(prec(ops->op[ops->top])>prec(str[i]))
            {
                while((ops->top >-1)&&(prec(ops->op[ops->top])>prec(str[i]))){
                    post[j++]=pop(ops);
                    post[j++]=' ';
                }
                push(ops,str[i++]);
            }
            continue;
        }
        else{// if the character is any other thing than the ones mentioned in problem
            printf("INVALID\n");
            return;
        }
    }
    while(ops->top > -1)//empty stack
    {
        post[j++]=pop(ops);
        post[j++]=' ';
    }
    post[j]='\0';//closing array
    for(i=0;i<strlen(post);i++)
    {
        if(post[i]=='$')//reference from the 'pop' function
        {
            printf("INVALID");
            return;
        }
    }
    printf("%s\n",post);// printing postfix
}

int main(){
    int t;
    scanf("%d\n",&t);
    while(t--)
    {
        intopost();
    }
}
