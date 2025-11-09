// Дана таблица, содержащая атрибуты объектов, описываемых парой признаков.
// Нанесите эти точки на плоскость и оцените количество кластеров. Проведите
// обучение СОК Кохонена с соответствующим количеством выходных нейронов по
// алгоритму "Победитель забирает всё".

// Для этого:
// 1) задайте случайным образом весовые коэффициенты каждого
// выходного нейрона и произведите нормировку векторов каждого нейрона;

// 2) проведите обучение (задайте константу обучения на 1 цикле в диапазоне от
// 0.3 до 0.7 и затем от цикла к циклу уменьшайте её значение);

// 3) реализуйте обучение СОК Кохонена с применением механизма утомляемости
// нейронов; сравните со временем обучения классического алгоритма «Победитель
// забирает всё»;

// 4) нанесите векторы весов выходных нейронов на плоскость с нормированными
// значениями объектов из обучающего множества;

// 5) предложите способ масштабирования вектора весов нейронов для того, чтобы
// он указывал в «центр» соответствующего кластера; нанесите масштабированные
// векторы весов нейронов на плоскость с исходными значениями из множества
// данных.

#include "./KohonenNeuron.cpp"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

#define MAX_LENGTH 2

std::vector<double> randomize_vector(std::vector<double> vector) {
    double r = 0;
    for (uint32_t i = 0; i < vector.capacity(); i++) {
        r = static_cast<double>(rand()) / static_cast<double>(RAND_MAX / 1);
        vector[i] = r;
    }
    return vector;
}

int main(void) {
    double learning_rate =
        static_cast<double>(rand() + 0.3) / static_cast<double>(RAND_MAX / 0.7);
    KohonenNeuron neuron(MAX_LENGTH);

    std::vector<double> neuron_vector(MAX_LENGTH);
    neuron_vector = randomize_vector(neuron_vector);

    double distance = neuron.computeDistance(neuron_vector);

    std::cout << "Initial distance: " << distance << '\n';
    std::vector<double> weights = neuron.getWeights();
    std::cout << "Old weights: ";
    for (double w : weights) {
        std::cout << w << " ";
    }
    std::cout << '\n';

    neuron.updateWeights(neuron_vector, learning_rate);

    weights = neuron.getWeights();
    std::cout << "Updated weights: ";
    for (double w : weights) {
        std::cout << w << " ";
    }
    std::cout << '\n';

    neuron.increaseFatigue(0.1);
    std::cout << "Neuron fatigue: " << neuron.getFatigue() << '\n';

    return 0;
}
