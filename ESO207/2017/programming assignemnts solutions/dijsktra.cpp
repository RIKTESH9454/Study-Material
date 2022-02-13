#include <stdio.h>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct graph_nodes
{
    long long int ver;
    long long int wt;
};

struct dijkstra_nodes
{
    long long int val;
    long long int d;
};

long long int sz = 1;

void interchange(long long int *n1, long long int *n2);
void interchange(dijkstra_nodes *node1, dijkstra_nodes *node2);
long long int min_heapify(long long int ind, dijkstra_nodes Q[], long long int position[]);
dijkstra_nodes show_min(long long int position[], dijkstra_nodes Q[]);
void Add_heap(long long int position[], long long int val, long long int d, dijkstra_nodes Q[]);
long long int Dec(long long int val, dijkstra_nodes Q[], long long int ind, long long int position[]);
long long int relaxation(long long int position[], dijkstra_nodes Q[], graph_nodes *n2_, dijkstra_nodes *n1_);
void Dijkstra_algo(dijkstra_nodes Q[], vector<graph_nodes> *Adjacency, long long int position[]);

int main()
{
    long long int N,source,D_,C1_,C2_,D1_,D2_,W1_,W2_,W3_;
    // storing all variables in the prescribed format
    cin >> N;
    
    vector <graph_nodes> Adjacency[N+1];
    dijkstra_nodes Q[N+1];
    
    cin >> source;
    
    cin >> D_;
    cin >> C1_;
    cin >> C2_;
    cin >> D1_;
    cin >> D2_;
    cin >> W1_;
    cin >> W2_;
    cin >> W3_;
    
    long long int position[N+1];
    
    for(long long int i = 1;i <= N;i++)
    {
        graph_nodes temp;
        long long int k;
        if(i == source)
            k = 0;
        else
            k = numeric_limits<long long int> :: max();
        position[i] = i;
        Add_heap(position, i, k, Q);
        
        long long int degree = (i * C2_ + i * i * D2_) % D_;
        
        for(long long int j=1;j<=degree;j++)
        {
            temp.ver = (i * C1_ + j * D1_) % N;
            temp.wt = (i * W1_ + j * W2_) % W3_;//wt of edge ( i, temp_node.vertex)
            temp.ver += 1;
            Adjacency[i].push_back(temp);
        }
    }
    
    sz--;
    
    Dijkstra_algo(Q, Adjacency, position);
    
    for (long long int x = 1; x <= N; x++)
    {
        if(Q[position[x]].d == numeric_limits<long long int> :: max())
            cout << Q[position[x]].val << " "<< -1 << endl;
        else
            cout << Q[position[x]].val << " " << Q[position[x]].d << endl;
    }
    return 0;
}


void interchange(long long int *n1, long long int *n2)
{
    long long int temp;
    temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

//overloading of functions :: interchange function
void interchange(dijkstra_nodes *node1, dijkstra_nodes *node2)
{
    dijkstra_nodes auxnode;
    
    auxnode = *node1;
    *node1 = *node2;
    *node2 = auxnode;
}


long long int min_heapify(long long int ind, dijkstra_nodes Q[], long long int position[])
{
    long long int rt_ = 2*ind + 1;  //characterisation for right branches
    long long int lt_ = 2*ind;  //left branches
    
    long long int min;
    
    if(Q[rt_].d < Q[ind].d && rt_ <= sz)
        min = rt_;
    else
        min = ind;
    
    if(Q[lt_].d < Q[min].d && lt_ <= sz)
        min = lt_;
    
    if(min != ind)
    {
        interchange(&Q[ind], &Q[min]);
        interchange(&position[Q[ind].val], &position[Q[min].val]);
        min_heapify(min, Q, position);
    }
}


dijkstra_nodes show_min(long long int position[], dijkstra_nodes Q[])
{
    dijkstra_nodes tiny = Q[1];
    
    interchange(&Q[1], &Q[sz]);
    interchange(&position[Q[1].val], &position[Q[sz].val]);
    sz --;
    
    min_heapify(1, Q, position);
    return tiny;
}


void Add_heap(long long int position[], long long int val, long long int d, dijkstra_nodes Q[])
{
    long long int x = sz;
    
    sz++;
    
    Q[x].d = d;
    Q[x].val = val;

    while(Q[x/2].d > Q[x].d && x > 1)
    {
        interchange(&position[Q[x/2].val], &position[Q[x].val]);
        //cout<<"yo"<<position[Q[x/2].val]<<"  "<<position[Q[x].val]<<endl;
        interchange(&Q[x/2], &Q[x]);
        //cout<<"go"<<position[Q[x/2].val]<<"  "<<position[Q[x].val]<<endl;
        x = x/2;
    }
}


long long int Dec(long long int val, dijkstra_nodes Q[], long long int ind, long long int position[])
{
    if(val > Q[position[ind]].d)
        return 0;
    
    Q[position[ind]].d = val;
    
    long long int k = position[ind];
    
    while(Q[k/2].d > Q[k].d && k > 1)
    {
        interchange(&position[Q[k/2].val], &position[ind]);
        interchange(&Q[k/2], &Q[k]);
        
        k = k/2;
    }
}


long long int relaxation(long long int position[], dijkstra_nodes Q[], graph_nodes *n2_, dijkstra_nodes *n1_)
{
    long long int ind;
    ind = n2_->ver;
    
    if(Q[position[ind]].d > n2_->wt + n1_->d)
    {
        if(n2_->wt + n1_->d < 0)
            return 0;
        Dec(n2_->wt + n1_->d, Q, Q[position[ind]].val, position);
    }
}


void Dijkstra_algo(dijkstra_nodes Q[], vector<graph_nodes> *Adjacency, long long int position[])
{
    while(sz != 0)
    {
        dijkstra_nodes aux = show_min(position,Q);
        if(aux.d == numeric_limits<long long int> :: max())
            break;
        for (long long int x = 0; x < Adjacency[aux.val].size(); x++)
            relaxation(position, Q, &Adjacency[aux.val][x], &aux);
    }
}



