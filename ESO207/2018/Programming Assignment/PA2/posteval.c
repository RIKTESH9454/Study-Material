#include <stdio.h>

typedef struct stack{
    int top;//denoting the top of stack i.e. the last element of array
    float op[1000];
}st;

void push(st* ops, float c){//standard push operation
    ops->top = (ops->top) + 1;
    ops->op[(ops->top)] = c;
}

float pop(st* ops){//standard pop
    return ops->op[(ops->top)--];
}

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

void evaluate(){
    char str[1000];
    gets(str);
    st* stack=(st*)malloc(sizeof(st));
    stack->top=-1;
    int i=0,len=strlen(str);
    float num;
    while(i<len){
        if(str[i]==' '){
            i++;
            continue;
        }
        else if(isDigit(str[i])){
// only 2 digit numbers taken into account, can be modified for more i.e. can make a different function, but only the adequate has been done here.
            if(isDigit(str[i+1])){
                num=(str[i]-48)*10+(str[i+1]-48);
                push(stack,num);
                i=i+2;
                continue;
            }
            else{
                push(stack,(str[i]-48));
                i++;
                continue;
            }
        }
        else{
            num=pop(stack);
            float Num=pop(stack);
            switch(str[i]){
                case '+': push(stack,(num+Num));
                          break;
                case '-': push(stack,(Num-num));
                          break;
                case '*': push(stack,(num*Num));
                          break;
                case '/': push(stack,(Num/num));
                          break;
                case '%': push(stack,(Num-((int)(Num/num))*num));
                          break;
                case '^': push(stack,(pow(Num,num)));
                          break;
                default : push(stack,Num);//for unary operator
                          push(stack,num*(-1));
                          break;
            }
            i++;
        }
    }
    printf("%.0f\n",pop(stack));
}

int main(){
	int t;
	scanf("%d\n",&t);
	while(t--){
	    evaluate();
	}
}
