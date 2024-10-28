#include "DynamicTSP.h"
#include <climits>
#include <algorithm>

using namespace std;

void DynamicTSP::start(int& path_length,int*& path, std::chrono::duration<double>& execution_time)
{
    dp[1][0] = 0; // Inicjalizacja: koszt dla stanu odwiedzaj�cego tylko wierzcho�ek pocz�tkowy wynosi 0

    auto begin = std::chrono::high_resolution_clock::now();

    // G��wna p�tla obliczaj�ca minimalne koszty przegl�damy wszystkie maski reprezentuj�ce zestawy odwiedzonych wierzcho�k�w (odwiedzamy tylko wierzcho�ki startuj�ce od 1)
    for (int mask = 1; mask < (1 << vertex); mask += 2) // mask += 2, poniewa� maska powinna zawiera� wierzcho�ek startowy (bit 1)
    {
        for (int i = 1; i < vertex; i++) // Przesuwamy si� po wszystkich wierzcho�kach ko�cowych
        {
            if (mask & (1 << i)) { // Sprawdzamy, czy `i` jest cz�ci� aktualnej maski
                for (int j = 0; j < vertex; j++)
                {
                    // Sprawdzamy, czy 'j' jest cz�ci� maski, jednocze�nie b�d�c nie r�wne 'i' oraz czy mamy wcze�niej obliczony koszt dla maski bez `i`
                    if (mask & (1 << j) && i != j && dp[mask ^ (1 << i)][j] != INT_MAX)
                    {
                        int new_cost = dp[mask ^ (1 << i)][j] + tab[j][i]; // Obliczamy nowy koszt dla trasy ko�cz�cej si� w `i` po `j`
                        if (new_cost < dp[mask][i])
                        {
                            dp[mask][i] = new_cost; // Aktualizujemy minimalny koszt dla tego stanu
                            parent[mask][i] = j; // Zapisujemy `j` jako rodzica `i`, aby �ledzi� optymaln� �cie�k�
                        }
                    }
                }
            }
        }
    }

    path_length = INT_MAX;
    int last_vertex = -1;

    // Ustalamy minimalny koszt powrotu do wierzcho�ka startowego
    for (int i = 1; i < vertex; i++)
    {
        int cost = dp[(1 << vertex) - 1][i] + tab[i][0]; // Obliczamy ca�kowity koszt, dodaj�c koszt powrotu z `i` do 0
        if (cost < path_length)
        {
            path_length = cost; // Zapisujemy najmniejszy koszt
            last_vertex = i; // Zapami�tujemy ostatni wierzcho�ek w �cie�ce
        }
    }

    // Tworzenie optymalnej �cie�ki
    path = new int[vertex + 1];
    int mask = (1 << vertex) - 1;

    // Odtwarzanie �cie�ki w odwrotnej kolejno�ci
    for (int i = vertex - 1; i >= 0; --i)
    {
        path[i] = last_vertex;
        int temp = last_vertex;
        last_vertex = parent[mask][last_vertex]; // �ledzimy rodzica wierzcho�ka
        mask ^= (1 << temp); // Usuwamy `temp` z maski, by kontynuowa� wstecz
    }
    path[vertex] = path[0]; // Dodajemy powr�t do punktu pocz�tkowego

    auto end = std::chrono::high_resolution_clock::now();
    execution_time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin); 
}
