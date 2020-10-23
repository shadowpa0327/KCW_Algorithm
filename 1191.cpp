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


int w_table[10010];
int testcase_num,deck_size,initial;
bool flag;
int table[10001];

void solve(int i){
    if(w_table[i]==0){
        flag=true;
        return;
    }
    if(table[i])return;
    table[i]=1;
    int next_i_add=i+w_table[i],next_i_minus=i-w_table[i];

    if(0<=next_i_add&&next_i_add<deck_size&&!flag)
        solve(next_i_add);
    if(0<=next_i_minus&&next_i_minus<deck_size&&!flag)
        solve(next_i_minus);
}

int main(){TIE
    cin>>testcase_num;
    while(testcase_num--){
        MEM(table,0);
        flag=false;
        cin>>deck_size>>initial;
        for(int i=0;i<deck_size;i++){
            cin>>w_table[i];
        }
        solve(initial);
        (flag)?cout<<"We will watch your career with great interest.":cout<<"My disappointment is immeasurable, and my day is ruined.";
        cout<<endl;
    }
    return 0;
}
