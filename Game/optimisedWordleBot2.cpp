#include<bits/stdc++.h>
using namespace std;

#include "../Headers/gameFunctions.hpp"
#include "../Headers/colorFunctions.hpp"

vector<string> orderedWords=getOrderedWords();
vector<string> orderedAnswers=getOrderedAnswers();

string generatedAnswer=chooseAnswer(orderedAnswers);

set<string> setWords(orderedAnswers.begin(),orderedAnswers.end());

set<string> otherSetWords(orderedWords.begin(),orderedWords.end());

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
  cout<<"Guess "<<guessNumber<<": ";
  printGuess(guess);
  cout<<endl;
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

  for(auto curGuessWord:otherSetWords){
    map<pair<int,string>,int> curWordSubsets;
    int curMaxSubsetSize=-1;

    for(auto possibleAnswerWord:setWords){
      int curInt=0;
      string curString="00000";
      
      for(int i=0;i<5;i++){
        if(curGuessWord[i]==possibleAnswerWord[i]){
          curString[i]=curGuessWord[i];
          curInt|=(1<<(curGuessWord[i]-'a'));
        }
        else if(possibleAnswerWord.find(curGuessWord[i])!=string::npos){
          curInt|=(1<<(curGuessWord[i]-'a'));
        }
      }

      curWordSubsets[make_pair(curInt,curString)]++;
      if(curWordSubsets[make_pair(curInt,curString)]>curMaxSubsetSize){
        curMaxSubsetSize=curWordSubsets[make_pair(curInt,curString)];
      }
      
    }

    if((curMaxSubsetSize<minSubsetSize) || (curMaxSubsetSize==minSubsetSize && 
      setWords.find(bestWord) == setWords.end() && setWords.find(curGuessWord)!=setWords.end())){
      minSubsetSize=curMaxSubsetSize;
      bestWord=curGuessWord;
    }
  }

  return bestWord;
}


int main(int argc,char* argv[])
{
  // if(argc>1)
  //   cout<<argv[1]<<endl;

  if(argc>1)
    generatedAnswer=orderedAnswers[stoi(argv[1])-1];
  
  cout<<"WORDLE BOT HAS STARTED\n";
  cout<<"Word to be guessed by program : "<<generatedAnswer<<"\n";

  string guess="";
  int guessNumber=0;

  do{
    guessNumber++;
    if(guessNumber==1)
        guess="arise"; // First word is always this as no differentiating information yet, hence hard-coded to save processing time
    else
      guess=chooseOptimizedAnswer(setWords); // RandomAnswerChoose from set
    makeGuess(guessNumber,guess);
  }
  while(!computeGuess(guess)); // Removes impossible guesses

  cout<<"Number of guesses needed : "<<guessNumber<<endl;
  cout<<"WORDLE BOT IS TERMINATING"<<endl;

  // ofstream fout("Files/wordleGuessCount.txt",ios::app);
  
  // fout<<guessNumber<<" "<<generatedAnswer;

  // if(argc>1)
  //     fout<<" "<<argv[1];

  // fout<<endl;

  return 0;
}