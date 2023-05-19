#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

#define Green "\033[32m"
#define Red "\033[31m"
#define Reset "\033[0m"
#define Orange "\u001b[38;5;216m"
#define Gray "\u001b[38;5;8m"
#define Up "\033[A"

void howToPlay();
void menu();
void statistics();
void mainGame();
void selectRandomWordGoal();
void wordGoalToArray();
void wordToArray(string s);
bool userEnter();
void resetStats();
void calculateAverageAttempts();
void calculateWinPercentage();
bool allowedWord();

// GLOBAL VARIABLES
int timesPlayed = 0;
vector<int> currentAttemptsList = {};
vector<string> wordsList = {};
vector<string> resultsList = {};
int totalAttempts = 0;
double averageAttempts = 0;
int totalWins = 0;
double winPercentage = 0;
int currentStreak = 0;
int longestStreak = 0;
string wordGoal = "";
string inputWord = "";
bool allowed = false;
bool gameIsRunning = false;
vector<char> keyboard = {'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m'};
vector<int> isGreen = {};
vector<int> isYellow = {};
vector<int> isGray = {};
int firstAttempt = 0;
int letterWords = 0;
string allowedText = "";
string isWord = "";

// MAIN & FUNCTIONS
int main(int argc, char *argv[]) {
    system("clear");
    letterWords = atoi(argv[1]);
    isWord = argv[2];
    allowedText = argv[3];
    cout << allowedText << endl;
    menu();
    return 0;
}

void menu() {
  int option = 0;
  while (option <= 0 || option >= 6) {
    cout << "=========================\n   WELCOME TO "
            "WORDLE\n========================="
         << endl;
    cout << "\n1. Play Wordle\n2. How to Play\n3. Statistics Summary\n4. Reset "
            "Statistics\n5. Exit\n\nSelect an option: ";
    cin >> option;
  }
  if (option == 1)
  {
      mainGame();
  }
  else if (option == 2) {
    howToPlay();
  } else if (option == 3) {
    statistics();
  }
  else if (option == 4)
  {
      resetStats();
  }
  else if (option == 5)
  {
      return;
  }
  return;
}

void howToPlay() {
    system("clear");
  cout << "=============================================\n                 HOW "
          "TO PLAY\n============================================="
       << endl;
  cout << "Guess the Wordle in 6 tries.\n" << endl;
  cout << "HOW TO PLAY:\n- Each guess must be a valid 5 letter word\n- The "
          "color of the tiles will change to show\n  you how close your guess "
          "was to the word.\n"
       << endl;
  cout << "\n " << Green << "---" << Reset << "  ---  ---  ---  ---\n"
       << Green << "| W |" << Reset << "| E || A || R || Y |\n " << Green
       << "---" << Reset << "  ---  ---  ---  ---\n"
       << endl;
  cout << "W is in the word and in the correct spot.\n" << endl;
  cout << "\n "
       << "--- " << Orange << " --- " << Reset << "---  ---  ---\n| P |"
       << Orange << "| I |" << Reset << "| L || L || S |\n --- " << Orange
       << " --- " << Reset << " ---  ---  ---\n"
       << endl;
  cout << "I is in the word but in the wrong spot.\n" << endl;
  cout << " ---  ---  ---  " << Gray << "---  " << Reset << "---" << endl;
  cout << "| V || A || G |" << Gray << "| U |" << Reset << "| E |" << endl;
  cout << " ---  ---  ---  " << Gray << "---  " << Reset << "---" << endl;
  cout << "U is not in the word in any spot.\n\n" << endl;
  cout << "Press [enter] to continue" << endl;
  
  cin.ignore();
  while (cin.get() != '\n') {
    cin.ignore();
    system("clear");
    howToPlay();
    return;
  }
  system("clear");
  menu();
  return;
}

