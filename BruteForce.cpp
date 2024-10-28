#include "BruteForce.h"
#include <iostream>
#include <chrono>
#include <climits>

using namespace std;

void BruteForce::start(int& path_length, int*& path, std::chrono::duration<double>& execution_time)
{
    path = new int[vertex + 1]; // Alokacja pamiêci dla œcie¿ki
    int* word = new int[vertex]; // Tablica do permutacji wierzcho³ków

    // Inicjalizacja tablicy 'word'
    for (int i = 0; i < vertex; i++)
    {
        word[i] = i;
    }

    auto begin = chrono::high_resolution_clock::now();
    path_permutations(path, vertex, word, tab);
    auto end = chrono::high_resolution_clock::now();
    execution_time = chrono::duration_cast<chrono::microseconds>(end - begin);

    path_length = min_result; // Ustawienie d³ugoœci œcie¿ki na minimalny koszt

    delete[] word; // Zwalnianie pamiêci
}

// Obliczenie kosztu œcie¿ki
int BruteForce::calculate_weight(int vertex, int** tab, int* path)
{
    int result = 0;
    int start_vertex = path[0];

    // Sumowanie kosztów przejœæ miêdzy wierzcho³kami
    for (int i = 0; i < vertex - 1; i++)
    {
        result += tab[path[i]][path[i + 1]];
    }

    result += tab[path[vertex - 1]][start_vertex]; // Dodanie kosztu powrotu
    return result; // Zwrócenie ca³kowitego kosztu
}

// Generowanie permutacji wierzcho³ków
void BruteForce::path_permutations(int* path, int vertex, int* word, int** tab, int poz)
{
    if (poz == vertex) // Jeœli osi¹gniêto pe³n¹ permutacjê
    {
        int result = calculate_weight(vertex, tab, word); // Obliczanie kosztu
        if (result < min_result) // Sprawdzenie, czy jest lepszy wynik
        {
            min_result = result; // Aktualizacja minimalnego kosztu
            for (int j = 0; j < vertex; j++)
            {
                path[j] = word[j]; // Zapisanie najlepszej œcie¿ki
            }
            path[vertex] = word[0]; // Ustawienie powrotu do startu
        }
    }
    else // Generowanie kolejnych permutacji
    {
        for (int i = poz; i < vertex; i++)
        {
            swap(word[i], word[poz]); // Zamiana wierzcho³ków
            path_permutations(path, vertex, word, tab, poz + 1); // Rekurencyjne wywo³anie
            swap(word[i], word[poz]); // Przywrócenie stanu
        }
    }
}
