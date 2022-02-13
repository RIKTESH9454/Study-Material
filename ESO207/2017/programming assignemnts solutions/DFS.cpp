#include <iostream>
#include <vector>
#include <stack>
#include <stdio.h>
#include <algorithm>
#include <set>

using namespace std;

int t = 0,cmpt_no = -1;

struct Vertex
{
    int status = 0;
    int cmpt_no = 0;
    int val;
};

stack<Vertex> N;

vector<pair<int,int>> tags;

//function for finding out the transpose
int transpose(vector<int> Adjacency[],vector<int> Adjacencyback[],int n)
{
    for (int x = 0; x < n; x++) {
        for (int k = 0; k < Adjacency[x].size(); k++) {
            Adjacencyback[Adjacency[x][k]].push_back(x);
        }
    }
    return 0;
}

int dfsexplore(vector<int> Adjacency[],Vertex node[],int curr,int min,int cmpt_no,int y)
{

    if(node[curr].status != 0)
        return node[curr].val;
    node[curr].cmpt_no = cmpt_no;
    t = t + 1;

    node[curr].status = 1;  //denoting in progress
    for (int x = 0; x < Adjacency[node[curr].val].size(); x++)
    {
        if(node[Adjacency[curr][x]].status == 0)  //denoting not visited
        {
            node[Adjacency[curr][x]].cmpt_no = cmpt_no;
            if(Adjacency[curr][x] < min)
                min = Adjacency[curr][x];  //choosing minimum
            min = dfsexplore(Adjacency,node,Adjacency[curr][x],min,cmpt_no,y);
        }
    }
    t = t + 1; //incremnting the t as we move
    if(y == 0)
        N.push(node[curr]); //pushing into the stack since it is finished
    return min;
}

void depthFirstSearch(vector<int> Adjacency[],Vertex node[],int n)
{
    int cmpt_no = 0;
    for (int i = 0; i < n; ++i)
    {
      if(node[i].status == 0)
      {
        dfsexplore(Adjacency,node,node[i].val,0,cmpt_no,0);
      }
    }
}

int dfs2(vector<int> Adjacencyback[],Vertex revnode[],int n)
{
    for (int counter = 0; counter < n; counter++)
    {
        Vertex aux = N.top(); //seeing the topmost element in stack N
        Vertex auxval = revnode[aux.val];
        //poping out the topmost element form the stack N
        N.pop();
        int minimum = aux.val;
        if(auxval.status == 0)
        {
            cmpt_no++;
            minimum = dfsexplore(Adjacencyback,revnode,auxval.val,minimum,cmpt_no,1);
            tags.push_back(make_pair(minimum,cmpt_no));
        }
    }
    return cmpt_no;
}

int main()
{
    int n;
    cin >> n;

    vector<int> Adjacency[n]; //adjacenecy list of the graph

    Vertex node[n];
    Vertex revnode[n];

    for (int i = 0; i < n; i++)
    {
        revnode[i].val = i;
        revnode[i].status = 0;
        node[i].val = i;
        int des;
        cin >> des;
        while(des != -1)
        {
            Adjacency[i].push_back(des);
            cin >> des;
        }
    }
    depthFirstSearch(Adjacency,node,n);

    t = 0;
    cmpt_no = -1;

    //sort(nodes,nodes + size,acompare);
    vector<int> Adjacencyback[n];

    transpose(Adjacency,Adjacencyback,n);

    int num;
    num = dfs2(Adjacencyback,revnode,n);
    int cmpt_nofind[num+1];
    sort(tags.begin(),tags.end());  //sorting through this function

    for (int i = 0; i <= num ; ++i)
        cmpt_nofind[tags[i].second] = i;

        //for printing the necessary output in the required format
    set<int> Adjacencycmpt_no[num+1];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < Adjacency[i].size(); ++j)
        {
            if(revnode[Adjacency[i][j]].cmpt_no != revnode[i].cmpt_no )
                Adjacencycmpt_no[cmpt_nofind[revnode[i].cmpt_no]].insert(cmpt_nofind[revnode[Adjacency[i][j]].cmpt_no]);
        }
    }
    cout << num+1 << endl;
    //now printing the adjacecny list of cmpt_no
    for (int k = 0; k < num+1; k++)
    {
      set<int>:: iterator i;
      i = Adjacencycmpt_no[k].begin();
      while(i != Adjacencycmpt_no[k].end())
      {
        cout << *i << " ";
        ++i;
      }
      cout << "-1" << endl;
    }

    return 0;
}
