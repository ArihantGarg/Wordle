#include <bits/stdc++.h>
using namespace std;

#include "../Headers/gameFunctions.hpp"

vector<string> orderedWords = getOrderedWords();
vector<string> orderedAnswers = getOrderedAnswers();

set<string> setWords(orderedAnswers.begin(), orderedAnswers.end());
set<string> otherSetWords(orderedWords.begin(), orderedWords.end());

void computeGuess(string guess, string result)
{
    set<string> toErase;

    for (int i = 0; i < 5; i++)
    {
        if (result[i] == 'G')
        {
            for (auto curWord : setWords)
            {
                if (curWord[i] != guess[i])
                {
                    toErase.insert(curWord);
                }
            }
        }
        else if (result[i] == 'Y')
        {
            for (auto curWord : setWords)
            {
                if (curWord[i] == guess[i] || curWord.find(guess[i]) == string::npos)
                {
                    toErase.insert(curWord);
                }
            }
        }
        else
        {
            for (auto curWord : setWords)
            {
                if (curWord.find(guess[i]) != string::npos)
                {
                    toErase.insert(curWord);
                }
            }
        }
    }

    for (auto curWord : toErase)
    {
        setWords.erase(curWord);
    }
}

void computeGuesses(vector<pair<string, string>> vectorGuesses)
{
    for (auto curGuess : vectorGuesses)
    {
        computeGuess(curGuess.first, curGuess.second);
    }
}

// Minimizing the max subset size
string chooseOptimizedAnswer(set<string> &setWords)
{
    int minSubsetSize = (int)(1e9);
    string bestWord = "";

    for (auto curGuessWord : otherSetWords)
    {
        map<pair<int, string>, int> curWordSubsets;
        int curMaxSubsetSize = -1;

        for (auto possibleAnswerWord : setWords)
        {
            int curInt = 0;
            string curString = "00000";

            for (int i = 0; i < 5; i++)
            {
                if (curGuessWord[i] == possibleAnswerWord[i])
                {
                    curString[i] = curGuessWord[i];
                    curInt |= (1 << (curGuessWord[i] - 'a'));
                }
                else if (possibleAnswerWord.find(curGuessWord[i]) != string::npos)
                {
                    curInt |= (1 << (curGuessWord[i] - 'a'));
                }
            }

            curWordSubsets[make_pair(curInt, curString)]++;
            if (curWordSubsets[make_pair(curInt, curString)] > curMaxSubsetSize)
            {
                curMaxSubsetSize = curWordSubsets[make_pair(curInt, curString)];
            }
        }

        if ((curMaxSubsetSize < minSubsetSize) || (curMaxSubsetSize == minSubsetSize &&
                                                   setWords.find(bestWord) == setWords.end() && setWords.find(curGuessWord) != setWords.end()))
        {
            minSubsetSize = curMaxSubsetSize;
            bestWord = curGuessWord;
        }
    }

    return bestWord;
}

int main(int argc, char *argv[])
{
    vector<pair<string,string>> vectorGuesses;
    for (int i = 1; i < argc; i += 2)
    {
        vectorGuesses.push_back(make_pair(argv[i], argv[i + 1]));
    }

    computeGuesses(vectorGuesses);

    ofstream fout("Files/bestGuess.txt");

    fout <<((argc==1)?"arise":chooseOptimizedAnswer(setWords)) << endl;

    return 0;
}