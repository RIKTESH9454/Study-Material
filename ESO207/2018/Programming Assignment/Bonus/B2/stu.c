#include <stdio.h>

typedef struct stack{
    long int top;
    long int arr[10000000];
}st;

void push(st* a,long int key){
    a->arr[++(a->top)]=key;
}

long int pop(st* a){
    return a->arr[(a->top)--];
}

long int min(st* a){
    long int min=0;
    long int i;
    for(i=1;i<=a->top;i++){
        if(a->arr[i]<=a->arr[min])
            min=i;
    }
    return min;
}

void makeu(long int m){
    st* s=(st*)malloc(sizeof(st));
    s->top=m-1;
    long int i;
    for(i=m-1;i>=0;i--)
        scanf("%ld",&(s->arr[i]));
    st* t=(st*)malloc(sizeof(st));
    t->top=-1;
    while(s->top>-1){
        if(t->top==-1){
            long int min1=min(s);
            while((s->top)>(min1-1))
                push(t,pop(s));
            printf("v%ld",pop(t));
        }
        if(t->top!=-1){
            long int min1=min(s);
            while((t->arr[t->top]<= (s->arr[min1]))&&(t->top>-1))
                printf("v%ld",pop(t));
            while(s->top!=(min1-1))
                push(t,pop(s));
            printf("v%ld",pop(t));
        }
    }
    while(t->top>-1)
        printf("v%ld",pop(t));
    free(s);
    free(t);
}

int main(){
	long int t,m;
	scanf("%ld\n",&t);
	while(t--){
	    scanf("%ld\n",&m);
	    makeu(m);
	    printf("\n");
	}
}
