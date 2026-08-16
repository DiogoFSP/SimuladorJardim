#ifndef UTILIDADES_H
#define UTILIDADES_H
#include <random>
#include <string>

using namespace std;
class Utilidades{
    static mt19937 rng;
public:
    static int obterValorAleatorio(int min, int max){
        uniform_int_distribution<int> distribution =
                uniform_int_distribution<int>(min, max);
        return distribution(rng);
    }

    int separarSegmentos(const std::string& linha, std::string* segmentos, int maxSegmentos) {
        int count = 0;
        std::string atual;

        for (size_t i = 0; i < linha.size(); i++) {
            if (linha[i] == ' ') {
                if (!atual.empty()) {
                    if (count < maxSegmentos) {
                        segmentos[count++] = atual;
                    }
                    atual.clear();
                }
            } else {
                atual.push_back(linha[i]);
            }
        }

        if (!atual.empty() && count < maxSegmentos) {
            segmentos[count++] = atual;
        }

        return count;
    }

    static bool soDigitos(const std::string& s) {
        if (s.empty()) return false;
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] < '0' || s[i] > '9') return false;
        }
        return true;
    }
};

#endif