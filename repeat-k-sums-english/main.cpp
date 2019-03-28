#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

vector<long long> ans;
long long *val;
bool* chk;
int n, k;
int N;
map<long long, vector<int> > myMap;

typedef map<long long, vector<int> >::const_iterator MapIterator;

int getN(int n, int k){    
    int loop_cnt = n - 1;
    long long rlt = 1;
    if(loop_cnt > k) loop_cnt = k;

    for(int i = 1; i <= loop_cnt; i++){
        rlt *= (n + k - i);
        rlt /= i;
    }

    int res = (int)rlt;
    return res;

}

void makeSum(long long sum, long long left_k, int dp){
    if(left_k == 0){
        //if(myMap[sum].empty() == true) return;
        int tmp_id = myMap[sum].back();
        myMap[sum].pop_back();
        chk[tmp_id] = 1;
        return;
    }
    if(dp == 0){        
        makeSum(sum + left_k * ans[0], 0, dp - 1);
    }
    else{
        for(int i = 0; i <= left_k; i++){
            makeSum(sum + i * ans[dp], left_k - i, dp - 1);
        }
    }
}

void solve(int minID, int dp){
    if(dp == n) return;
    int i, j;
    for(i = minID; i < N; i++){
        if(chk[i] == 0) break;
    }
    ans.push_back(val[i] - ans[0] * (k-1));
    //cout << ans[dp] << " ";
    for(j = 1; j <= k; j++){
        makeSum(ans[dp]*j, k-j, dp-1);
    }
    solve(i, dp+1);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int T;
    cin >> T;    
    while(T--){        
        cin >> n >> k;
        N = getN(n, k);

        chk = new bool[N];
        val = new long long[N];        
        for(int i = 0; i < N; i++) chk[i] = 0;
        
        for(int i = 0; i < N; i++){
            cin >> val[i];
        }
        sort(val, val + N);

        ans.push_back(val[0] / k);
        chk[0] = 1;

        for(int i = 0; i < N; i++){
            long long fI = val[i];
            MapIterator it = myMap.find(fI);
            if(it != myMap.end()){
                myMap[fI].push_back(i);
            }
            else{
                vector<int> tmp_pos;
                tmp_pos.push_back(i);
                myMap[fI] = tmp_pos;
            }
            
        }      
        /*for(MapIterator it = myMap.begin(); it != myMap.end(); it++){
            cout << it->first << endl;
            typedef vector<int>::const_iterator vectorIterator;
            for(vectorIterator vit = it->second.begin(); vit != it->second.end(); vit++){
                cout << *vit << " ";
            }
            cout << endl;
        }*/  

        /*long long tmp_aa = 56;
        MapIterator it = myMap.find(tmp_aa);
        bool flag = (it != myMap.end());
        if(flag) cout << T << " " << myMap[tmp_aa][0] << endl;*/
        //cout << ans[0] << " ";

        solve(1, 1);

        cout << ans[0];
        for(int i = 1; i < n; i++) cout << " " << ans[i];
        cout << endl;
        
        myMap.clear();
        ans.clear();
    }
    return 0;
}
