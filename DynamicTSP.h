#ifndef DYNAMICTSP_H
#define DYNAMICTSP_H

#include <vector>
#include <chrono>

class DynamicTSP 
{
    int** tab; // Macierz wag
    int vertex; // Liczba wierzcho³ków
    std::vector<std::vector<int>> dp; // Tablica DP
    std::vector<std::vector<int>> parent; // Tablica do œledzenia œcie¿ki

public:
    DynamicTSP(int** t, int v) : tab(t), vertex(v), dp(1 << v, std::vector<int>(v, INT_MAX)), parent(1 << v, std::vector<int>(v, -1)) {}
    void start(int& path_length, int*& path, std::chrono::duration<double>& execution_time);
};

#endif // DYNAMICTSP_H
