#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <climits>
#include <chrono>

class BruteForce
{
    int** tab; // Macierz wag
    int vertex; // Liczba wierzcho³ków
    int min_result; // Minimalny koszt

public:
    BruteForce(int** t, int v) : tab(t), vertex(v), min_result(INT_MAX) {}
    void start(int& path_length, int*& path, std::chrono::duration<double>& execution_time);

private:
    void path_permutations(int* path, int vertex, int* word, int** tab, int poz = 0);
    int calculate_weight(int vertex, int** tab, int* path);
};

#endif // BRUTEFORCE_H
