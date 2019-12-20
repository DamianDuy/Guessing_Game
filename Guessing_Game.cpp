#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <cmath>
class guessingGame
{
    public:

    std::string chosenSymbol;
    std::string userInput;
    double money;
    double bet;

    void loadTheSymbol()//Loads the random symbol from the file
    {
      srand(time(NULL));
      std::string line;
      int lineNumber = 1;
      int randomNumber = (std::rand() % 5) + 1;
      std::fstream symbolsFile;
      symbolsFile.open("symbols.txt");
      if (!symbolsFile.good())
      {
        std::cout << "Could not open the file. Program will be terminated. Check if the file" << std::endl << "\"symbols.txt\" is in the folder.";
        exit(EXIT_FAILURE);
      }
      while(getline(symbolsFile,line))
      {
         if (lineNumber == randomNumber)
         {
            chosenSymbol = line;
            break;
         }
        lineNumber++;
      }
    symbolsFile.close();
    }
    void receiveInput()//Prompts user to enter his guess and the amount of many he has/wants to bet
    {
    std::cout << std::endl;
    std::cout << "How much money do you want to bet?" << std::endl;
    std::cin >> bet;
    if (std::cin.fail())
    {
      std::cout << "Invalid input. Program will be terminated.";
      exit (EXIT_FAILURE);
    }
    while (bet < 0)
    {
      std::cout << "You can't bet less money than zero! Try again: " << std::endl;
      std::cin >> bet;
      if (std::cin.fail())
       {
        std::cout << "Invalid input. Program will be terminated.";
        exit (EXIT_FAILURE);
       }
    }
     while (bet > money)
    {
       std::cout << "You can't bet more money than you have! Try again: " << std::endl;
       std::cin >> bet;
       if (std::cin.fail())
       {
        std::cout << "Invalid input. Program will be terminated.";
        exit (EXIT_FAILURE);
       }
    }
    std::cout << "Choose the symbol: ";
    std::cin.clear();
    std::cin.ignore(1000,'\n');
    getline(std::cin, userInput);
    while (userInput != "-.-" && userInput != "@.@" && userInput != "[*]" && userInput != "^J^" && userInput != "o~~")
    {
        std::cout << "You chose non existent symbol. Try again." << std::endl;
        std::cout << "Choose the symbol: ";
        getline (std::cin, userInput);
    }
    }
    void showResult()//Shows user the result and the amount of money he has now
    {
        if (chosenSymbol == userInput)
        {
            money += 2*bet;
            std::cout << "You guessed right! You now have " << money << " money." << std::endl;
        }
        else
        {
            money -= bet;
            std::cout << "You guessed wrong! You now have " << money << " money." << std::endl;
            std::cout << "The correct symbol was " << chosenSymbol << "." << std::endl;
        }
    }
    void menu()//Shows the menu
    {

    std::cout << std::endl;
    std::cout << "0) Exit" << std::endl
              << "1) Play" << std::endl;
    std::cout << std::endl;
    }
};
int main()
{
 std::cout << "Welcome to the Guessing Game!" << std::endl;
 sleep(2);
 std::cout << "You'll bet money on one of the following symbols: " << std::endl;
 sleep(2);
 std::cout << "-.-" << std::endl;
 sleep(1);
 std::cout << "@.@" << std::endl;
 sleep(1);
 std::cout << "[*]" << std::endl;
 sleep(1);
 std::cout << "^J^" << std::endl;
 sleep(1);
 std::cout << "o~~" << std::endl;
 sleep(1);
 std::cout << "Next, the computer will draw one of the symbols randomly." << std::endl;
 sleep(2);
 std::cout << "If you chose the same symbol you'll get double of the money you bet." << std::endl;
 std::cout << "In other case you'll lose the money you bet." << std::endl;
 sleep(2);
 std::cout << "Pretty simple, right? Let us begin!" << std::endl;
 sleep(2);
 guessingGame game;
 int choice = 0;
 std::cout << "How much money do you have?" << std::endl;
 std::cin >> game.money;
 if (std::cin.fail())
 {
  std::cout << "Invalid input. Program will be terminated.";
  exit (EXIT_FAILURE);
 }
while (game.money <= 0)
{
  std::cout << "You must have more money than 0 to play. Try again: " << std::endl;
  std::cin >> game.money;
  if (std::cin.fail())
    {
      std::cout << "Invalid input. Program will be terminated.";
      exit (EXIT_FAILURE);
    }
}
    game.menu();
    std::cin >> choice;
 if (std::cin.fail())
    {
       std::cout << "Invalid input. Program will be terminated.";
       exit (EXIT_FAILURE);
    }
 while (choice != 0 && choice != 1)
 {
    std::cout << "No such choice in the menu. Try again." << std::endl;
    std::cin >> choice;
    if (std::cin.fail())
     {
       std::cout << "Invalid input. Program will be terminated.";
       exit (EXIT_FAILURE);
     }
 }
 while (choice == 1)
  {
    game.loadTheSymbol();
    game.receiveInput();
    game.showResult();
    if (game.money <= 0) break;
    game.menu();
    std::cin >> choice;
    if (std::cin.fail())
    {
       std::cout << "Invalid input. Program will be terminated.";
       exit (EXIT_FAILURE);
    }
    while (choice != 0 && choice != 1)
    {
      std::cout << "No such choice in the menu. Try again." << std::endl;
      std::cin >> choice;
      if (std::cin.fail())
      {
         std::cout << "Invalid input. Program will be terminated.";
         exit (EXIT_FAILURE);
      }
    }
 }
 sleep (2);
 std::cout << std::endl;
 std::cout << "Thank you for playing!";
 if (game.money >= 0) std::cout << " You ended up with " << game.money << " money.";
 else std::cout << "You ended up with " << abs(game.money) << " debt."; //A feature can be started by making it possible for user to bet more money then they have
 return 0;
}