void statistics() {
    system("clear");
  cout << "==========================\n    STATISTICS "
          "SUMMARY\n==========================\n"
       << endl;
  cout << "Times Played:" << setw(13) << right << timesPlayed << endl;
  cout << "Average Attempts:" << setw(9) << right << averageAttempts << endl;
  cout << "Win Percentage:" << setw(10) << right << winPercentage << "%"
       << endl;
  cout << "Current Streak:" << setw(11) << right << currentStreak << endl;
  cout << "Longest Streak:" << setw(11) << right << longestStreak << endl;
  cout << "\n\n--------------------------\nWORD     ATTEMPTS      "
          "WIN\n--------------------------"
<< endl;
for (int i = wordsList.size()-1; i >= 0; i--)
{
    cout << wordsList[i] << setw(5) << currentAttemptsList[i] << setw(16) << resultsList[i] << endl;
}
  cout << "\n\nPress [enter] to continue" << endl;
  cin.ignore();
  while (cin.get() != '\n') {
    cin.ignore();
    howToPlay();
    return;
  }
  system("clear");
  menu();
  return;
}

void mainGame() 
{   
    system("clear");
    // Selecting a randomized word goal and converting it into an array
    selectRandomWordGoal();
    isGreen = {};
    isYellow = {};
    isGray = {};
    int attempt = 1;
    totalAttempts++;
    timesPlayed++;
    calculateAverageAttempts();
    bool boolAttempt = false;
    while (attempt <=6 && boolAttempt == false)
    {
        totalAttempts++;
        firstAttempt++;
        boolAttempt = userEnter();
        ++attempt;
        if (boolAttempt == true)
        {
            totalWins++;
            currentStreak++;
            if (currentStreak > longestStreak)
            {
                longestStreak = currentStreak;
            }
            cout << "\n\nSplendid!\n\n" << endl;
            wordsList.push_back(wordGoal);
            resultsList.push_back("Yes");
            currentAttemptsList.push_back(attempt-1);
        }
    }
    calculateWinPercentage();
    currentAttemptsList.push_back(attempt);
    if (boolAttempt == false)
    {
        currentStreak = 0;
        currentAttemptsList.push_back(attempt);
        wordsList.push_back(wordGoal);
        resultsList.push_back("No");
        cout << "The word was:" <<  wordGoal << "\n\n\nBetter luck next time!\n\n" <<endl;
    }
    cout << "Press [enter] to continue" << endl;

    cin.ignore();
    while (cin.get() != '\n') {
      cin.ignore();
      cout << "Press [enter] to continue" << endl;
      return;
    }
    ofstream myfile ("keyboardStatus.txt");
    myfile << "false" << endl;
    for (int i = 0; i < 26; i++)
    {
        myfile << "white" << endl;
    }
    system("clear");
    menu();
    return;
}

void resetStats() {
  timesPlayed = 0;
  totalAttempts = 0;
  averageAttempts = 0;
  totalWins = 0;
  winPercentage = 0.0;
  currentStreak = 0;
  longestStreak = 0;
  wordsList = {};
  resultsList = {};
  currentAttemptsList = {};
  system("clear");
  statistics();
}

void selectRandomWordGoal()
{
ifstream file;
  file.open(allowedText, ios::in);
  string q = "";
  int lines = 0;
//   Get file length
    while(getline(file,q))
    {
        lines++;
    }
    file.close();
    file.open(allowedText, ios::in);
  srand((unsigned) time(NULL));
  int random = 1 + rand() % 69;
  int counter = 0;
  string temp = "";
    while(counter != random && getline(file, temp))
    {
        ++counter;
        if(counter == random)
        {
            wordGoal = temp;
        }
    }
    file.close();
    return;
}

