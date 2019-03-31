#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the arrayManipulation function below.

bool cmpBF(const vector<int> &a, const vector<int> &b){
    return (a[0] < b[0]);
}

bool cmpBS(const vector<int> &a, const vector<int> &b){
    return (a[1] < b[1]);
}

long arrayManipulation(int n, vector<vector<int>> queries) {
    vector<vector<int>> sorted_bf = queries;
    vector<vector<int>> sorted_bs = queries;

    sort(sorted_bf.begin(), sorted_bf.end(), cmpBF);
    sort(sorted_bs.begin(), sorted_bs.end(), cmpBS);

    int m = queries.size();

    vector<int> points;
    vector<int> points_val;
    vector<int> points_fos;

    int cur = sorted_bf[0][0];
    int tmp_fos;
    int s_cur = 0;
    int e_cur = 0;

    while(1){
        if(s_cur >= m && e_cur >= m) break;
        if(s_cur < m && (sorted_bf[s_cur][0] <= sorted_bs[e_cur][1] + 1)){
            tmp_fos = 0;
            points.push_back(sorted_bf[s_cur][0]);
            points_val.push_back(sorted_bf[s_cur][2]);
            points_fos.push_back(tmp_fos);
            s_cur++;
        }else{
            tmp_fos = 1;
            points.push_back(sorted_bs[e_cur][1] + 1);
            points_val.push_back(sorted_bs[e_cur][2]);
            points_fos.push_back(tmp_fos);
            e_cur++;
        }
    }
/*
    for(int i = 0; i < 2 * m; i++){
        cout << points[i] << " " << points_val[i] << " " << points_fos[i] << endl;
    }
*/
    long sum = 0;
    long rlt = 0;
    int pre_cur = points[0];
    for(int i = 0; i < 2*m; i++){
        while(pre_cur == points[i]){
            if(points_fos[i] == 0){
                sum = sum + points_val[i];
            }
            else{
                sum = sum - points_val[i];
            }
            i++;
        }       
        if(rlt < sum) {
            rlt = sum;
        }
        pre_cur = points[i];
        i--;
    }

    return rlt;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<vector<int>> queries(m);
    for (int i = 0; i < m; i++) {
        queries[i].resize(3);

        for (int j = 0; j < 3; j++) {
            cin >> queries[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    long result = arrayManipulation(n, queries);

    fout << result << "\n";

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
