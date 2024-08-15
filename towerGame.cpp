#include<iostream> 
#include<stack>
#include<map>
#include<vector>
using namespace std;

int checkBackCount(vector<char> v, char toCheck) {
    int count =0;
    for(int i=v.size()-1;i>=0;i--) {
        if(v[i] == toCheck) count++;
        else break;
    }
    return count;
}
int maxLenOfSolution = 1e4;
auto start = chrono::high_resolution_clock::now();

void findSolution(int numOfTowers,int sizeOfTower, int numOfEmptyTowers,vector< vector<char> >& towerGrid, vector<pair<int,int>>& solution) {
    // base case check if it is recquired solution 
    bool foundSolution = true;
    int empty = 0;
    for(int i=0;i<numOfTowers;i++) {
       vector<char> st =  towerGrid[i];
       map<char,int> mp;
       while(!st.empty()){
        char charTop = st.back();
        mp[charTop] ++;
        st.pop_back();
       }
       if(mp.size()>1){
            foundSolution = false;
       }
       if (mp.size()==0) {
          empty++;
       }
    }
    if (foundSolution and empty == numOfEmptyTowers) {
        // print the solution here
        if (maxLenOfSolution > solution.size()) { // only print better solution every time
            int count = 0;
            cout<<endl<<"-----------😎 Horray!! solution ------"<<endl;
            for(int i=0;i<solution.size();i++) {
                if (i!=0 && solution[i]== solution[i-1]) continue;
                count++;
                cout<<"move elements from "<<solution[i].first+1<<" to "<<solution[i].second+1<<endl;
            }
            auto end = std::chrono::high_resolution_clock::now();
            chrono::duration<double> duration = end - start;
            cout<<"------ Total Size & duration: "<<count<<" : "<<duration.count()<<"s -------------"<<endl;
            cout<<"--------Congratulations 🥳 You Solved IT !!----"<<endl;
            


            maxLenOfSolution = solution.size();
        }
        return;
    }
    if(solution.size() > maxLenOfSolution) return;
    // // check if it is in hell 
    if(solution.size()>2) {
        pair<int,int> lastOne = solution[solution.size()-1];
        pair<int,int> lastSecond = solution[solution.size()-2];
        if(lastSecond.first == lastOne.second && lastOne.first == lastSecond.second) return;
    }
    // move one by one and check if solution it is or backtrack the solution
    for(int i=0;i<numOfTowers;i++) {
        // if ith tower is empty move on 
        if (towerGrid[i].empty()) continue;
         // check if top of each tower can be moved to next any of them 
        for(int j=0;j<numOfTowers;j++) {
            if(j==i) continue;
            char topOnIthTower = towerGrid[i].back();
            // check if it is an empty tower or its top matches
            if(towerGrid[j].empty() || (topOnIthTower == towerGrid[j].back() && towerGrid[j].size() < sizeOfTower)) {
                // check how many element can be moved to tower j from i
                int backCountInI = checkBackCount(towerGrid[i],topOnIthTower);
                // int backCountInJ = checkBackCount(towerGrid[j],topOnIthTower);
                // if size is greater then what can be pushed move on
                if(backCountInI > sizeOfTower-towerGrid[j].size()) continue;
                // if j is empty and i has all element equal move on
                if(towerGrid[j].empty() && backCountInI == towerGrid[i].size()) continue;
                // put all elements to j available in i
                towerGrid[j].push_back(topOnIthTower);
                towerGrid[i].pop_back();
                solution.push_back(pair(i,j));
                findSolution(numOfTowers, sizeOfTower,  numOfEmptyTowers, towerGrid,solution);
                towerGrid[j].pop_back();
                towerGrid[i].push_back(topOnIthTower);
                solution.pop_back();
            }
        }   
    }          
}
int main() {
 // take input 
 int numTower=4 , emptyTower = 1 ,sizeOfTower= 3;
 vector< vector<char> > grid;
 cout<<"Enter Number of Towers: "<<endl;
 cin>>numTower;
 cout<<"Enter number of Empty towers: "<<endl;
 cin>>emptyTower;
 cout<<"Enter size of tower: "<<endl;
 cin>>sizeOfTower;
 cout<<"enter each tower from top to bottom."<<endl;
 for(int i=0;i<numTower-emptyTower;i++) {
    vector<char> singleTowerV;
    for(int j=0;j<sizeOfTower;j++) {
        char currentColor;
        cin>>currentColor;
        singleTowerV.push_back(currentColor);
    }
    // reverse vector and put
    reverse(singleTowerV.begin(),singleTowerV.end());
    grid.push_back(singleTowerV);
 }
 for(int i=0;i<emptyTower;i++) {
    vector<char> emptyTower;
    grid.push_back(emptyTower);
 }
 vector<pair<int,int>> solution;
 cout<<"............Doing Science.........."<<endl;
 // input is ready let us add some tadka
 start = chrono::high_resolution_clock::now();
 findSolution(numTower, sizeOfTower, emptyTower, grid, solution);
 
 return 0;
}