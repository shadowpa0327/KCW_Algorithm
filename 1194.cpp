#pragma GCC optimize ("Ofast","unroll-loops")
#include <bits/stdc++.h>
#define PB push_back
#define eb emplace_back
#define MK make_pair
#define F first
#define S second
#define setpre(a) cout.precision(a),cout<<fixed;
#define ALL(a) a.begin(),a.end()
#define MEM(a,b) memset(a,b,sizeof a)
#define TIE ios::sync_with_stdio(0),cin.tie(0);
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;

class Graph{
public:
    int num_vertex;
    std::vector< std::list<int> > AdjList;
    vector<bool>can_reach;
    int *color,             
        *predecessor,
        *discover,
        *finish;
    int target;

    Graph():num_vertex(0){};
    Graph(int N,int T):num_vertex(N),target(T){
        can_reach.resize(num_vertex,false);
        AdjList.resize(num_vertex);
        can_reach[target]=true;
    };

    void AddEdgeList(int from, int to);
    void BFS(int Start);    
    void DFS(int Start);
    void DFSVisit(int vertex, int &time);
};

void Graph::DFS(int Start){
    color = new int[num_vertex];           
    discover = new int[num_vertex];
    finish = new int[num_vertex];
    predecessor = new int[num_vertex];

    int time = 0;                          
    for (int i = 0; i < num_vertex; i++) { 
        color[i] = 0;
        discover[i] = 0;
        finish[i] = 0;
        predecessor[i] = -1;
    }
    int i = Start;
    for (int j = 0; j < num_vertex; j++) { 
        if (color[i] == 0) {               
            DFSVisit(i, time);
        }
        i = j;                             
    }
}

void Graph::AddEdgeList(int from,int to){
    AdjList[from].push_back(to);
}


void Graph::DFSVisit(int vertex, int &time){   
    color[vertex] = 1;                         
    discover[vertex] = ++time;                 
    for(auto itr:AdjList[vertex])
    {
        if(itr==target)       //設定是否能找到target
            can_reach[vertex]=true;                  
        if (color[itr] == 0) {              
            predecessor[itr] = vertex;        
            DFSVisit(itr, time);              
        }
        if(can_reach[itr])can_reach[vertex]=true;
    }
    color[vertex] = 2;                      
    finish[vertex] = ++time;                   
}

bool cmd(const pii &l,const pii&r){
    return l.second>r.second;
}


int main(){TIE
    int n;
    cin>>n;
    while(n--){
        int r,k,n;
        cin>>r>>k>>n;
        Graph g(r,n);
        for(int i=0,from,to;i<k;i++){
            cin>>from>>to;
            g.AddEdgeList(from,to);
        }
        g.DFS(0);
        vector<pii>ans(r);
        for(int i=0;i<r;i++){
            ans[i]=MK(i,g.finish[i]);
        }
        sort(ans.begin(),ans.end(),cmd);
        for(auto it:ans){
            if(g.can_reach[it.first])cout<<it.first<<" ";
            if(it.first==n)break;
        }
        cout<<endl;
    }
    return 0;
}
