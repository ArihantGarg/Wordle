#include<bits/stdc++.h>
using namespace std;

#include "../Headers/gameFunctions.hpp"
#include "../Headers/colorFunctions.hpp"

vector<string> orderedWords=getOrderedWords();
vector<string> orderedAnswers=getOrderedAnswers();

string generatedAnswer=chooseAnswer(orderedAnswers);

set<string> setWords(orderedAnswers.begin(),orderedAnswers.end());

void printGuess(string guess){
  for(int i=0;i<5;i++){
    if(guess[i]==generatedAnswer[i])
      print(guess[i],"GREEN");
    else if(generatedAnswer.find(guess[i])!=string::npos)
      print(guess[i],"YELLOW");
    else
      cout<<guess[i];
  }
}

void makeGuess(int guessNumber, string guess){
  // cout<<"Guess "<<guessNumber<<": ";
  // printGuess(guess);
  // cout<<endl;
}

bool computeGuess(string guess){
  if(guess==generatedAnswer){
    return 1;
  }
  else{
    // Removing impossible guesses from set

    set<string> toErase;

    for(int i=0;i<5;i++){
      if(guess[i]==generatedAnswer[i]){
        for(auto curWord:setWords){
          if(curWord[i]!=guess[i]){
            toErase.insert(curWord);
          }
        }
      }
      else if(generatedAnswer.find(guess[i])!=string::npos){
        for(auto curWord:setWords){
          if(curWord[i]==guess[i] || curWord.find(guess[i])==string::npos){
            toErase.insert(curWord);
          }
        }
      }
      else{
        for(auto curWord:setWords){
          if(curWord.find(guess[i])!=string::npos){
            toErase.insert(curWord);
          }
        }
      }
    }

    for (auto curWord:toErase){
      setWords.erase(curWord);
    }

    return 0;
  }
}

// Minimizing the max subset size
string chooseOptimizedAnswer(set<string>& setWords){
  int minSubsetSize=(int)(1e9);
  string bestWord="";

  for(auto curGuessWord:setWords){
    map<pair<set<char>,string>,int> curWordSubsets;
    int curMaxSubsetSize=-1;

    for(auto possibleAnswerWord:setWords){
      set<char> curSet;
      string curString="00000";
      
      for(int i=0;i<5;i++){
        if(curGuessWord[i]==possibleAnswerWord[i]){
          curString[i]=curGuessWord[i];
          curSet.insert(curGuessWord[i]);
        }
        else if(possibleAnswerWord.find(curGuessWord[i])!=string::npos){
          curSet.insert(curGuessWord[i]);
        }
      }

      curWordSubsets[make_pair(curSet,curString)]++;
      if(curWordSubsets[make_pair(curSet,curString)]>curMaxSubsetSize){
        curMaxSubsetSize=curWordSubsets[make_pair(curSet,curString)];
      }
      
    }

    if(curMaxSubsetSize<minSubsetSize){
      minSubsetSize=curMaxSubsetSize;
      bestWord=curGuessWord;
    }
  }

  return bestWord;
}


int main()
{
  // cout<<"WORDLE BOT HAS STARTED\n";
  // cout<<"Word to be guessed by program : "<<generatedAnswer<<"\n";

  string guess="";
  int guessNumber=0;



  do{
    guessNumber++;
    guess=chooseOptimizedAnswer(setWords); // RandomAnswerChoose from set
    // if(guessNumber==1)
    //   guess="salet";
    makeGuess(guessNumber,guess);
  }
  while(!computeGuess(guess)); // Removes impossible guesses

  // cout<<"Number of guesses needed : "<<guessNumber<<endl;
  // cout<<"WORDLE BOT IS TERMINATING"<<endl;

  ofstream fout("Files/wordleGuessCount.txt",ios::app);

  fout<<guessNumber<<" "<<generatedAnswer<<endl;

  return 0;
}