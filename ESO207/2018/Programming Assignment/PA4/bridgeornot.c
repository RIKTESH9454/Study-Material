#include <stdio.h>

typedef struct adjvertex{
    int val;
    struct adjvertex* next;
} node;

typedef struct alist{
    node* h;
    int d;
} list;

typedef struct Graph{
    int v;
    list* vertices;
} ver;

typedef struct queue{
    int *nos;
    int f;
    int l;
    int sz;
} vlist;

vlist* makeq(int v){
    vlist* q= (vlist*)malloc(sizeof(vlist));
    q->nos=(int*)malloc(v*sizeof(int));
    q->f=-1;
    q->l=-1;
    q->sz=v;
    return q;
}

void enq(vlist* q, int v){
    if(q->l>=(q->sz - 1)) printf("ERROR");
    else{
        if(q->f==-1) q->f=0;
        q->l++;
        q->nos[q->l]=v;
    }
    return;
}

int dq(vlist* q){
    if(q->l==-1 || q->f==-1) return 0;
    int v=q->nos[q->f];
    q->f++;
    if(q->f > q->l) q->f=q->l=-1; //reset
    return v;
}

node* newnode(int V){
    node* n=(node*)malloc(sizeof(node));
    n->val=V;
    n->next=NULL;
    return n;
}

ver* makeg(int V){
    ver* g=(ver*)malloc(sizeof(ver));
    g->v=V;
    g->vertices=(list*)malloc(V*sizeof(list));
    for(int i=0;i<V;i++){
        g->vertices[i].h=NULL;
        g->vertices[i].d=0;
    }
    return g;
}

void del(ver* g, int v1, int v2){
    node* temp=g->vertices[v1].h;
    if(temp->val==v2){
        g->vertices[v1].h=temp->next;
        temp->next=NULL;
    }
    else{
        while((temp->next->val) != v2) temp=temp->next;
        if(temp->next){
            node* temp1=temp->next;
            temp->next=temp1->next;
            temp1->next=NULL;
            free(temp1);
        }
    }
    temp=g->vertices[v2].h;
    if(temp->val==v1){
        g->vertices[v2].h=temp->next;
        temp->next=NULL;
    }
    else{
        while((temp->next->val) != v1) temp=temp->next;
        if(temp->next){
            node* temp1=temp->next;
            temp->next=temp1->next;
            temp1->next=NULL;
            free(temp1);
        }
    }
}

void add(ver* g, int v1, int v2){
    node* newn=newnode(v2);
    newn->next=g->vertices[v1].h;
    g->vertices[v1].h=newn;
    node* newn1=newnode(v1);
    newn1->next=g->vertices[v2].h;
    g->vertices[v2].h=newn1;
    return;
}

int checkb(ver* g, int v, int v1, int v2){
    del(g,v1,v2);
    vlist* q=makeq(v);
    g->vertices[v1].d=1;
    enq(q,v1);
    while(q->l!=-1){
        int curr=dq(q);
        node* temp=g->vertices[curr].h;
        while(temp){
            int adj=temp->val;
            if(adj==v2) return 1;
            if(g->vertices[adj].d!=1){
                g->vertices[adj].d=1;
                enq(q,adj);
            }
            temp=temp->next;
        }
    }
    return 0;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
	    int e,V,temp,v1,v2;
	    scanf("%d\n%d\n",&V,&e);
	    temp=e;
	    ver* graph=makeg(V);
	    while(temp--){
	        scanf("%d %d\n",&v1,&v2);
	        add(graph,v1,v2);
	    }
	    scanf("%d %d\n",&v1,&v2);
	    if(checkb(graph,V,v1,v2)) printf("Not Bridge\n");
	    else printf("Bridge\n");
	}
}
