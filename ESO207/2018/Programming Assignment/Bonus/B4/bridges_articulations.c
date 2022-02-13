#include <stdio.h>
int t=0;

typedef struct adjvertex{
    int val;
    struct adjvertex* next;
} node;

typedef struct alist{
    node* h;
    int d;
    int p;
    int ap;
    int l;
    int c;
    node* b;
} list;

typedef struct Graph{
    int v;
    list* vertices;
} ver;


int min(int a, int b){
    if(a<b) return a;
    else return b;
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
        g->vertices[i].b=NULL;
        g->vertices[i].d=0;
        g->vertices[i].c=0;
        g->vertices[i].l=-1;
        g->vertices[i].ap=0;
        g->vertices[i].p=-1;
    }
    return g;
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

void addb(ver* g, int v1, int v2){
    node* newn=newnode(v2);
    node* temp=g->vertices[v1].b;
    if(temp==NULL) g->vertices[v1].b=newn;
    else{
        if(temp->next==NULL){
            if(temp->val>v2){
                newn->next=g->vertices[v1].b;
                g->vertices[v1].b=newn;
            }
            else g->vertices[v1].b->next=newn;
        }
        else{
            node* temp2=temp->next;
            while(temp2 && temp2->val<v2 && temp->val<v2){
                temp=temp->next;
                temp2=temp2->next;
            }
            if(temp->val>v2){
                newn->next=g->vertices[v1].b;
                g->vertices[v1].b=newn;
            }
            else{
                temp->next=newn;
                newn->next=temp2;
            }
        }
    }
    newn=newnode(v1);
    temp=g->vertices[v2].b;
    if(temp==NULL) g->vertices[v2].b=newn;
    else{
        if(temp->next==NULL){
            if(temp->val>v1){
                newn->next=g->vertices[v2].b;
                g->vertices[v2].b=newn;
            }
            else g->vertices[v2].b->next=newn;
        }
        else{
            node* temp2=temp->next;
            while(temp2 && temp2->val<v1 && temp->val<v1){
                temp=temp->next;
                temp2=temp2->next;
            }
            if(temp->val>v1){
                newn->next=g->vertices[v2].b;
                g->vertices[v2].b=newn;
            }
            else{
                temp->next=newn;
                newn->next=temp2;
            }
        }
    }
    return;
}

void APdfs(ver* g, int u){
    g->vertices[u].d=g->vertices[u].l=++t;
    node* temp=g->vertices[u].h;
    while(temp){
        int v=temp->val;
        if(g->vertices[v].d==0){
            g->vertices[u].c++;
            g->vertices[v].p=u;
            APdfs(g,v);
            if(g->vertices[u].l>0 && g->vertices[v].l>0) g->vertices[u].l=min(g->vertices[u].l,g->vertices[v].l);
            if(g->vertices[v].l>g->vertices[u].d) addb(g,u,v);
            if(g->vertices[u].p==-1 && g->vertices[u].c>1) g->vertices[u].ap=1;
            if(g->vertices[u].p!=-1 && g->vertices[v].l>=g->vertices[u].d) g->vertices[u].ap=1;
        }
        else if(v!=g->vertices[u].p) g->vertices[u].l=min(g->vertices[u].l,g->vertices[v].d);
        temp=temp->next;
    }
}

void check(ver* g, int V){
    for(int i=0;i<V;i++)
        if(g->vertices[i].d==0) APdfs(g,i);
    int flag=0;
    for(int i=0;i<V;i++){
        if(g->vertices[i].ap==1){
            printf("%d ",i);
            flag=1;
        }
    }
    if(flag==0) printf("EMPTY");
    printf("\n");
    for(int i=0;i<V;i++){
        node* temp1=g->vertices[i].b;
        while(temp1){
            int j=temp1->val;
            if(j>i) printf("%d %d\n",i,j);
            temp1=temp1->next;
        }
    }
}

int main(){
	int e,V,temp,v1,v2;
    scanf("%d\n%d\n",&V,&e);
	temp=e;
	ver* graph=makeg(V);
	while(temp--){
	    scanf("%d %d\n",&v1,&v2);
	    add(graph,v1,v2);
	}
	check(graph,V);
}
