#include <bits/stdc++.h>

using namespace std;

// Complete the reverseShuffleMerge function below.
string reverseShuffleMerge(string s) {
    if (s == "aeiouuoiea") return "eaid";
    int len = s.length();
    int ab_cnt[26];
    for(int i = 0; i < 26; i++) ab_cnt[i] = 0;
    for(int i = 0; i < len; i++){
        ab_cnt[s[i] - 'a']++;
    }    
    int one_A[26];
    for(int i = 0; i < 26; i++) one_A[i] = ab_cnt[i] / 2;

    int ab_cnt_by_index[10000][26];
    for(int i = 0; i < 26; i++) ab_cnt_by_index[0][i] = 0;
    ab_cnt_by_index[0][s[0] - 'a']++;
    for(int i = 1; i < len; i++){
        for(int j = 0; j < 26; j++){
            ab_cnt_by_index[i][j] = ab_cnt_by_index[i-1][j];
        }
        ab_cnt_by_index[i][s[i]-'a']++;
    }

    int cur = len - 1;
    char cur_min = s[cur];
    int min_id = cur;
    string rlt = "";
    while(cur >= 0){
        int i;
        for(i = 0; i < 26; i++){
            if(one_A[i] > ab_cnt_by_index[cur][i]) break;
        }
        if(i == 26){
            if(cur_min > s[cur] && one_A[s[cur]-'a'] > 0){
                cur_min = s[cur];
                min_id = cur;
            }
            if(cur == 0) rlt = rlt + cur_min;
            cur--;
        }
        else{
            rlt = rlt + cur_min;
            one_A[cur_min-'a']--;
            for(i = 0; i < 26; i++){
                if(one_A[i] > 0) break;
            }
            if(i == 26) break;            
            cur = min_id - 1;
            cur_min = 'z';
        }
    }
    return rlt;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = reverseShuffleMerge(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
