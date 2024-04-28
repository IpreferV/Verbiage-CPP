#include <iostream>

class Vanity {
    public:
        std::string screen_clear = "\033[H\033[2J";
        std::string text_reset = "\u001B[0m";
        std::string text_green = "\u001B[32m";
        std::string text_blue = "\u001B[34m";
        std::string text_yellow = "\u001B[35m";
        std::string text_cyan = "\u001B[36m";
};
Vanity vanity;
void welcome_screen() {
    std::cout << vanity.screen_clear;

    std::cout << "Welcome to " << vanity.text_cyan << "Verbiage" << vanity.text_reset << "!" << std::endl;
}
void main_menu() {
    std::cout << vanity.text_blue << "\n1. Report a Bug" << vanity.text_green << "\n2. See Existing Bugs" << vanity.text_yellow << "\n3. Manage Bugs" << vanity.text_reset << std::endl;

    int choice = 0;
    std::cout << "Select an Operation:\n-> ";
    std::cin >> choice;

    if (choice == 1) {

    }
    else if (choice == 2) {

    }
    else if (choice == 3) {

    }
}
int main() {
    welcome_screen();
    main_menu();

    return 0;
}