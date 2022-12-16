#include<iostream>
#include<string>
#include<time.h>
using namespace std;

void menu(string, bool, bool); //menu representation
string random_word(string[]); //function to generate random words
void draw_hangman(int); //function for drawing hangman
bool print_guesses(string, string); //function to print correct guesses
void start_game(string[]); //starting game
void game_rules(); //rules to play game
void Display_Words(string[]); //function to print available words
void go_back(); //for going back to main screen

int main()
{
    //An array of strings
    string words[] = { "CAT","DOG","NUST","ASHMA","HANGMAN","BAT" };

    //looping until user selects exit
    for (int i = 0;i != 4;)
    {
        system("Color DE"); //changing color of background and text

        cout << "\n\t\t\t\t\t+-------------------------------+" << endl;
        cout << "\t\t\t\t\t\tWelcome to HANGMAN" << endl << endl;
        cout << "\t\t\t\t\t1-Start Game\t2-Read Rules" << endl;
        cout << "\t\t\t\t\t3-Show Words\t4-Exit" << endl;
        cout << "\t\t\t\t\t+-------------------------------+" << endl;

        cout << "Select: ";
        cin >> i;

        switch (i)
        {

        case 1: start_game(words); go_back(); continue;

        case 2: game_rules(); go_back(); continue;

        case 3: Display_Words(words); go_back(); continue;

        case 4: cout << "\nThanks For Playing.."; exit(0);

        }
    }

    return 0;
}

string random_word(string str[])
{
    //generating random words:

    srand(time(NULL)); //starting the time seed

    return str[rand() % 6];
}

void menu(string text, bool top = true, bool bottom = true)
{
    bool centre = true;

    if (top == true) //printing the top content if top is TRUE
    {
        cout << "x------------------------------x" << endl;
        cout << "|";
    }

    else
        cout << "|";
  
    for (int i = text.length();i < 30;i++) //printing the text in-between
    {
        //managing spaces:

        if (centre == true)
            text = " " + text;
   
        else
            text = text + " ";

        centre = !centre; //changing centre to its inverse
    }

    cout << text;
  
    if (bottom == true) //printing the bottom content if bottom is TRUE
    {
        cout << "|" << endl;
        cout << "x------------------------------x" << endl;
    }

    else
        cout << "|" << endl;
}

void draw_hangman(int count) //drawing hangman based on wrong guesses
{
    if (count == 0) //if 0 wrong guess, no hangman is drawn
        menu(" ", false, false);

    //Based on number of wrong guesses, different parts of hangman are drawn:

    if (count >= 1) 
        menu("|", false, false);

    if (count >= 2)
        menu("|", false, false);

    if (count >= 3)
        menu("O", false, false);

    if (count >= 4)
        menu("/|\\", false, false);

    if (count >= 6)
        menu("|", false, false);

    if (count == 7)
        menu("/ \\", false, false);
}

bool print_guesses(string word, string guess)
{
    bool flag = 1;
    string str = " ";

    for (int i = 0;i != word.length();i++)
    {
        if (guess.find(word[i]) == string::npos)
        {
            str += "_   "; //adding placeholders if guess is wrong
            flag = 0;
        }

        else //adding the correct guessed alphabet in the string
        {
            str += word[i];
            str += " ";
        }
    }

    menu(str, false, true); //printing string
    return flag;
}

void start_game(string words[])
{
    system("Color 4F");
    system("CLS");

    srand(time(NULL)); //starting the time seed

    cout << "Starting..." << endl << endl;

    //Variables used in the game

    string word, random, guess;
    char alphabet;
    bool win;
    int error_count = 0, hint=2;

    //Words used for guessing in the game
    random = random_word(words);

    for (int i = 0;i <= 10;i++)
    {

        menu("WORLD OF HANGMAN", true, true); //printing message with top and bottom borders
        draw_hangman(error_count); //drawing hangman
        menu("Guess the Word", true, true); //printing message with top and bottom borders
        win = print_guesses(random, guess);

        if (win || error_count == 7) //if user wins or error_count reaches its limit i.e 7
        {
            break;
        }

        cout << "\nAlphabet (Press 'h' For HINT): ";
        cin >> alphabet;

        if (alphabet == 'h' && hint!=0) //To Avail HINT
        {
            cout << "The Hidden Word Contains: " << random[rand() % random.length()] << endl << endl;
            hint--;
            i--; //hints shouldn't decrease tries
            system("pause");
        }

        else
        {
            if (random.find(alphabet) == string::npos) //if wrong letter is guessed
            {
                error_count++;
            }

            //checks to see if the letter is already guessed:

            else
            {
                if (guess.find(alphabet) == string::npos)
                {
                    guess += alphabet; //adding into the string
                }

                else
                {
                    cout << "\nSorry. You Already Guessed the Letter " << alphabet << endl << endl;
                    system("Pause");
                }
            }
        }
        if (i <= 10)
            system("CLS");
    }

    if (win)
        cout << "\nCongratulations!! You WIN!" << endl;
    else
        cout << "\nYou LOSE. The Word Was " << random << endl;
}

void Display_Words(string str[]) 
{
    system("CLS");

    cout << "\nAvailable Words Are:\n" << endl;

    //Displaying words stored in the string

    for (int i = 0;i < 6;i++)
    {
        cout << str[i] << endl;
    }
}

void game_rules()
{
    system("Color E4");
    system("CLS");

    //Printing Game Rules:

    cout << "\n\t\t\t+------------------------------------------------------+" << endl;
    cout << "\t\t\t\t\t   Rules of HANGMAN" << endl << endl;
    cout << "\t\t\t#1-Try to guess the word until the hangman is fully drawn." << endl;
    cout << "\t\t\t#2-You Can Only Use Upper-Case Alphabets" << endl;
    cout << "\t\t\t#3-You Can Press 'h' to get a hint." << endl;
    cout << "\t\t\t#4-You Can Use Hints Upto 2 Times in the Game" << endl;
    cout << "\n\t\t\t+------------------------------------------------------+" << endl;

}

void go_back()
{
    cout << "\n\nPress E to go back..." << endl;
    getchar();
    getchar();
    system("CLS");
}