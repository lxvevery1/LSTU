#include <algorithm>
#include <cmath>
#include <random>
#include <vector>

class KohonenNeuron {
  private:
    std::vector<double> weights; // Вектор весов нейрона
    double fatigue; // Параметр усталости нейрона

  public:
    // Конструктор: инициализация весов случайными значениями и усталости
    KohonenNeuron(int inputSize) : fatigue(0.0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(0.0, 1.0);

        weights.resize(inputSize);
        for (auto& w : weights) {
            w = dist(gen); // Случайное значение от 0 до 1
        }
        normalizeWeights();
    }

    // Нормализация вектора весов
    void normalizeWeights() {
        double norm = std::sqrt(std::inner_product(
            weights.begin(), weights.end(), weights.begin(), 0.0));
        if (norm > 0) {
            for (auto& w : weights) {
                w /= norm;
            }
        }
    }

    // Вычисление расстояния между входным вектором и весами (евклидово
    // расстояние)
    double computeDistance(const std::vector<double>& input) const {
        double distance = 0.0;
        for (size_t i = 0; i < input.size(); ++i) {
            distance += std::pow(input[i] - weights[i], 2);
        }
        return std::sqrt(distance);
    }

    // Обновление весов (правило "победитель забирает всё")
    void updateWeights(const std::vector<double>& input, double learningRate) {
        for (size_t i = 0; i < weights.size(); ++i) {
            weights[i] += learningRate * (input[i] - weights[i]);
        }
        normalizeWeights(); // Нормализация после обновления
    }

    // Утомляемость: увеличивает усталость нейрона
    void increaseFatigue(double value) { fatigue += value; }

    // Снижение усталости (восстановление)
    void reduceFatigue(double value) {
        fatigue = std::max(0.0, fatigue - value);
    }

    // Получение усталости
    double getFatigue() const { return fatigue; }

    // Получение весов нейрона
    const std::vector<double>& getWeights() const { return weights; }
};
