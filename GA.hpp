#include <iostream>
#include <vector>
#include <string>

namespace GA {
    typedef std::vector<std::string> population;

    void run(std::string target_, size_t populationSize_, size_t mutationRate_);

    std::string getTarget();
    size_t getPopulationSize();
    size_t getMutationRate();

    bool getReachedTarget();

    char getRandomChar();
    std::string getRandomGuy();
    population getInitialPopulation();
    int fitness(std::string guy);
    std::pair<std::string, std::string> selection(population p);
    population crossover(std::pair<std::string, std::string> maBois);
    void mutate(std::string &guy);

}