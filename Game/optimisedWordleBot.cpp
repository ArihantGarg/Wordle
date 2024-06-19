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

int main()
{
  // cout<<"WORDLE BOT HAS STARTED\n";
  // cout<<"Word to be guessed by program : "<<generatedAnswer<<"\n";

  string guess="";
  int guessNumber=0;



  do{
    guessNumber++;
    guess=chooseAnswer(setWords); // RandomAnswerChoose from set
    if(guessNumber==1)
      guess="salet";
    makeGuess(guessNumber,guess);
  }
  while(!computeGuess(guess)); // Removes impossible guesses

  // cout<<"Number of guesses needed : "<<guessNumber<<endl;
  // cout<<"WORDLE BOT IS TERMINATING"<<endl;

  ofstream fout("Files/wordleGuessCount.txt",ios::app);

  fout<<guessNumber<<" "<<generatedAnswer<<endl;

  return 0;
}