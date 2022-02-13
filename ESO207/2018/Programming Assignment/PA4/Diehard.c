#include <stdio.h>

typedef struct pqueue{
    int nos[100000][3];
    int f;
    int l;
} queue;

queue* makeq(){
    queue* q= (queue*)malloc(sizeof(queue));
    q->f=-1;
    q->l=-1;
    return q;
}

void nq(queue* q, int a, int b, int c){
    if(q->l>=(100000 - 1)) printf("ERROR");
    else{
        if(q->f==-1) q->f=0;
        q->l++;
        q->nos[q->l][0]=a;
        q->nos[q->l][1]=b;
        q->nos[q->l][2]=c;
    }
    return;
}

int* dq(queue* q){
    int* list=(int*)malloc(3*sizeof(int));
    if(q->l==-1 || q->f==-1) return list;
    list[0]=q->nos[q->f][0];
    list[1]=q->nos[q->f][1];
    list[2]=q->nos[q->f][2];
    q->f++;
    if(q->f > q->l) q->f=q->l=-1; //reset
    return list;
}

void check(int l1, int l2, int l3, int s1, int s2, int s3, int a1, int a2, int a3){
    if(s1==a1 && s2==a2 && s3==a3){
        printf("0\n");
        return;
    }
    if(((a1+a2+a3)>(s1+s2+s3))||((a1+a2+a3)>(l1+l2+l3))||(a1>l1)||(a2>l2)||(a3>l3)){
        printf("IMPOSSIBLE\n");
        return;
    }
    int i,arr[l1+1][l2+1][l3+1],a,b,c;
    memset(arr,0,sizeof(arr));
    queue* q=makeq();
    nq(q,s1,s2,s3);
    arr[s1][s2][s3]=1;
    while(q->l!=-1){
        int *curr=dq(q);
        a=curr[0];
        b=curr[1];
        c=curr[2];
        if(a==a1 && b==a2 && c==a3) break;

        if((a<=l2-b)&&(arr[0][a+b][c]==0)){
            nq(q,0,b+a,c);
            arr[0][a+b][c]=arr[a][b][c] + 1;
        }
        else if((a>l2-b)&&(arr[a+b-l2][l2][c]==0)){
            nq(q,a+b-l2,l2,c);
            arr[a-l2+b][l2][c]=arr[a][b][c] + 1;
        }

        if((a<=l3-c)&&(arr[0][b][a+c]==0)){
            nq(q,0,b,a+c);
            arr[0][b][a+c]=arr[a][b][c] + 1;
        }
        else if((a>l3-c)&&(arr[a-l3+c][b][l3]==0)){
            nq(q,a-l3+c,b,l3);
            arr[a-l3+c][b][l3]=arr[a][b][c] + 1;
        }

        if((b<=l1-a)&&(arr[a+b][0][c]==0)){
            nq(q,b+a,0,c);
            arr[a+b][0][c]=arr[a][b][c] + 1;
        }
        else if((b>l1-a)&&(arr[l1][b-l1+a][c]==0)){
            nq(q,l1,b+a-l1,c);
            arr[l1][b-l1+a][c]=arr[a][b][c] + 1;
        }

        if((b<=l3-c)&&(arr[a][0][b+c]==0)){
            nq(q,a,0,b+c);
            arr[a][0][b+c]=arr[a][b][c] + 1;
        }
        else if((b>l3-c)&&(arr[a][b+c-l3][l3]==0)){
            nq(q,a,b-l3+c,l3);
            arr[a][b+c-l3][l3]=arr[a][b][c] + 1;
        }

        if((c<=l1-a)&&(arr[a+c][b][0]==0)){
            nq(q,c+a,b,0);
            arr[a+c][b][0]=arr[a][b][c] + 1;
        }
        else if((c>l1-a)&&(arr[l1][b][c+a-l1]==0)){
            nq(q,l1,b,a+c-l1);
            arr[l1][b][c+a-l1]=arr[a][b][c] + 1;
        }

        if((c<=l2-b)&&(arr[a][b+c][0]==0)){
            nq(q,a,c+b,0);
            arr[a][b+c][0]=arr[a][b][c] + 1;
        }
        else if((c>l2-b)&&(arr[a][l2][c+b-l2]==0)){
            nq(q,a,l2,c+b-l2);
            arr[a][l2][c+b-l2]=arr[a][b][c] + 1;
        }

        if((a>0) && (arr[0][b][c]==0) && (b+c >= a1+a2+a3)){
            nq(q,0,b,c);
            arr[0][b][c]=arr[a][b][c] + 1;
        }
        if((b>0) && (arr[a][0][c]==0) && (a+c >= a1+a2+a3)){
            nq(q,a,0,c);
            arr[a][0][c]=arr[a][b][c] + 1;
        }

        if((c>0) && (arr[a][b][0]==0) && (b+a >= a1+a2+a3)){
            nq(q,a,b,0);
            arr[a][b][0]=arr[a][b][c] + 1;
        }
    }
    if(a==a1 && b==a2 && c==a3) printf("%d\n",arr[a][b][c]);
    else printf("IMPOSSIBLE\n");
}

int main(){
	int t,l1,l2,l3,s1,s2,s3,a1,a2,a3,n;
	scanf("%d", &t);
	while(t--){
	    scanf("%d %d %d\n%d %d %d\n%d\n",&l1,&l2,&l3,&s1,&s2,&s3,&n);
	    while(n--){
	        scanf("%d %d %d\n",&a1,&a2,&a3);
	        check(l1,l2,l3,s1,s2,s3,a1,a2,a3);
	    }
	}
}
