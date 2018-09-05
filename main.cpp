#include <utility>
#include <bits/stdc++.h>

using namespace std;

void addUndirEdge(vector<int> adjList[],int src,int dest){
    adjList[src].push_back(dest);
    adjList[dest].push_back(src);
    return;
}

void addDirEdge(vector<int> adjList[],int src,int dest){
    adjList[src].push_back(dest);
    return;
}

void addEdgewithWt(vector<pair<int,int> > adjList[],int src,int dest,int wt){
    adjList[src].push_back(make_pair(dest,wt));
    adjList[dest].push_back(make_pair(src,wt));
    return;
}

void display(vector<int> adjList[],int V){
    int i;
    for(i=0;i<V;i++){
        vector<int>::iterator iter;

        printf("%d->",i);
        for(iter = adjList[i].begin();iter != adjList[i].end();iter++){
            printf("%d,",*iter);
        }
    printf("\n");
    }
}

void displayWithWt(vector<pair<int,int> > adjList[],int V){
    int i;
    for(i=0;i<V;i++){
        vector<pair<int,int> >::iterator iter;

        printf("%d->",i);
        for(iter = adjList[i].begin();iter != adjList[i].end();iter++){
            printf("(%d,%d),",iter->first,iter->second);
        }
    printf("\n");
    }
}

void BFS(vector<int> adjList[],int s,int V){
    bool* visited = new bool[V];
    for(int i = 0;i < V;i++){
        visited[i] = false;
    }

    list<int> queue;
    queue.push_back(s);
    visited[s] = true;

    vector<int>::iterator iter;

    while(!queue.empty()){
        int val = queue.front();
        queue.pop_front();

        for(iter = adjList[val].begin();iter != adjList[val].end();iter++){
            if(visited[*iter] == false){
                queue.push_back(*iter);
                visited[*iter] = true;
            }
        }
    }

    for(int i=0;i<V;i++){
        printf("\n%d",visited[i]);
    }
    return;
}

void dfs_visit(vector<int> adj[],int u,bool* visited){
    visited[u] = true;
    printf("%d ",u);
    vector<int>::iterator iter;

    for(iter = adj[u].begin();iter != adj[u].end();iter++){
        if(visited[*iter] == false){
            dfs_visit(adj,*iter,visited);
        }
    }
}

void DFS(vector<int> adjList[],int s,int V){
    bool* visited  = new bool[V];
    for(int i=0;i < V;i++){
        visited[i] = false;
    }
    visited[s] = false;

    dfs_visit(adjList,s,visited);

    for(int i=0;i<V;i++){
        printf("\n%d",visited[i]);
    }
    return;
}

bool is_cyclic_Util(vector<int> adjList[],int s,bool* visited,bool* recstack){

    if(visited[s] == false){
        visited[s] = true;
        recstack[s] = true;

        vector<int>::iterator iter;
        for(iter = adjList[s].begin();iter != adjList[s].end();iter++){

            if(visited[*iter] == false){
                bool temp = is_cyclic_Util(adjList,*iter,visited,recstack);
                printf("%d ",temp);
                if(temp == true){
                    return true;
                }
            }
            else if(recstack[*iter] == true){
                return true;
            }
        }
    }

    recstack[s] = false;
    return false;
}

bool is_cyclic(vector<int> adjList[],int V){
    bool* visited = new bool[V];
    bool* recstack = new bool[V];
    for(int i=0;i<V;i++){
        visited[i] = false;
        recstack[i] = false;
    }

    bool res;

    for(int i=0;i<V;i++){
        if(is_cyclic_Util(adjList,i,visited,recstack)){
            return true;
        }
    }
    return false;
}

void topo_visit(vector<int> adjList[],int s,bool visited[],stack<int> &Stack){
    visited[s] = true;

    vector<int>::iterator iter;
    for(iter = adjList[s].begin();iter != adjList[s].end();iter++){
        if(visited[*iter] == false){
            topo_visit(adjList,*iter,visited,Stack);
        }
    }
    Stack.push(s);
}

void topologicalSorting(vector<int> adjList[],int V){
    bool* visited = new bool[V];
    for(int i=0;i<V;i++){
        visited[i] = false;
    }
    stack<int> Stack;

    for(int i=0;i<V;i++){
        if(visited[i] == false)
        topo_visit(adjList,i,visited,Stack);
    }
    while(!Stack.empty()){
        printf("%d ",Stack.top());
        Stack.pop();
    }
}

