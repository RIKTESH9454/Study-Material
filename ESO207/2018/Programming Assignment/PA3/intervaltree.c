#include <stdio.h>
/*
    F
    I
    N
    A
    L
    S
    O
    L
    U
    T
    I
    O
    N
*/
typedef struct node{
    double lo;
    double hi;
    struct node* left;
    struct node* right;
    struct node* p;
}tnode;

tnode* makenode(double l, double h){
    tnode* newnode=(tnode*)malloc(sizeof(tnode));
    newnode->lo=l;
    newnode->hi=h;
    newnode->left=newnode->right=newnode->p=NULL;
    return newnode;
}

tnode* treemin(tnode* root){
    tnode* x=root;
    if(x==NULL) return x;
    while(x->left != NULL)
        x=x->left;
    return x;
}

tnode* trans(tnode* root, tnode* u, tnode* v){
    if(u->p==NULL) root=v;
    else if(u==(u->p->left)) u->p->left=v;
    else u->p->right=v;
    if(v!=NULL) v->p=u->p;
    return root;
}

double maxv(tnode* z, tnode* root){
    tnode* x= root;
    double h=z->hi;
    double l=z->lo;
    while(x != NULL && h!=(x->hi) && l!=(x->lo)){
        if(h<x->hi) x=x->left;
        else x=x->right;
    }
    while(x->right!=NULL) x=x->right;
    return x->hi;
}

void min(tnode* root){
    tnode* x= root;
    if(x==NULL) return;
    while(x->left!=NULL) x=x->left;
    if(x!=NULL) printf("[%.0lf %.0lf]\n",x->lo, x->hi);
    return;
}

void max(tnode* root){
    tnode* x= root;
    if(x==NULL) return;
    while(x->right!=NULL) x=x->right;
    if(x!=NULL) printf("[%.0lf %.0lf]\n",x->lo, x->hi);
    return;
}

tnode* insert1(tnode* root, double l, double h){
    tnode* x=root;
    tnode*z=makenode(l,h);
    if(root==NULL) return z;
    else{
        tnode* y;
        while(x!=NULL){
            y=x;
            if(l<x->lo) x=x->left;
            else x=x->right;
        }
        z->p=y;
        if(l<y->lo) y->left=z;
        else y->right=z;
    }
    return z;
}

tnode* insert2(tnode* root, double l, double h){
    tnode* x=root;
    tnode*z=makenode(l,h);
    if(root==NULL) return z;
    else{
        tnode* y;
        while(x!=NULL){
            y=x;
            if(h<x->hi) x=x->left;
            else x=x->right;
        }
        z->p=y;
        if(h<y->hi) y->left=z;
        else y->right=z;
    }
    return z;
}

tnode* del1(tnode* root, double l, double h){
    tnode* x=root;
    while(x != NULL && (h!=(x->hi) && l!=(x->lo))){
        if(l<x->lo) x=x->left;
        else x=x->right;
    }
    if(x==NULL) return root;
    if(x->left==NULL) root=trans(root,x,x->right);
    else if(x->right==NULL) root=trans(root,x,x->left);
    else{
        tnode* y=treemin(x->right);
        if(y->p!=x){
            root=trans(root,y,y->right);
            y->right=x->right;
            y->right->p=y;
        }
        root=trans(root,x,y);
        y->left=x->left;
        y->left->p=y;
    }
    return root;
}

tnode* del2(tnode* root, double l, double h){
    tnode* x=root;
    while(x != NULL && (h!=(x->hi) && l!=(x->lo))){
        if(h<x->hi) x=x->left;
        else x=x->right;
    }
    if(x==NULL) return root;
    if(x->left==NULL) root=trans(root,x,x->right);
    else if(x->right==NULL) root=trans(root,x,x->left);
    else{
        tnode* y=treemin(x->right);
        if(y->p!=x){
            root=trans(root,y,y->right);
            y->right=x->right;
            y->right->p=y;
        }
        root=trans(root,x,y);
        y->left=x->left;
        y->left->p=y;
    }
    return root;
}

void isover(tnode* root1,tnode* root2, double l, double h){
    tnode* x=root1;
    while(x!=NULL && !(l<=(x->hi) && (x->lo)<=h)){
        if(x->left!=NULL && maxv(x->left,root2)>=l) x=x->left;
        else x=x->right;
    }
    if(x==NULL) printf("0\n");
    else printf("1\n");
    return;
}

void losucc(tnode* root, double l, double h){
    tnode* x= root;
    while(x!=NULL && l!=(x->lo)){
        if(l<x->lo) x=x->left;
        else x=x->right;
    }
    if(x==NULL){
        printf("INVALID\n");
        return;
    }
    if(x->right!=NULL) min(x->right);
    else{
        tnode* y=x->p;
        while(y!=NULL && x==(y->right)){
            x=y;
            y=y->p;
        }
        if(y!=NULL) printf("[%.0lf %.0lf]\n",y->lo,y->hi);
        else printf("INVALID\n");
    }
    return;
}

void hisucc(tnode* root, double l, double h){
    tnode* x= root;
    while(x!=NULL && h!=(x->hi)){
        if(h<x->hi) x=x->left;
        else x=x->right;
    }
    if(x==NULL){
        printf("INVALID\n");
        return;
    }
    if(x->right!=NULL) min(x->right);
    else{
        tnode* y=x->p;
        while(y!=NULL && x==(y->right)){
            x=y;
            y=y->p;
        }
        if(y!=NULL) printf("[%.0lf %.0lf]\n",y->lo,y->hi);
        else printf("INVALID\n");
    }
    return;
}

double main(){
	int t;
	scanf("%d\n",&t);
	while(t--){
	    int m;
	    double l,h;
	    char str[10];
	    scanf("%d\n",&m);
	    char c=getchar();
	    while(c!='+') c=getchar();
	    scanf(" %lf %lf\n",&l,&h);
	    //printf("%lf %lf",l,h);
	    tnode* root1=makenode(l,h);
	    tnode* root2=makenode(l,h);
	    m--;
	    while(m--){
	        c=getchar();
	        if(c=='+'){
	            scanf(" %lf %lf\n",&l,&h);
	            insert1(root1,l,h);
	            insert2(root2,l,h);
	        }
	        else if(c=='-'){
	            scanf(" %lf %lf\n",&l,&h);
	            root1=del1(root1,l,h);
	            root2=del2(root2,l,h);
	        }
	        else if(c=='m'){
	            c=getchar();
	            if(c=='a') max(root2);
	            else min(root1);
	            gets(str);
	        }
	        else if(c=='l'){
	            scanf("succ %lf %lf\n",&l,&h);
	            losucc(root1,l,h);
	        }
	        else if(c=='h'){
	            scanf("succ %lf %lf\n",&l,&h);
	            hisucc(root2,l,h);
	        }
	        else if(c=='o'){
	            scanf("verlap %lf %lf\n",&l,&h);
	            isover(root1,root2,l,h);
	        }
	    }
	}
}
