#include <unistd.h>

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

class Messages {
 public:
  void menu()  // Shows the menu
  {
    std::cout << "0) Exit" << std::endl << "1) Play" << std::endl;
  }
  void beginMessage() {
    std::cout << "Welcome to the Guessing Game!" << std::endl;
    sleep(2);
    std::cout << "You'll bet money on one of the following symbols: "
              << std::endl;
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
    std::cout << "Next, the computer will draw one of the symbols randomly."
              << std::endl;
    sleep(2);
    std::cout << "If you chose the same symbol you'll get double of the money "
                 "you bet."
              << std::endl;
    std::cout << "In other case you'll lose the money you bet." << std::endl;
    sleep(2);
    std::cout << "Pretty simple, right? Let us begin!" << std::endl;
    sleep(2);
  }
  void errorMessage() {
    std::cout << "Invalid input. Program will be terminated.\n";
    exit(EXIT_FAILURE);
  }
  int menuChoice() {
    int choice = 0;
    do {
      std::cin >> choice;
      if (std::cin.fail()) {
        errorMessage();
      }
      if (choice != 0 && choice != 1) {
        std::cout << "No such choice in the menu. Try again." << std::endl;
      }
    } while (choice != 0 && choice != 1);
    return choice;
  }
  double moneyChoice() {
    double money = 0;
    do {
      std::cout << "How much money do you have?" << std::endl;
      std::cin >> money;
      if (std::cin.fail()) {
        errorMessage();
      }
      if (money <= 0) {
        std::cout << "You must have more money than 0 to play. Try again: "
                  << std::endl;
      }
    } while (money <= 0);
    return money;
  }
};

class guessingGame {
 public:
  guessingGame() {
    symbolsFile.open("symbols.txt");
    if (!symbolsFile.good()) {
      std::cout << "Could not open the file. Program will be terminated. Check "
                   "if the file"
                << std::endl
                << "\"symbols.txt\" is in the folder.\n";
      exit(EXIT_FAILURE);
    }
    srand(time(NULL));
  }
  ~guessingGame() { symbolsFile.close(); }
  double getMoney() { return money; }
  void setMoney(double _money) { money = _money; }
  void loadSymbol()  // Loads the random symbol from the file
  {
    std::string line;
    int lineNumber = 1;
    int randomNumber = (std::rand() % 5) + 1;
    while (getline(symbolsFile, line)) {
      if (lineNumber == randomNumber) {
        chosenSymbol = line;
        break;
      }
      lineNumber++;
    }
    symbolsFile.clear();
    symbolsFile.seekg(0);
  }
  void receiveInput()  // Prompts user to enter his guess and the amount of many
                       // // he has/wants to bet
  {
    Messages message;
    std::cout << "How much money do you want to bet?" << std::endl;
    do {
      std::cin >> bet;
      if (std::cin.fail()) {
        message.errorMessage();
      }
      if (bet <= 0 || bet > money) {
        std::cout << "Inappropriate amount (has to be > 0 and <= the money you "
                     "own). Try again: "
                  << std::endl;
      }

    } while (bet <= 0 || bet > money);
    std::cout << "Choose the symbol: ";
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    getline(std::cin, userInput);
    while (userInput != "-.-" && userInput != "@.@" && userInput != "[*]" &&
           userInput != "^J^" && userInput != "o~~") {
      std::cout << "You chose non existent symbol. Try again." << std::endl;
      std::cout << "Choose the symbol: ";
      getline(std::cin, userInput);
    }
  }
  void setResult()  // Shows user the result and the amount of money he has now
  {
    if (chosenSymbol == userInput) {
      money += 2 * bet;
      std::cout << "You guessed right! You now have " << money << " money."
                << std::endl;
    } else {
      money -= bet;
      std::cout << "You guessed wrong! You now have " << money << " money."
                << std::endl;
      std::cout << "The correct symbol was " << chosenSymbol << "."
                << std::endl;
    }
  }
  void showResult() {
    std::cout << "Thank you for playing!";
    if (this->getMoney() >= 0)
      std::cout << " You ended up with " << this->getMoney() << " money.\n";
    else
      std::cout
          << "You ended up with " << abs(this->getMoney())
          << " debt.\n";  // A feature can be started by making it possible
                          // for user to bet more money then they have
  }

 private:
  std::string chosenSymbol;
  std::string userInput;
  double money;
  double bet;
  std::fstream symbolsFile;
};

int main() {
  int choice = 0;
  double money = 0;
  Messages message;
  guessingGame game;
  message.beginMessage();
  money = message.moneyChoice();
  game.setMoney(money);
  message.menu();
  choice = message.menuChoice();
  while (choice == 1) {
    game.loadSymbol();
    game.receiveInput();
    game.setResult();
    if (game.getMoney() <= 0) break;
    message.menu();
    choice = message.menuChoice();
  }
  game.showResult();
  return 0;
}
