#include <bits/stdc++.h>
using namespace std;

int main()
{
  ifstream fin("Files/wordleGuessCount.txt");
  int failCount=0,totalCount=0;

  int curGuessCount=0;
  string curWord="";

  vector<pair<int,string>> v;

  while(fin>>curGuessCount)
  {
    fin>>curWord;
    if(curGuessCount>6){
      failCount++;
      v.push_back(make_pair(curGuessCount,curWord));
    }
      
    totalCount++;

    fin>>curWord;
  }

  cout<<failCount<<" "<<totalCount<<endl;

  for(auto x:v){
    cout<<x.first<<" "<<x.second<<endl;
  }

  return 0;
}
