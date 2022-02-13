#include <stdio.h>
#include <iostream>
//#include <bits/stdc++.h>
#include <algorithm>
#include <stack>
#include <vector>
#include <stdlib.h>

using namespace std;

#define WHITE 1
#define GRAY 2
#define BLACK 3

struct nodes
{
    int dis;
    int fin;
    int status;
    int parent;
};

void printDFSstack(stack<int> S);
void distinctelements(int A[], int x, int y,int *dist);
int minimum(stack<int> S);
//left
class StronglyConnGraph
{
    private :
        vector<int> *Adjacency;
        stack<int> S;
        int numV;
    
    public :
        void initiate(int n)
        {
            cout<< "haha";
            numV=n;
            Adjacency = (vector<int>*)malloc((numV+1)*sizeof(vector<int>));
            cout<<"b";
        }
    
        int newconn(int s, int d)
        {
            vector<int>:: iterator i=Adjacency[s].begin();
            for(;i!=Adjacency[s].end();i++)
            {
                if(d == *i)
                    return 0;
            }
            return 1;
        }
    
        void inputconn(int s, int d)
        {
           // if(newconn(s,d))
            cout<<"abcd"<<endl;
            Adjacency[s].push_back(d);
            cout<<"wxyz"<<endl;
        }
    
        void DFSVisit(int src, nodes N[], int time)
        {
            N[src].status= GRAY;
            time=time+1;
            N[src].dis=time;
        
            vector<int> :: iterator i=Adjacency[src].begin();
            while(i!=Adjacency[src].end())
            {
                if(N[*i].status == WHITE)
                {
                    N[*i].parent=src;
                    DFSVisit(*i,N,time);
                }
            }
            N[src].status= BLACK;
            time=time+1;
            N[src].fin=time;
            S.push(src);
        }
    
        void DFS()
        {
            nodes * N;
            N=(nodes*)malloc(numV*sizeof(nodes));
            for(int i=0;i<numV;i++)
                N[i].status= WHITE;
            int time=0;
            for (int i=0;i<numV;i++)
            {
                if(N[i].status== WHITE)
                    DFSVisit(i,N,time);
            }
        }
    
    
        StronglyConnGraph transpose(StronglyConnGraph* G)
        {
            StronglyConnGraph G_T;
            G_T.initiate(G->numV);
            vector<int>::iterator i;
            for(int j=0;j<G->numV;j++)
            {
                for(i=G->Adjacency[j].begin();i!=G->Adjacency[j].end();i++)
                    G_T.inputconn(*i,j);
            }
            return G_T;
        }
    
        StronglyConnGraph SCC(StronglyConnGraph* G)
        {
            G->DFS();
            StronglyConnGraph Gtrans= G->transpose(G);
            int time=0,min;
            nodes N[G->numV];
            for(int i=0;i<G->numV;i++)
                N[i].status= WHITE;
            int SCCcount=0;
            int pi[G->numV];
            while(! G->S.empty())
            {
                int counter=G->S.top();
                if(N[counter].status==WHITE)
                {
                    Gtrans.DFSVisit(counter, N ,time);
                    min=minimum(Gtrans.S);
                    while(! Gtrans.S.empty())
                    {
                        pi[Gtrans.S.top()]=min;
                        Gtrans.S.pop();
                    }
                    SCCcount++;
                }
                G->S.pop();
            }
            int *aux;
            aux=(int *)malloc(sizeof(int)*SCCcount);
            distinctelements(pi,numV,SCCcount,aux);
            int x,y;
            sort(aux,aux+SCCcount);
            for(x=0;x<SCCcount;x++)
            {
                for(y=0;y<numV;y++)
                {
                    if(pi[y]==aux[x])
                        pi[y]=x;
                }
            }
        
            StronglyConnGraph G_SCC;
            G_SCC.initiate(SCCcount);
            vector<int> :: iterator i;
            for(x=0;x<numV;x++)
            {
                for(i=Adjacency[x].begin();i!=Adjacency[x].end();i++)
                {
                    if((pi[x] != pi[*i]) && (G_SCC.newconn(pi[x], pi[*i])))
                        G_SCC.inputconn(pi[x], pi[*i]);
                }
            }
            return G_SCC;
        }
    
        void printSCC()
        {
            vector<int>:: iterator i;
            cout << numV;
            for(int j=0;j<numV;j++)
            {
                //cout << "yeah" ;
                cout << endl;
            
                sort(Adjacency[j].begin(), Adjacency[j].end());
                for(i=Adjacency[j].begin();i!=Adjacency[j].end();i++)
                    cout << *i << " ";
                cout << "-1";
            }
        }
};

void distinctelements(int A[], int x, int y, int *dist)
{
    int count=0,j;
    for(int i=0;i<x;i++)
    {
        for (j=0;j<i;j++)
        {
            if(A[i]==A[j])
                break;
        }
        if(j==i)
        {
            dist[count]=A[i];
            count++;
        }
    }
}

int minimum(stack<int> S)
{
    stack<int> Scpy=S;
    int min=Scpy.top();
    Scpy.pop();
    
    while(! Scpy.empty())
    {
        int TOP=Scpy.top();
        if(min > TOP)
            min=TOP;
        Scpy.pop();
    }
    return min;
}

int main()
{
    int n;
    cin >> n;
    StronglyConnGraph Gph;
    StronglyConnGraph Gph_scc;
    Gph.initiate(n);
    cout << n << endl;
    for(int i=0;i<=n;i++)
    {
        int j;
        cin >> j;
        cout<<j<<"out"<<endl;
        while(j!=-1)
        {
            Gph.inputconn(i,j);
            cin >> j;
            cout<<j<<"in"<<endl;
        }
        cout<<"aaa"<<endl;
    }
    cout << "yeah";
    Gph_scc=Gph.SCC(&Gph);
    Gph_scc.printSCC();
    return 0;
}

/*void printDFSstack(stack<int> S)
 {
 stack<int> aux=S;
 while(! aux.empty())
 {
 cout << aux.top() << endl;
 aux.pop();
 }
 }
 */
