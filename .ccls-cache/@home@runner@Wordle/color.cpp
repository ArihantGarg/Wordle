#include <iostream>

// ANSI escape codes for text color
#define RESET   "\033[0m"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"      
#define BLUE    "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"      

int main() {
    std::cout << RED << "This is red text!" << RESET << std::endl;
    std::cout << GREEN << "This is green text!" << RESET << std::endl;
    std::cout << BLUE << "This is blue text!" << RESET << std::endl;
    std::cout << YELLOW << "This is yellow text!" << RESET << std::endl;
    std::cout << MAGENTA << "This is magenta text!" << RESET << std::endl;
    std::cout << CYAN << "This is cyan text!" << RESET << std::endl;

    return 0;
}