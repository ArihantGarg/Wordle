#include<bits/stdc++.h>
using namespace std;

#include "../Headers/colorFunctions.hpp"
#include "../Headers/gameFunctions.hpp"

vector<string> orderedAnswers=getOrderedAnswers();
vector<string> orderedWords=getOrderedWords();

vector<string> orderedGuesses;

void printGuesses(string correctAnswer){
  for(auto word:orderedGuesses){
    for(int i=0;i<5;i++){
      if(word[i]==correctAnswer[i])
        print(word[i],"GREEN");
      else if(correctAnswer.find(word[i])!=string::npos)
        print(word[i],"YELLOW");
      else
        cout<<word[i];
    }
    cout<<"\n";
  }
}

int main()
{
  cout<<"WORDLE\n";

  string correctAnswer = chooseAnswer(orderedAnswers);
  string guess = "";
  string result = "";

  cout << "Answer is : " << correctAnswer << "\n";

  while(!checkCorrectGuess(guess,correctAnswer)){
    
    cout<<"Enter your guess: ";
    cin>>guess;
    result=computeGuess(guess,correctAnswer,orderedWords,orderedAnswers);

    
    
    if(result=="Correct Guess"){
      cout<<"Congratulations! You guessed the correct word!\n";
      break;
    }
    else if(result=="Invalid Guess"){
      cout<<"Invalid guess. Please enter a valid word.\n";
    }
    else{
      orderedGuesses.push_back(guess);
      cout<<"Incorrect guess. Try again.\n";
      cout<<"Your Guesses:\n";
      printGuesses(correctAnswer);
    }

    cout<<endl;
    
  }

  return 0;
}