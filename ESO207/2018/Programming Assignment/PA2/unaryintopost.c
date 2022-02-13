#include <stdio.h>

typedef struct stack{
    int top;//denoting the top of stack i.e. the last element of array
    char op[1000];
}st;

void push(st* ops, char c){//standard push operation
    ops->top = (ops->top) + 1;
    ops->op[(ops->top)] = c;
}

char pop(st* ops){//standard pop
    if(ops->top == -1) return "$";
    else return ops->op[(ops->top)--];
}
//the functions isDigit, isOp, prec are the part of the 'TOKENIZER'
int isDigit(char c){
    if((c>='0')&&(c<='9'))
        return 1;
    else return 0;
}

int isOp(char c){
    if((c=='-')||(c=='*')||(c=='+')||(c=='/')||(c=='^')||(c=='%'))
        return 1;
    else return 0;
}

int prec(char c){
    if((c=='-')||(c=='+')) return 1;
    else if(c=='*') return 2;
    else if((c=='/')||(c=='%')) return 3;
    else if(c=='^') return 4;
    else if(c=='~') return 5;
    else return 0;
}

int count(char* str, int n){
    int c=0,i;
    while(i<n){
        if(!isDigit(str[i])){
            i++;
            continue;
        }
        else{
            while(isDigit(str[i]))
                i++;
            c++;
        }
    }
    return c;
}

int error(char* str){// all the cases which give an error are listed here
    int i, left=0, right=0,sign=0,digit=0,ngtv=0;
    if(isOp(str[0]) || isOp(str[strlen(str) - 1]) || isOp(str[1]) || isOp(str[strlen(str) - 2]))
        return 1;
    for(i=0;i<6;i++){
        if(str[i]==')')
            return 1;
    }
    for(i=strlen(str)-1;i>strlen(str)-7;i--){
        if(str[i]=='(')
            return 1;
    }
    for(i=0;i<strlen(str);i++){
        if((isOp(str[i])) && ((isOp(str[i+2])) || (isOp(str[i+3]))))
            return 1;
        if(((isDigit(str[i])) && (str[i+1] == ' ')) && ((isDigit(str[i+2]))||(isDigit(str[i+3]))))
            return 1;
        if(((isDigit(str[i])) && (isDigit(str[i+1])) && (str[i+2] == ' ')) &&((isDigit(str[i+3])) || (isDigit(str[i+4]))))
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
        digit=count(str,strlen(str));
        if(str[i]=='~')
            ngtv++;
    }
    if(left!=right)//if the no. of opening and closing brackets is not equal
        return 1;
    if(sign>=digit || ngtv>digit || ngtv>(sign+1) || digit!=(sign+1))//if no. of operands greater than digits
        return 1;
    //printf("%d\n",digit);
    return 0;
}

void checkunary( char* str, int n)
{
    for(int i=0;i<n-2;i++)
    {
        if(str[i]=='-')
        {
            if(((i<2) || isOp(str[i-2]) || str[i-2]=='(')&&(isDigit(str[i+2]) || str[i+2]=='('))
                str[i]='~';
        }
    }
}

void intopost()
{
    char post[1000];
    char* str= (char*)malloc(1000*sizeof(char));
    gets(str);
    checkunary(str,strlen(str));
    if(error(str))
    {
        printf("INVALID\n");
        return;
    }
    st* ops=(st*)malloc(sizeof(st));
    ops->top=-1;//initialising
    int i=0,j=0;
    int len=strlen(str);
    while(i<len)
    {
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
        else if(isDigit(str[i]))//I have written the code for numbers<10000. Extra conditions would be needed for nos. greater than 10000.
        {
            post[j++]=str[i++];
            if(isDigit(str[i]))
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
        else if(isOp(str[i]) || (str[i]=='~'))
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
            else if((prec(ops->op[ops->top])>=prec(str[i])))
            {
                while((ops->top >-1)&&((prec(ops->op[ops->top])>=prec(str[i])))){
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
    free(str);
}

int main(){
    int t;
    scanf("%d\n",&t);
    while(t--)
    {
        intopost();
    }
}
