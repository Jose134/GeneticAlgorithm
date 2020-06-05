#include <iostream>
#include <cstdlib>
#include <ctime>

#include "GA.hpp"

#define OPTION_SET_TARGET 0
#define OPTION_SET_POPULATION_SIZE 1
#define OPTION_SET_MUTATION_RATE 2
#define OPTION_RUN 3
#define OPTION_EXIT 4

int main () {
    srand(time(NULL));

    int option = 0;

    char target[250] = "Hello World!";
    size_t populationSize = 100;
    size_t mutationRate = 10;

    do {
        std::cout << "0. Set target (current \"" << target << "\")"               << std::endl;
        std::cout << "1. Set population size (current " << populationSize << ")"  << std::endl;
        std::cout << "2. Set mutation rate (current " << mutationRate << "%)"     << std::endl;
        std::cout << "3. Run"                                                     << std::endl;
        std::cout << "4. Exit"                                                    << std::endl;

        std::cin >> option;

        switch (option) {
            case OPTION_SET_TARGET:
                std::cin.get();
                std::cin.getline(target, 250);
                break;

            case OPTION_SET_POPULATION_SIZE:
                std::cin >> populationSize;
                break;

            case OPTION_SET_MUTATION_RATE:
                std::cin >> mutationRate;
                break;

            case OPTION_RUN:
                GA::run(target, populationSize, mutationRate);
                break;

            case OPTION_EXIT:
                break;

            default:
                std::cout << "ERROR: Not a valid option!" << std::endl;
        }
    } while(option != OPTION_EXIT);

    return 0;
}