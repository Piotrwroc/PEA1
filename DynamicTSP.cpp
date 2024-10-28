#include "DynamicTSP.h"
#include <climits>
#include <algorithm>

using namespace std;

void DynamicTSP::start(int& path_length,int*& path, std::chrono::duration<double>& execution_time)
{
    dp[1][0] = 0; // Inicjalizacja: koszt dla stanu odwiedzającego tylko wierzchołek początkowy wynosi 0

    auto begin = std::chrono::high_resolution_clock::now();

    // Główna pętla obliczająca minimalne koszty przeglądu wszystkich masek reprezentujących zestawy odwiedzonych wierzchołków 
    for (int mask = 1; mask < (1 << vertex); mask += 2) // mask += 2, ponieważ maska powinna zawierać wierzchołek startowy (bit 1)
    {
        for (int i = 1; i < vertex; i++) // Iterujemy po wszystkich wierzchołkach końcowych
        {
            if (mask & (1 << i)) { // Sprawdzamy, czy `i` jest częścią aktualnej maski
                for (int j = 0; j < vertex; j++)
                {
                    // Sprawdzamy, czy 'j' jest częścią maski, jednocześnie będąc nie równe 'i' oraz czy mamy wcześniej obliczony koszt dla maski bez `i`
                    if (mask & (1 << j) && i != j && dp[mask ^ (1 << i)][j] != INT_MAX)
                    {
                        int new_cost = dp[mask ^ (1 << i)][j] + tab[j][i]; // Obliczamy nowy koszt dla trasy kończącej się w `i` po `j`
                        if (new_cost < dp[mask][i])
                        {
                            dp[mask][i] = new_cost; // Aktualizujemy minimalny koszt dla tego stanu
                            parent[mask][i] = j; // Zapisujemy `j` jako rodzica `i`, aby śledzić optymalną ścieżkę
                        }
                    }
                }
            }
        }
    }

    path_length = INT_MAX;
    int last_vertex = -1;

    // Ustalamy minimalny koszt powrotu do wierzchołka startowego
    for (int i = 1; i < vertex; i++)
    {
        int cost = dp[(1 << vertex) - 1][i] + tab[i][0]; // Obliczamy całkowity koszt, dodając koszt powrotu z `i` do 0
        if (cost < path_length)
        {
            path_length = cost; // Zapisujemy najmniejszy koszt
            last_vertex = i; // Zapamiętujemy ostatni wierzchołek w ścieżce
        }
    }

    // Tworzenie optymalnej ścieżki
    path = new int[vertex + 1];
    int mask = (1 << vertex) - 1;

    // Odtwarzanie ścieżki w odwrotnej kolejności
    for (int i = vertex - 1; i >= 0; --i)
    {
        path[i] = last_vertex;
        int temp = last_vertex;
        last_vertex = parent[mask][last_vertex]; // Śledzimy rodzica wierzchołka
        mask ^= (1 << temp); // Usuwamy `temp` z maski
    }
    path[vertex] = path[0]; // Dodajemy powrót do punktu początkowego

    auto end = std::chrono::high_resolution_clock::now();
    execution_time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin); 
}
