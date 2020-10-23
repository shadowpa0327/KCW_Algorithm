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
    vector<list<int> >adjlist;
    vector<list<int> >adjlist_rev;
    vector<int>visit1;
    vector<set<int> >SCC_set;
    vector<int>visit2;
    vector<int>in_number;
    vector<int>SCC_idx;
    stack<int> order;
    queue<int> bom_border;
    int round;
    int n;
    int zero_node;
    graph(int size):n(size)
    {
        round=0;
        adjlist.resize(n);
        adjlist_rev.resize(n);
        visit1.resize(n,0);
        visit2.resize(n,0);
        SCC_idx.resize(n,0);
        in_number.resize(n,0);
    }

    void addedge(int from,int to);
    void dfs(int s);
    void dfs_scc2(int s);
    void dfs_scc(int s,int counter);
    void dfs_caller();
    void collapse();
    void dfs_caller2();
    void dfs_caller3();
    void how_many_zero();
    void showedge();
    graph connect_scc();
};

void graph::how_many_zero(){
    int tmp=0;
    for(int i=0;i<n;i++){
        if(in_number[i]){
            continue;
        }else{
            tmp++;
        }
    }
    zero_node=tmp;
}

void graph::showedge(){
    for(int i=0;i<n;i++){
        for(auto it:adjlist[i]){
            cout<<i<<" "<<it<<endl;
        }
    }
    
}

void graph::addedge(int from,int to){
    in_number[to]++;
    adjlist[from].push_back(to);
    adjlist_rev[to].push_back(from);
}

graph graph::connect_scc(){
    graph tmp(round);
    for(int i=0;i<n;i++){
        for(auto it:adjlist[i]){
            if(SCC_idx[i]!=SCC_idx[it]){
                tmp.addedge(SCC_idx[i],SCC_idx[it]);
            }else{
                continue;
            }
        }
    }
    return tmp;
}

void graph::collapse(){
    SCC_set.resize(round);
    for(int i=0;i<SCC_idx.size();i++){
        SCC_set[SCC_idx[i]].insert(i);
    }
}

void graph::dfs_caller(){
    for(int i=0;i<n;i++){
        if(visit1[i]==0){
            dfs(i);
        }
    }
}

void graph::dfs_caller2(){
    while(!order.empty()){
        int current=order.top();
        order.pop();
        if(visit2[current]==0){
            //cout<<endl<<"current:"<<current<<endl;
            dfs_scc(current,round);
            round++;
        }
    }
}

void graph::dfs_caller3(){
    //cout<<"call"<<endl;
    while(!order.empty()){
        int current=order.top();
        order.pop();
        //cout<<current<<" ";
        if(visit2[current]==0){
            //cout<<endl<<"current:"<<current<<endl;
            dfs_scc2(current);
            round++;
        }
    }
    //cout<<endl;
}

void graph::dfs(int s){
    visit1[s]=1;
    for(auto it:adjlist[s]){
        if(visit1[it]==0)
            dfs(it);
    }
    visit1[s]=2;
    order.push(s);
    //bom_border.push(s);
}

void graph::dfs_scc(int s,int counter){
    visit2[s]=1;
    SCC_idx[s]=counter;
    for(auto it:adjlist_rev[s]){
        if(visit2[it]==0){
            dfs_scc(it,counter);
        }
    }
}

void graph::dfs_scc2(int s){
    visit2[s]=1;
    //cout<<s<<" ";
    for(auto it:adjlist[s]){
        if(visit2[it]==0){
            dfs_scc2(it);
        }
    }
}



int main(){TIE
    int V,E;
    int n;
    cin>>n;
    while(n--){
        cin>>V>>E;
        graph g(V);
        for(int i=0,from,to;i<E;i++){
            cin>>from>>to;
            g.addedge(from-1,to-1);
        }
        g.dfs_caller();
        g.dfs_caller2();
        //g.collapse();
        graph scc=g.connect_scc();
        //scc.dfs_caller();
        //scc.dfs_caller3();
        scc.how_many_zero();
        cout<<scc.zero_node<<endl;
    }
    return 0;
    
}

//優化方法：先把input 0 的圖先炸掉 , scc 只做環
/*
9 15
0 1
1 2
1 4
2 0
2 3
2 5
3 2
4 5
4 6
5 4
5 6
5 7
6 7
7 8
8 6
*/