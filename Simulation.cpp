#include "Simulation.h"
#include "Menu.h"
#include "BruteForce.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <climits>
#include <random>
#include <chrono>

#define REPETITION 100
#define UNIT 1000

using namespace std;

void Simulation::simulation_mode(int algnum)
{
    int vertexCounts[] = { 8, 9, 10, 11, 12, 13, 14 }; // liczby wierzcho³ków

    cout << mode_name(algnum) << endl;

    Menu menu;

        for (int i = 0; i < 7; i++)
        {
            cout << "--- rozmiar " << vertexCounts[i] << endl;

            std::chrono::duration<double> czas{};

            
            for (int n = 0; n < REPETITION; n++)
            {
                menu.generate_data(vertexCounts[i], vertexCounts[i] * 2);
              
                int path_length;
                int* path = nullptr;
                std::chrono::duration<double> execution_time;

                

                int** tab = menu.get_tab(); 
                int vertex = menu.get_vertex(); 

                if (algnum == 1)
                {
                    BruteForce bruteForce(tab, vertex);
                    bruteForce.start(path_length, path, execution_time);
                }
                if (algnum == 2)
                {
                    DynamicTSP dynamicTSP(tab, vertex);
                    dynamicTSP.start(path_length, path, execution_time);
                }


                czas += execution_time;
                delete[] path;
            }
            cout << "Sredni czas wyniosl: " << czas.count() * UNIT / REPETITION << " ms" << endl;
        }
        cout << endl << endl << endl;
    }

const char* Simulation::mode_name(int algnum)
{
    switch (algnum)
    {
    case 1:
    {
        return "Algorytm Brute Force";
        break;
    }
    case 2:
    {
        return "Algorytm Programowania Dynamicznego";
        break;
    }
    case 3:
    {
        return "Algorytm Branch and Bound";
        break;
    }
    {
    deafult:
        return "error";
    }
    }
}