bool userEnter()
{
    ofstream myfile ("keyboardStatus.txt");
    myfile << "true" << endl;
    cout << "Enter guess: ";
    cin >> inputWord;
    bool accept = allowedWord();
    // If input is not an accepted word or is not the amount of letters long
    while(accept == false || inputWord.length() != letterWords)
    {
        cout << Up << "";
        cout << "Enter guess: ";
        cin >> inputWord;
        accept = allowedWord();
    }
    vector<string> tempList = {};
    bool correct = false;
    if (inputWord.compare(wordGoal) == 0)
    {
        // The word is correct
        for (int i = 0; i < letterWords; i++)
        {
            tempList.push_back("green");
            for (int g = 0; g < keyboard.size(); g++)
                {
                    if (keyboard[g] == inputWord[i])
                    {
                        isGreen.push_back(g);
                    }
                }
        }
        correct = true;
    }
    else{
        for (int i = 0; i< letterWords; i++)
        {
            // Checks if the letter is the correct index first
            if (wordGoal[i] == inputWord[i])
            {
                // Letter is in the correct spot
                tempList.push_back("green");
                for (int g = 0; g < keyboard.size(); g++)
                {
                    if (keyboard[g] == inputWord[i])
                    {
                        isGreen.push_back(g);
                    }
                }
            }
            // Checks if the letter is at least in the word but not in the same spot
            else if (wordGoal.find(inputWord[i]) <=letterWords && wordGoal.find(inputWord[i]) != i)
            {
                // Letter is in the word but not in the correct spot
                tempList.push_back("yellow");
                for (int y = 0; y < keyboard.size(); y++)
                {
                    if (keyboard[y] == inputWord[i])
                    {
                        isYellow.push_back(y);
                    }
                }
            }
            // Otherwise, letter is not in the wordGoal
            else{
                // Letter is not in the wordGoal
                tempList.push_back("gray");
                for (int e = 0; e < keyboard.size(); e++)
                {
                    if (keyboard[e] == inputWord[i])
                    {
                        isGray.push_back(e);
                    }
                }
            }
        }
    }
    for (int z = 0; z < 26; z++)
    {
        bool colorGreen = false;
        bool colorYellow = false;
        bool colorGray = false;
        for (int g = 0; g < isGreen.size(); g++)
        {
            if (z == isGreen[g])
            {
                colorGreen = true;
            }
        }
        for (int g = 0; g < isYellow.size(); g++)
        {
            if (isYellow[g] == z)
            {
                colorYellow = true;
            }
        }
        for (int g = 0; g < isGray.size(); g++)
        {
            if (isGray[g] == z)
            {
                colorGray = true;
            }
        }
        if(colorGreen == true)
        {
            myfile << "green" << endl;
        }else if (colorYellow == true)
        {
            myfile << "yellow" << endl;
        }
        else if (colorGray == true)
        {
            myfile << "gray" << endl;
        }else
        {
            myfile << "white" << endl;
        }
    }
    myfile.close();
    cout << Up << "";
    for (int i = 0; i < letterWords; i++)
    {
        if (tempList[i] == "green")
        {

            cout << Green << " --- ";
        }else if (tempList[i] == "yellow")
        {
            cout << Orange << " --- ";
        }
        else
        {
            cout << Gray << " --- ";
        }
    }
    cout << "\n";
    for (int i = 0; i < letterWords; i++)
    {
        if (tempList[i] == "green")
        {
            cout << Green << "| " << inputWord[i] << " |";
        }else if (tempList[i] == "yellow")
        {
            cout << Orange << "| " << inputWord[i] << " |";
        }
        else
        {
            cout << Gray << "| " << inputWord[i] << " |";
        }
    }
    cout << "\n";
    for (int i = 0; i < letterWords; i++)
    {
        if (tempList[i] == "green")
        {
            cout << Green << " --- ";
        }else if (tempList[i] == "yellow")
        {
            cout << Orange << " --- ";
        }
        else
        {
            cout << Gray << " --- ";
        }
    }
    cout << Reset << endl;
    return correct;
}

bool allowedWord()
{
    ifstream fileAllowed;
    fileAllowed.open(allowedText, ios::in);
    bool tempBool = false;
    string temp = "";
    while (getline(fileAllowed, temp)) {
      // Word is found at the line
      size_t pos = temp.find(inputWord);
      if (pos != string::npos)
      {
        tempBool = true;
      }
    }
    fileAllowed.close();
    ifstream fileWords;
    fileWords.open(isWord, ios::in);
    bool tempBoolTwo = false;
    while (getline(fileWords,temp))
    {
      size_t pos = temp.find(inputWord);
      if (pos != string::npos)
      {
        tempBool = true;
      }
    }
    if (tempBool == true || tempBoolTwo == true)
    {
        return true;
    }
    return false;
}

void calculateAverageAttempts()
{
    if (timesPlayed != 0)
    averageAttempts = (double)totalAttempts / timesPlayed;
    return;
}

void calculateWinPercentage()
{
    if (timesPlayed != 0)
    {
        winPercentage = (double)totalWins / timesPlayed *100;
    }
    return;
}