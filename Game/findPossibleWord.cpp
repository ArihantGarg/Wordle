#include<bits/stdc++.h>
using namespace std;

#include "../Headers/gameFunctions.hpp"
#include "../Headers/colorFunctions.hpp"

vector<string> orderedWords=getOrderedWords();
vector<string> orderedAnswers=getOrderedAnswers();

set<string> setWords(orderedAnswers.begin(),orderedAnswers.end());

void updateSetWords(vector<char> containsChars)
{
    vector<string> toErase;

    for(auto x:setWords)
    {
        for(auto y:containsChars)
        {
            if(x.find(y)==string::npos)
            {
                toErase.push_back(x);
                break;
            }
        }
    }

    for(auto x:toErase)
    {
        setWords.erase(x);
    }
}

int main(int argc,char* argv[])
{
  updateSetWords({'u','n','e'});

  for(auto curWord:setWords)
  {
    cout<<curWord<<endl;
  }

  return 0;
}