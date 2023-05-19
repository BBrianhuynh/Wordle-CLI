#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

#define Green "\033[32m"
#define Red "\033[31m"
#define Reset "\033[0m"
#define Orange "\u001b[38;5;216m"
#define Gray "\u001b[38;5;8m"
#define Up "\033[A"
#define White "\u001b[37m"
void printKeyboard();
void resetColorKeyboard();
void getColorKeyboard();

int main(int argc, char *argv[])
{
    system("clear");
    cout<<"Waiting for Wordle Game round to start"<< endl;
    for(;;)
    {
        printKeyboard();
    }
    return 0;
}

// Global variables
vector<string> qwertyKeyboard = {"Q","W","E","R","T","Y","W","I","O","P","A","S","D","F","G","H","J","K","L","Z","X","C","V","B","N","M"};
vector<string> colorKeyboard = {"white","white","white","white","white","white","white","white","white","white","white","white","white","white","white","white","white","white","white","white","white","white","white","white","white","white"};
string status = "false";

void printKeyboard()
{
    getColorKeyboard();
    if (status.find("false") == 0)
    {
        system("clear");
        cout << Reset;
        cout<<"Waiting for Wordle Game round to start"<< endl;
        return;
    }
    system("clear");
    // qwertyuiop printing top box
    for (int i = 0; i < 10; i++)
    {
        if (colorKeyboard[i] == "green")
        {
            cout << Green << " --- ";
        }else if (colorKeyboard[i] == "yellow")
        {
            cout << Orange << " --- ";
        }
        else if (colorKeyboard[i] == "white")
        {
            cout << White << " --- ";
        }
        else
        {
            cout << Gray << " --- ";
        }
    }
    cout << "\n";
    // qwertyuiop printing middle
    for (int i = 0; i < 10; i++)
    {
        if (colorKeyboard[i] == "green")
        {
            cout << Green << "| " << qwertyKeyboard[i] << " |";
        }else if (colorKeyboard[i] == "yellow")
        {
            cout << Orange << "| " << qwertyKeyboard[i] << " |";
        }
        else if (colorKeyboard[i] == "white")
        {
            cout << White << "| " << qwertyKeyboard[i] << " |";
        }
        else
        {
            cout << Gray << "| " << qwertyKeyboard[i] << " |";
        }
    }
    cout << "\n";
    // qwertyuiop printing bottom
    for (int i = 0; i < 10; i++)
    {
        if (colorKeyboard[i] == "green")
        {
            cout << Green << " --- ";
        }else if (colorKeyboard[i] == "yellow")
        {
            cout << Orange << " --- ";
        }
        else if (colorKeyboard[i] == "white")
        {
            cout << White << " --- ";
        }
        else
        {
            cout << Gray << " --- ";
        }
    }
    cout << "\n  ";
    // asdfghjkl printing top
    for (int i = 10; i < 19; i++)
    {
        if (colorKeyboard[i] == "green")
        {
            cout << Green << " --- ";
        }else if (colorKeyboard[i] == "yellow")
        {
            cout << Orange << " --- ";
        }
        else if (colorKeyboard[i] == "white")
        {
            cout << White << " --- ";
        }
        else
        {
            cout << Gray << " --- ";
        }
    }
    cout << "\n  ";
    // asdfghjkl printning middle
    for (int i = 10; i < 19; i++)
    {
        if (colorKeyboard[i] == "green")
        {
            cout << Green << "| " << qwertyKeyboard[i] << " |";
        }else if (colorKeyboard[i] == "yellow")
        {
            cout << Orange << "| " << qwertyKeyboard[i] << " |";
        }
        else if (colorKeyboard[i] == "white")
        {
            cout << White << "| " << qwertyKeyboard[i] << " |";
        }
        else
        {
            cout << Gray << "| " << qwertyKeyboard[i] << " |";
        }
    }
    cout << "\n  ";
    // asdfghjkl printing bottom
    for (int i = 10; i < 19; i++)
    {
        if (colorKeyboard[i] == "green")
        {
            cout << Green << " --- ";
        }else if (colorKeyboard[i] == "yellow")
        {
            cout << Orange << " --- ";
        }
        else if (colorKeyboard[i] == "white")
        {
            cout << White << " --- ";
        }
        else
        {
            cout << Gray << " --- ";
        }
    }
    cout << "\n        ";
    // zxcvbnm printing top
    for (int i = 19; i < 26; i++)
    {
        if (colorKeyboard[i] == "green")
        {
            cout << Green << " --- ";
        }else if (colorKeyboard[i] == "yellow")
        {
            cout << Orange << " --- ";
        }
        else if (colorKeyboard[i] == "white")
        {
            cout << White << " --- ";
        }
        else
        {
            cout << Gray << " --- ";
        }
    }
    cout << "\n        ";
    // zxcvbnm printing middle
    for (int i = 19; i < 26; i++)
    {
        if (colorKeyboard[i] == "green")
        {
            cout << Green << "| " << qwertyKeyboard[i] << " |";
        }else if (colorKeyboard[i] == "yellow")
        {
            cout << Orange << "| " << qwertyKeyboard[i] << " |";
        }
        else if (colorKeyboard[i] == "white")
        {
            cout << White << "| " << qwertyKeyboard[i] << " |";
        }
        else
        {
            cout << Gray << "| " << qwertyKeyboard[i] << " |";
        }
    }
    cout<<"\n        ";
    // zxcvbnm printing bottom
    for (int i = 19; i < 26; i++)
    {
        if (colorKeyboard[i] == "green")
        {
            cout << Green << " --- ";
        }else if (colorKeyboard[i] == "yellow")
        {
            cout << Orange << " --- ";
        }
        else if (colorKeyboard[i] == "white")
        {
            cout << White << " --- ";
        }
        else
        {
            cout << Gray << " --- ";
        }
    }
    cout << Reset << "\n";
}

void resetColorKeyboard()
{
    colorKeyboard = {"white","white","white","white","white","white","white","white","white","white","white","white","white","white",
"white","white","white","white","white","white","white","white","white","white","white","white"};
}

void getColorKeyboard()
{
  colorKeyboard = {};
  ifstream fileKeyboard;
  fileKeyboard.open("../wordle/keyboardStatus.txt", ios::in);
  int counter = 0;
  string temp = "";
  while (getline(fileKeyboard, temp)) {
    ++counter;
    if (counter == 1) {
      status = temp;
    }
    else{
        colorKeyboard.push_back(temp);
    }
  }
  fileKeyboard.close();
  return;
}