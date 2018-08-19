#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int numP;
    int numR;
    cin >> numP;
    cin >> numR;
    vector<vector<int>> v;
    for(int i=0; i<numR; i++){
        vector<int> tempV;
        int num;
        cin >> num;
        while(num != -1){
            tempV.push_back(num);
            cin >> num;
        }
        sort(tempV.begin(), tempV.end());
        v.push_back(tempV);
    }
    int win[numR];
    int num;
    for(int i=0; i<numR; i++){
        cin >> num;
        win[i] = num;
    }
    for(int i=0; i<numR; i++){
        if(win[i] >= v[i].size()){
            cout << -1 << endl;
        }else{
            cout << v[i][win[i]] << endl;
        }
    }
    
    return 0;
}
