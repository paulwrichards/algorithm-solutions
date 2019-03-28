#include <bits/stdc++.h>
#include <vector>

using namespace std;

vector<string> split_string(string);
vector<int> rlt;
vector<int> res;
bool solved;
int min_len, K;
long N;
vector<int> V;


void solve(long val, int dp, int len){
    if(val > N) return;
    if(len >= min_len) return;
    if(val == N){
        min_len = len;
        res = rlt;
        solved = 1;
        return;
    }
    for(int i = dp; i < K; i++){
        rlt.push_back(val * V[i]);
        solve(val * V[i], i, len+1);
        rlt.pop_back();
    }
}

// Complete the kFactorization function below.
vector<int> kFactorization(int n, vector<int> A) {
    V = A;
    K = A.size();
    N = long(n);
    sort(A.begin(), A.end());
    solved = 0;
    min_len = 100;
    rlt.clear();
    rlt.push_back(1);

    solve(1, 0, 0);

    if(solved == 0){
        vector<int> non_res;
        non_res.push_back(-1);
        return non_res;
    }
    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string A_temp_temp;
    getline(cin, A_temp_temp);

    vector<string> A_temp = split_string(A_temp_temp);

    vector<int> A(k);

    for (int i = 0; i < k; i++) {
        int A_item = stoi(A_temp[i]);

        A[i] = A_item;
    }

    vector<int> result = kFactorization(n, A);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << " ";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