void transpose_graph(vector<int> adjList[],vector<int> t_adjList[],int V){
    vector<int>::iterator iter;

    for(int i=0;i<V;i++){
        for(iter = adjList[i].begin();iter != adjList[i].end();iter++){
            t_adjList[*iter].push_back(i);
        }
    }

}

void SCC(vector<int> adjList[],int s,bool* visited,stack<int> &Stack){
    visited[s] = true;

    vector<int>::iterator iter;
    for(iter = adjList[s].begin();iter != adjList[s].end();iter++){
        if(visited[*iter] == false){
            SCC(adjList,*iter,visited,Stack);
        }
    }
    Stack.push(s);
}

void kosaraju_SCC(vector<int> adjList[],int V){
    bool* visited = new bool[V];
    for(int i=0;i<V;i++){
        visited[i] = false;
    }

    stack<int> Stack;
    for(int i=0;i<V;i++){
        if(visited[i] == false){
            SCC(adjList,i,visited,Stack);
        }
    }
    for(int i=0;i<V;i++){
        visited[i] = false;
    }

    vector<int> trans_adjList[V];

    transpose_graph(adjList,trans_adjList,V);

    while(!Stack.empty()){
        if(visited[Stack.top()] == false){
            dfs_visit(trans_adjList,Stack.top(),visited);
            printf("\n");
        }
        Stack.pop();
    }

}

void removeVertex(vector<int> adjList[],int V,int v){
    // V is no of vertices
    // v is the vertex to be removed
    vector<int>::iterator iter;
    
    for(int i = 0;i < V;i++){
        for(iter = adjList[i].begin();iter != adjList[i].end();iter++){
            if(*iter == v){
                adjList[i].erase(iter);
            }
        }
    }

    return;
}

int Find(int* parent,int i){
    if(parent[i] == -1){
        return i;
    }
    return Find(parent,parent[i]);
}

void Union(int* parent,int x,int y){
    int xset = Find(parent,x);
    int yset = Find(parent,y);
    parent[xset] = yset;
}

bool isCyclic_bidirectional(vector<int> adjList[],int V){
    int* parent = new int[V];
    for(int i=0;i<V;i++){
        parent[i] = -1;
    }

    for(int i=0;i<V;i++){
        vector<int>::iterator iter; 
        for(iter = adjList[i].begin();iter != adjList[i].end();iter++){
            if(i==0 || (i>0 && *iter != (i-1))){
            int x = Find(parent,i);
            int y = Find(parent,*iter);

            if(x == y){
                return true;
            }
            Union(parent,x,y);
            }
        }
    }
    return false;
}

int main()
{
    int no_of_vertices = 6;
    vector<int> adjList[no_of_vertices];
 
    addUndirEdge(adjList,0,1);
    addUndirEdge(adjList,1,2);
    addUndirEdge(adjList,1,4);
    addUndirEdge(adjList,2,3);
    addUndirEdge(adjList,3,4);
    display(adjList,no_of_vertices);    
    
    //removeVertex(adjList,no_of_vertices,4);   --Not builded
    
    //BFS(adjList,0,no_of_vertices);

    //DFS(adjList,0,no_of_vertices);
/*
    addDirEdge(adjList,0,1);
    addDirEdge(adjList,1,2);
    addDirEdge(adjList,2,3);
    addDirEdge(adjList,2,1);
    addDirEdge(adjList,3,4);
    addDirEdge(adjList,3,1);
    addDirEdge(adjList,4,0);
    display(adjList,no_of_vertices);
*/
    //removeVertex(adjList,no_of_vertices,1);
    //display(adjList,no_of_vertices);

    //bool check = is_cyclic(adjList,no_of_vertices);
    //if(check == true){ printf("\nTrue"); } else { printf("\nFalse"); }

    //topologicalSorting(adjList,no_of_vertices);

    //kosaraju_SCC(adjList,no_of_vertices);

    //bool check = isCyclic_bidirectional(adjList,no_of_vertices);
    //if(check == true){ printf("\nTrue"); } else { printf("\nFalse"); }

    
    cout <<endl<< "Hello world!" << endl;

    return 0;
}


