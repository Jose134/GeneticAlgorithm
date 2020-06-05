#include "GA.hpp"

namespace GA {

    namespace {
            std::string validCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?_-%&+*1234567890 ";
            std::string target;
            size_t populationSize;
            int mutationRate;
            bool reachedTarget;
    }

    char getRandomChar () {
        return validCharacters[rand() % validCharacters.size()];
    }

    std::string getTarget() {
        return target;
    }

    size_t getpopulationSize() {
        return populationSize;
    }

    size_t getMutationRate () {
        return mutationRate;
    }

    bool getReachedTarget() {
        return reachedTarget;
    }

    std::string getRandomGuy () {
        std::string guy = target;

        for (int i = 0; i < guy.size(); i++) {
            guy[i] = getRandomChar();
        }

        return guy;        
    }

    population getInitialPopulation () {
        std::vector<std::string> v(populationSize);

        for (int i = 0; i < populationSize; i++) {
            v[i] = getRandomGuy();
        }

        return v;
    }

    int fitness (std::string guy) {
        int count = 0;
        int bonus = 0;
        bool prev = false;
        bool complete = true;
        
        for (int i = 0; i < target.size(); i++) {
            if (guy[i] == target[i]) {
                count++;

                if (prev) {
                    bonus++;
                }
                else {
                    prev = true;
                }
            }
            else {
                complete = false;
                prev = false;
            }
        }

        if (complete) {
            reachedTarget = true;
        }

        return count + bonus;
    }

    std::pair<std::string, std::string> selection(population p) {
        std::pair<std::string, std::string> maBois;

        if (fitness(p[1]) > fitness(p[0])) {
            maBois.first = p[1];
            maBois.second = p[0];
        }
        else {
            maBois.first = p[0];
            maBois.second = p[1];
        }

        for (int i = 2; i < p.size(); i++) {
            if (fitness(p[i]) > fitness(maBois.first)) {
                maBois.second = maBois.first;
                maBois.first = p[i];
            }
        }

        return maBois;
    }

    population crossover(std::pair<std::string, std::string> maBois) {
        population leNewGuys;
        
        for (int i = 0; i < populationSize; i++) {
            std::string str = target;

            int crossPoint = rand() % maBois.first.size();

            for (int j = 0; j < str.size(); j++) {
                if (j < crossPoint) {
                    str[j] = maBois.first[j];
                }
                else {
                    str[j] = maBois.second[j];
                }
            }

            if (rand() % mutationRate < 10) {
                mutate(str);
            }

            leNewGuys.push_back(str);
        }

        return leNewGuys;
    }

    void mutate(std::string &guy) {
        int charIndex = rand() % guy.size();
        guy[charIndex] = getRandomChar();
    }

    void run (std::string target_, size_t populationSize_, size_t mutationRate_) {
        reachedTarget = false;

        target = target_;
        populationSize = populationSize_;
        mutationRate = mutationRate_;


        population p = getInitialPopulation();

        int count = 0;

        bool print = false;

        do {
            
            std::cout << std::endl <<  "Generation: " << count << " " << p.size() << std::endl;
            
            //Prints current population
            if (print) {
                for (int i = 0; i < p.size(); i++) {
                    std::cout << p[i] << " " << std::endl;
                }
                std::cout << std::endl;
            }

            auto bestOnes = selection(p);
            std::cout << "First best: " << bestOnes.first << "      " << fitness(bestOnes.first) << std::endl;
            std::cout << "Second best: " << bestOnes.second << "     " << fitness(bestOnes.second) << std::endl;

            p = crossover(bestOnes);
            count++;

        } while (!reachedTarget);

    }

}