#include <iostream>
#include <vector>
#include "Random.h"
using namespace std;

namespace WordList{
    vector<string_view> words {"star", "hoshino", "science", "math", "luggage", "unsteady", "chemistry"};
    string_view getRandomWord(){
        return words[Random::get(0, words.size() - 1)];
    }
}

class Session{
    private:
        string_view currentWord = WordList::getRandomWord();
        int maxGuess = 5;
        vector<char> correctGuesses{};
        vector<char> allGuesses{};
        vector<char> incorrectGuesses{};
    public:
        int getMaxGuess(){
            return maxGuess;
        }

        bool checkGuess(char letter){
            for(int i = 0; i < currentWord.length(); i++){
                if (letter == currentWord[i]){
                    return true;
                }
            }
            return false;
        }

        string_view getWord(){
            return currentWord;
        }

        void draw(){
            cout << "The word:";
            for (int i = 0; i < currentWord.size(); i++){
                cout << "_";
            }
            cout << endl;
        }

        void draw(vector<char> correctGuesses){
            cout << "The word:";
            for (int i = 0; i < currentWord.size(); i++){
                    if(find(correctGuesses.begin(), correctGuesses.end(), currentWord[i]) != correctGuesses.end()){
                        cout << currentWord[i];
                    }   
                    else {
                        cout << "_";
                    }
               
    
            }
            cout << "       incorrect: ";
            for (int i = 0; i < maxGuess; i++){
               if(i < incorrectGuesses.size()){
                    cout << incorrectGuesses[i];
               }
               cout << "_";
    
            }
            cout << endl;
        }

        char acceptInput(){
            while(true){
                char letter = ' ';
                cout << "Enter a letter" << endl;
                cin >> letter;
                if (letter > 'z' || letter < 'a'){
                    cout << "Invalid input";
                    continue;
                }
                for (auto i : allGuesses){
                    if (i == letter){
                        cout << "Already guessed" << endl;
                        continue;
                    }
                }
                allGuesses.push_back(letter);

                if(checkGuess(letter) == true){
                    correctGuesses.push_back(letter);
                    draw(correctGuesses);
                }
                else{
                    cout << "Incorrect guess" << endl;
                    incorrectGuesses.push_back(letter);
                    draw(correctGuesses);
                }

                return letter;
            }
           
        }
};



int main(){
    char letter;
    cout << "Welcome to C++man (a variant of Hangman)" << endl;
    cout << "To win: guess the word.  To lose: run out of pluses." << endl;
    Session s;
    int maxGuess = s.getMaxGuess();
    int currentGuess = 0;

    s.draw();
    while(currentGuess <= maxGuess){
        letter = s.acceptInput();
        if (s.checkGuess(letter) == false){
            currentGuess += 1;
        }
    }
    
    
    return 0;
}
