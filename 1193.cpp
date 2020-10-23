//#pragma GCC optimize ("Ofast","unroll-loops")
#include <bits/stdc++.h>
#define PB push_back
#define eb emplace_back
#define MK make_pair
#define endl '\n'
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
typedef pair<int,string> pis;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;

class graph{
    public:
    vector<list<int> >adjlist;
    vector<list<int> >adjlist_rev;
    vector<int>visit;
    vector<int>visit2;
    vector<int>SCC_group_number;
    stack<int>order;
    int size;
    int counter;
    graph(int n):size(n){
        adjlist.resize(2*n);
        adjlist_rev.resize(2*n);
        visit.resize(2*n,0);
        visit2.resize(2*n,0);
        SCC_group_number.resize(2*n);
        counter=0;
    }

    void addedge(int size,vector<pis> &opinion);
    void addedge2(int from,int to);
    void showedge();
    void show_ans();
    void dfs_caller();
    graph connect_scc();
    void dfs(int s);
    void dfs_caller2();
    void dfs2(int s);
};


graph graph::connect_scc(){
    graph tmp(counter);
    for(int i=0;i<size*2;i++){
        for(auto it:adjlist[i]){
            if(SCC_group_number[i]!=SCC_group_number[it]){
                tmp.addedge2(SCC_group_number[i],SCC_group_number[it]);
            }
        }
    }
    return tmp;
}

void graph::addedge2(int from,int to){
    adjlist[from].push_back(to);
    adjlist_rev[to].push_back(from);
}

void graph::addedge(int n,vector<pis>&opinion){
    if(n<=2){
        for(int i=0;i<n;i++){
            if(opinion[i].S=="aye"){
                adjlist[opinion[i].F+size].PB(opinion[i].F);
                adjlist_rev[opinion[i].F].PB(opinion[i].F+size);
            }
            else if(opinion[i].S=="nay"){
                adjlist[opinion[i].F].PB(opinion[i].F+size);
                adjlist_rev[opinion[i].F+size].PB(opinion[i].F);
            } 
        }
    }else if(n>2){
        for(int i=0;i<n-1;i++){
            for(int j=i+1;j<n;j++){
                int idx1,idx2,not_idx1,not_idx2;
                idx1=((opinion[i].S=="aye")?opinion[i].F:opinion[i].F+size);
                idx2=((opinion[j].S=="aye")?opinion[j].F:opinion[j].F+size);
                not_idx1=((idx1>=size)?(idx1-size):(idx1+size));
                not_idx2=((idx2>=size)?(idx2-size):(idx2+size));
                adjlist[not_idx1].PB(idx2);
                adjlist_rev[idx2].PB(not_idx1);
                adjlist[not_idx2].PB(idx1);
                adjlist_rev[idx1].PB(not_idx2);
            }
        }
    }
}

void graph::showedge(){
    for(int i=0;i<size*2;i++){
        for(auto it:adjlist[i]){
            cout<<i<<" "<<it<<endl;
        }
    }
}

void graph::dfs_caller(){
    for(int i=0;i<2*size;i++){
        if(!visit[i]){
            dfs(i);
        }
    }
}

void graph::dfs(int s){
    visit[s]=1;
    for(auto it:adjlist[s]){
        if(!visit[it]){
            dfs(it);
        }
    }
    order.push(s);
}

void graph::dfs_caller2(){
    while(!order.empty()){
        int tmp=order.top();order.pop();
        if(!visit2[tmp]){
            dfs2(tmp);
            counter++;
        }
    }
}

void graph::dfs2(int s){
    visit2[s]=1;
    for(auto it:adjlist_rev[s]){
        if(!visit2[it]){
            dfs2(it);
        }
    }
    SCC_group_number[s]=counter;
}

int main(){TIE
    int N,M,K;
    while(cin>>N>>M&&(N||M)){
        graph g(N);
        for(int i=0;i<M;i++){
            cin>>K;
            vector<pis> opinions;
            for(int i=0;i<K;i++){
                string op;
                int week;
                cin>>week>>op;
                opinions.PB(MK(week-1,op));
            }
            g.addedge(K,opinions);
        }
        g.dfs_caller();
        g.dfs_caller2();


        bool flag=false;
        for(int i=0;i<N;i++){
            if(g.SCC_group_number[i]==g.SCC_group_number[i+N]){
                flag=true;
                break;
            }
        }
        graph scc=g.connect_scc();
        string ans;
        ans.clear();
        for(int i=0;i<N;i++){
            bool flag_1,flag_2;
            int source=g.SCC_group_number[i],goal=g.SCC_group_number[i+N];
            scc.dfs(source);
            flag_1=scc.visit[goal];
            scc.visit.clear();
            scc.visit.resize(scc.size*2,0);
            scc.dfs(goal);
            flag_2=scc.visit[source];
            scc.visit.clear();
            scc.visit.resize(scc.size*2,0);
            if(flag_1)ans.PB('n');
            else if(flag_2)ans.PB('y');
            else ans.PB('p');
        }
        if(flag)cout<<"It's treason, then."<<endl;
        else cout<<ans<<endl;
    }
    return 0;
}
