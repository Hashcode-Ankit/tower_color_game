#include<iostream> 
#include<stack>
#include<map>
#include<vector>
using namespace std;

void findSolution(int numOfTowers,int sizeOfTower, int numOfEmptyTowers, int numOfColors,vector< std::stack<char> >& towerGrid, vector<string>& solution) {
    // base case check if it is recquired solution 
   
    stack<char> towerGrid1THPosition = towerGrid[0];
    stack<char> towerGrid2THPosition = towerGrid[1];
    stack<char> towerGrid3THPosition = towerGrid[2];
    stack<char> towerGrid4THPosition = towerGrid[3];
    bool foundSolution = true;
    int empty = 0;

    for(int i=0;i<numOfTowers;i++) {
       stack<char> st =  towerGrid[i];
       map<char,int> mp;
       while(!st.empty()){
        char charTop = st.top();
        mp[charTop] ++;
        st.pop();
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
        cout<<endl<<"printing solution here: "<<endl;
        for(int i=solution.size()-1;i>=0;--i) {
            cout<<solution[i]<<endl;
        }
        cout<<endl<<"solution end here"<<endl;
        return;
    }
    if(solution.size()>4) {
        if (solution[solution.size()-1] == solution[solution.size()-3] and solution[solution.size()-2] == solution[solution.size()-4])
        {
            return;
        }
    }
    // move one by one and check if solution it is or backtrack the solution
    for(int i=0;i<numOfTowers;i++) {
        stack<char> towerGridITHPosition = towerGrid[i];
        // if ith tower is empty move on 
        if (towerGrid[i].empty()) continue;
        // check if top of each tower can be moved to next any of them 
        for(int j=0;j<numOfTowers;j++) {
           if(j==i) continue;
           stack<char> elementOFJthTower = towerGrid[j];
           char topOnIthTower = towerGrid[i].top();
           // check if it is an empty tower
           if(towerGrid[j].empty()) {
                // just put the element 
                towerGrid[j].push(topOnIthTower);
                towerGrid[i].pop();
                solution.push_back("move "+ to_string(i) + "element to "+ to_string(j));
                findSolution(numOfTowers, sizeOfTower,  numOfEmptyTowers,  numOfColors, towerGrid,solution);
                solution.pop_back();
                towerGrid[j].pop();
                towerGrid[i].push(topOnIthTower);
            }else {
                char topOnJthTower = towerGrid[j].top();
                int sizeT2 = towerGrid[j].size();
                // if both are equal 
                if (topOnIthTower == topOnJthTower) {
                    // if size of tower is less in jth tower move it 
                    if(sizeT2 < sizeOfTower){
                        towerGrid[j].push(topOnIthTower);
                        towerGrid[i].pop();
                        solution.push_back("move "+ to_string(i) + "element to "+ to_string(j));
                        findSolution(numOfTowers, sizeOfTower,  numOfEmptyTowers,  numOfColors, towerGrid, solution);
                        solution.pop_back();
                        towerGrid[j].pop();
                        towerGrid[i].push(topOnIthTower);
                    }
                    // else in next iterations it automatically be moved to empty towers
                }
           }
          
        }
    }
}
int main() {
 // take input 
 int numTower=4 , emptyTower = 1 ,sizeOfTower= 3, colours = 3;
 std::vector< stack<char> > grid;
 vector<char> t1 = {'A', 'B', 'A'};
 vector<char> t2 = {'A', 'C', 'B'};
 vector<char> t3 = {'B', 'C', 'C'};
 stack<char> st1, st2, st3,st4;
 map<char,int> mp1,mp2,mp3,mp4;
//  for(auto x: t1){
//     st1.push(x);
//     mp1[x]++;
//  }
//  for(auto x: t2){
//     st2.push(x);
//     mp2[x]++;
//  }
//  for(auto x: t3){
//     st3.push(x);
//     mp3[x]++;
//  }
//  grid.push_back(st1);
//  grid.push_back(st2);
//  grid.push_back(st3);
//  grid.push_back(st4);

 cout<<"Enter Number of Towers: "<<endl;
 cin>>numTower;
 cout<<"Enter number of Empty towers: "<<endl;
 cin>>emptyTower;
 cout<<"Enter number of size of tower: "<<endl;
 cin>>sizeOfTower;
 cout<<"enter number of colors"<<endl;
 cin>>colours;
 cout<<"enter each tower representing color from bottom to top ...."<<endl;
 for(int i=0;i<numTower-emptyTower;i++) {
    cout<<"enter colors in "<<i+1<<" tower"<<endl;
    stack<char> singleTower;
    for(int j=0;j<sizeOfTower;j++) {
        char currentColor;
        cin>>currentColor;
        singleTower.push(currentColor);
    }
    grid.push_back(singleTower);
 }
 vector<string> solution;
 // input is ready let us add some tadka
 findSolution(numTower, sizeOfTower, emptyTower,colours, grid, solution);
 return 0;
}