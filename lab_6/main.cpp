#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

struct Product {
    int id;
    std::string name;
    int minQuantity;
    int maxQuantity;
    int weight;
};

class Individual {
public:
    std::vector<int> quantities;
    int fitness;

    Individual(int numProducts) {
        quantities.resize(numProducts);
    }

    void calculateFitness(int weightLimit, const std::vector<Product>& products) {
        int totalWeight = 0;
        fitness = 0;
        for (size_t i = 0; i < quantities.size(); ++i) {
            totalWeight += quantities[i] * products[i].weight;
            fitness += quantities[i]; // Goal is to maximize quantities
        }
        if (totalWeight > weightLimit) {
            fitness = 0; // Penalize if over the weight limit
        }
    }
};

void initializePopulation(std::vector<Individual>& population, const std::vector<Product>& products, int weightLimit) {
    for (auto& individual : population) {
        for (size_t i = 0; i < products.size(); ++i) {
            individual.quantities[i] = rand() % (products[i].maxQuantity + 1);
        }
        individual.calculateFitness(weightLimit, products);
    }
}

Individual crossover(const Individual& parent1, const Individual& parent2) {
    Individual child(parent1.quantities.size());
    for (size_t i = 0; i < parent1.quantities.size(); ++i) {
        child.quantities[i] = (rand() % 2) ? parent1.quantities[i] : parent2.quantities[i];
    }
    return child;
}

void mutate(Individual& individual, const std::vector<Product>& products) {
    size_t index = rand() % products.size();
    individual.quantities[index] = rand() % (products[index].maxQuantity + 1);
}

void geneticAlgorithm(const std::vector<Product>& products, int weightLimit, int populationSize, int generations) {
    std::vector<Individual> population(populationSize, Individual(products.size()));
    initializePopulation(population, products, weightLimit);

    for (int generation = 0; generation < generations; ++generation) {
        std::sort(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
            return a.fitness > b.fitness;
        });

        std::vector<Individual> newPopulation;
        for (int i = 0; i < populationSize / 2; ++i) {
            Individual child = crossover(population[i], population[i + 1]);
            mutate(child, products);
            child.calculateFitness(weightLimit, products);
            newPopulation.push_back(child);
        }
        population = newPopulation;
    }

    std::cout << "Лучшее решение найдено:\n";
    for (size_t i = 0; i < population[0].quantities.size(); ++i) {
        std::cout << products[i].name << ": " << population[0].quantities[i] << "\n";
    }
}

int main() {
    std::srand(std::time(0));

    std::vector<Product> products = {
        {1, "Продукт 1", 0, 10, 2},
        {2, "Продукт 2", 0, 10, 3},
        // Добавьте остальные 48 продуктов
        {50, "Продукт 50", 0, 10, 1}
    };

    int weightLimit;
    std::cout << "Введите грузоподъемность автомобиля: ";
    std::cin >> weightLimit;

    geneticAlgorithm(products, weightLimit, 100, 1000);

    return 0;
}
