#include "DynamicTSP.h"
#include <climits>
#include <algorithm>

using namespace std;

void DynamicTSP::start(int& path_length,int*& path, std::chrono::duration<double>& execution_time)
{
    dp[1][0] = 0; // Inicjalizacja: koszt dla stanu odwiedzaj¹cego tylko wierzcho³ek pocz¹tkowy wynosi 0

    auto begin = std::chrono::high_resolution_clock::now();

    // G³ówna pêtla obliczaj¹ca minimalne koszty przegl¹damy wszystkie maski reprezentuj¹ce zestawy odwiedzonych wierzcho³ków (odwiedzamy tylko wierzcho³ki startuj¹ce od 1)
    for (int mask = 1; mask < (1 << vertex); mask += 2) // mask += 2, poniewa¿ maska powinna zawieraæ wierzcho³ek startowy (bit 1)
    {
        for (int i = 1; i < vertex; i++) // Przesuwamy siê po wszystkich wierzcho³kach koñcowych
        {
            if (mask & (1 << i)) { // Sprawdzamy, czy `i` jest czêœci¹ aktualnej maski
                for (int j = 0; j < vertex; j++)
                {
                    // Sprawdzamy, czy 'j' jest czêœci¹ maski, jednoczeœnie bêd¹c nie równe 'i' oraz czy mamy wczeœniej obliczony koszt dla maski bez `i`
                    if (mask & (1 << j) && i != j && dp[mask ^ (1 << i)][j] != INT_MAX)
                    {
                        int new_cost = dp[mask ^ (1 << i)][j] + tab[j][i]; // Obliczamy nowy koszt dla trasy koñcz¹cej siê w `i` po `j`
                        if (new_cost < dp[mask][i])
                        {
                            dp[mask][i] = new_cost; // Aktualizujemy minimalny koszt dla tego stanu
                            parent[mask][i] = j; // Zapisujemy `j` jako rodzica `i`, aby œledziæ optymaln¹ œcie¿kê
                        }
                    }
                }
            }
        }
    }

    path_length = INT_MAX;
    int last_vertex = -1;

    // Ustalamy minimalny koszt powrotu do wierzcho³ka startowego
    for (int i = 1; i < vertex; i++)
    {
        int cost = dp[(1 << vertex) - 1][i] + tab[i][0]; // Obliczamy ca³kowity koszt, dodaj¹c koszt powrotu z `i` do 0
        if (cost < path_length)
        {
            path_length = cost; // Zapisujemy najmniejszy koszt
            last_vertex = i; // Zapamiêtujemy ostatni wierzcho³ek w œcie¿ce
        }
    }

    // Tworzenie optymalnej œcie¿ki
    path = new int[vertex + 1];
    int mask = (1 << vertex) - 1;

    // Odtwarzanie œcie¿ki w odwrotnej kolejnoœci
    for (int i = vertex - 1; i >= 0; --i)
    {
        path[i] = last_vertex;
        int temp = last_vertex;
        last_vertex = parent[mask][last_vertex]; // Œledzimy rodzica wierzcho³ka
        mask ^= (1 << temp); // Usuwamy `temp` z maski, by kontynuowaæ wstecz
    }
    path[vertex] = path[0]; // Dodajemy powrót do punktu pocz¹tkowego

    auto end = std::chrono::high_resolution_clock::now();
    execution_time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin); 
}
