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
    vector<int>vertex_number;
    vector<vector<int> >adjlist;
    vector<vector<int> >adjlist_rev;//get SCC
    vector<int>visit;
    vector<int>visit2;//for final bomb;
    vector<int>in_number;
    queue<int>bomb;
    vector<pii>order;
    stack<int>topo_order;
    int size;
    int edge_number;
    int explosive_num;

    graph(int n,int e):size(n),edge_number(e){
        adjlist.resize(n);
        vertex_number.resize(n);
        visit.resize(n,0);
        visit2.resize(n,0);
        //adjlist_rev.resize(n);
        in_number.resize(n,0);
        explosive_num=0;
    }
    void addedge(int from ,int to);
    void DFS(int s,bool flag);
    void DFS_findSCC();
    void DFS_reverse(int s);
    void DFS2(int s);
    void explosition();
    void BFS(int s);
    void count_zero();//count how many vertex with zero input edge
    void form_bomb_order();//get how many vertex with 
    void create();
    void showedge();
    void showtopo();
};

bool cmd(const pii &l,const pii &r)
{
    return l.second>r.second;
}

void graph::explosition(){
   
    //cout<<explosive_num<<endl;
    while (!topo_order.empty())
    {
        int tmp=topo_order.top();
        topo_order.pop();
       // for(auto it:visit2)cout<<it<<" ";
        //cout<<endl;
        if(!visit2[tmp]){
            //cout<<"current:"<<tmp<<endl;
            explosive_num++;
            DFS2(tmp);
        }
    }
    
}

void graph::showtopo(){
    while (!topo_order.empty())
    {
        cout<<topo_order.top()<<" ";
        topo_order.pop();
    }
    cout<<endl;
}

void graph::count_zero(){
    for(int i=0;i<in_number.size();i++){
        if(in_number[i]==0&&!visit[i]){
            explosive_num++;
            DFS(i,false);
        }else{
            bomb.push(i);
        }
    }    
}


void graph::addedge(int from,int to){
    adjlist[from].push_back(to);
}

void graph::create(){
    for(int i=0,from,to;i<edge_number;i++){
        cin>>from>>to;
        //cout<<from<<" "<<to<<endl;
        in_number[to-1]++;
        addedge(from-1,to-1);
    }
}



void graph::DFS_findSCC(){
    while(!bomb.empty()){
        int i=bomb.front();
        bomb.pop();
        if(visit[i]==0){
            //explosive_num++;
            DFS(i,true);
        }
    }
}

void graph::DFS(int s,bool flag){
    visit[s]=1;
    if(!flag)visit2[s]=1;
    for(auto it : adjlist[s]){
        if(visit[it]==0)
            DFS(it,flag);
    }
    if(flag)topo_order.push(s);
    if(!flag)visit2[s]=2;
    visit[s]=2;
}

void graph::DFS2(int s){
    visit2[s]=1;
    for(auto it : adjlist[s]){
        if(visit2[it]==0)
            DFS2(it);
    }
    visit2[s]=2;
}




void graph::showedge(){
    for(int i=0;i<size;i++){
        for(auto it:adjlist[i])
        {
            cout<<i<<" "<<it<<endl;
        }
    }
}

int main(){TIE
    int n;
    cin>>n;
    while(n--){
        int V,E;
        cin>>V>>E;
        graph g(V,E);
        g.create();
        //cout<<"what"<<endl;
        g.count_zero();
        g.DFS_findSCC();
        g.explosition();
       // g.showtopo();
        cout<<g.explosive_num<<endl;
    }
    return 0;
}