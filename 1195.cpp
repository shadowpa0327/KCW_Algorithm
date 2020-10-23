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

class graph{
    public:
    vector<list<pii> >adjlist;
    vector<int>visit;
    vector<int>color;
    int size;
    int max_time;
    int soucre;

    graph(int n,int s):size(n),soucre(s){
        color.resize(size,0);
        adjlist.resize(size);
        max_time=0;
    }
    void addedge(int from ,int to,int weight);
    int DFS(int s);
    void create();
    void showedge();

};

void graph::addedge(int from,int to,int weight){
    adjlist[from].PB(MK(to,weight));
}

void graph::create(){
    for(int i=0,from,weight;i<size;i++){
        cin>>from>>weight;
        if(i==soucre||from<0)continue;
        addedge(from,i,weight);
    }
}

void graph::showedge(){
    for(int i=0;i<size;i++){
        for(auto it:adjlist[i])
        {
            cout<<i<<" "<<it.first<<endl;
        }
    }
}

int graph::DFS(int s){
    int tmp=0;
    color[s]=1;
    for(auto it:adjlist[s]){
        if(color[it.first]==0){
            tmp=max(tmp,DFS(it.first)+it.second);
        }
    }
    color[s]=2;
    return tmp;
}


int main(){TIE
    int n;
    cin>>n;
    while(n--){
        int n,s;//people,source
        cin>>n>>s;
        graph g(n,s);
        g.create();
       // g.showedge();
        cout<<g.DFS(s)<<endl;
    }
    return 0;
}
