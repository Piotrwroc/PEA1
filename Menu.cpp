#include "Menu.h"
#include "Simulation.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <climits>
#include <random>

using namespace std;

void Menu::f_menu()
{
    bool x = true;
    while (x)
    {
        int wybor_opcji = 0;
        cout << endl;
        cout << "Autorem programu jest Piotr Jozefek 272311" << endl;
        cout << "Wybierz funkcje programu: " << endl;
        cout << "1. Wczytaj dane z pliku" << endl;
        cout << "2. Zapisz dane do pliku" << endl;
        cout << "3. Wygenerowanie danych losowych" << endl;
        cout << "4. Wyswietlenie ostatnio wczytanych lub wygenerowanych danych" << endl;
        cout << "5. Uruchomienie algorytmu Brute force" << endl;
        cout << "6. Uruchomienie algorytmu programowania dynamicznego Helda-Karpa" << endl;
        cout << "7. Uruchomienie algorytmu Branch and Bound" << endl;
        cout << "8. Symulacja" << endl;
        cout << "9. Wylaczenie programu" << endl;
        cout << endl;
        cin >> wybor_opcji;

        switch (wybor_opcji)
        {
        case 1:
        {
            string filename;
            cout << "Podaj nazwe pliku do odczytu" << endl;
            cin >> filename;
            const char* filenamev2 = filename.c_str();
            load_data(filenamev2);
            break;
        }

        case 2:
        {
            string filename;
            cout << "Podaj nazwe pliku do zapisu" << endl;
            cin >> filename;
            const char* filenamev2 = filename.c_str();
            save_data(filenamev2); 
            break;
        }

        case 3:
        {
            int liczba_wierzcholkow, max_value;
            cout << "Podaj liczbe wierzcholkow: ";
            cin >> liczba_wierzcholkow;
            cout << "Podaj maksymalna wartosc wagi: ";
            cin >> max_value;
            generate_data(liczba_wierzcholkow, max_value);
            cout << "Dane zostaly wygenerowane losowo." << endl << endl;
            break;
        }

        case 4:
        {
            display_data();
            break;
        }

        case 5: 
        {
            if (tab != nullptr)
            {
                int path_length;
                int* path = nullptr;
                std::chrono::duration<double> execution_time;

                BruteForce bruteForce(tab, vertex); // Utworzenie obiektu z danymi
                bruteForce.start(path_length, path, execution_time); // Uruchomienie algorytmu i zapisanie wyników

                // Wyœwietlenie wyników
                cout << "Minimalny koszt sciezki: " << path_length << endl;           
                cout << "Sciezka: ";
                for (int i = 0; i <= vertex; ++i) 
                {
                    cout << path[i] << " ";
                }
                cout << endl;
                cout << "Czas wykonania: " << execution_time.count() * 1000 << " ms" << endl;

                delete[] path; 
            }
            else
            {
                cout << "Brak danych do analizy." << endl;
            }
            break;
        }

        case 6:
        {
            if (tab != nullptr)
            {
                int path_length;
                int* path = nullptr;
                std::chrono::duration<double> execution_time;

                DynamicTSP dynamicTSP(tab, vertex); // Tworzenie obiektu klasy z danymi
                dynamicTSP.start(path_length, path, execution_time); // Uruchomienie algorytmu i zapisanie wyników

                // Wyœwietlenie wyników
                cout << "Minimalny koszt sciezki: " << path_length << endl;
                cout << "Sciezka: ";
                for (int i = 0; i <= vertex; ++i) 
                {
                    cout << path[i] << " ";
                }
                cout << endl;
                cout << "Czas wykonania: " << execution_time.count() * 1000 << " ms" << endl;

                delete[] path;
            }
            else
            {
                cout << "Brak danych do analizy." << endl;
            }
            break;
        }

        case 7:
        {
            // Branch and Bound
            break;
        }

        case 8:
        {
            Simulation simulation;
            simulation.simulation_mode(2);
            break;
        }

        case 9:
        {
            cout << "Zakonczono dzialanie programu" << endl;
            exit(0);
            break;
        }

        default:
        {
            cout << "Wybrano niepoprawna opcje" << endl;
            break;
        }
        }
    }
}

//Wczytanie danych z pliku
void Menu::load_data(const char* filename)
{
    // Usuwanie istniej¹cych danych, jeœli takie s¹
    if (tab != nullptr)
    {
        for (int i = 0; i < vertex; i++)
        {
            delete[] tab[i];
        }
        delete[] tab;
        delete[] path;
        delete[] finalpath;

        tab = nullptr;
        path = nullptr;
        finalpath = nullptr;
    }

    ifstream file;
    file.open(filename);
    if (file.is_open())
    {
        file >> vertex;
        tab = new int* [vertex];
        path = new int[vertex + 1];
        finalpath = new int[vertex + 1];

        for (int i = 0; i < vertex; i++)
        {
            tab[i] = new int[vertex];
        }

        for (int i = 0; i < vertex; i++)
        {
            for (int j = 0; j < vertex; j++)
            {
                file >> weight;
                tab[i][j] = weight;
            }
        }
        file.close();
        cout << "Odczyt udany" << endl << endl;
    }
    else
    {
        cout << "Nie mozna odtworzyc pliku do odczytu: " << filename << endl << endl;
    }
}

//Zapis danych do pliku
void Menu::save_data(const char* filename)
{
    if (tab == nullptr)
    {
        cout << "Brak danych do zapisania." << endl;
        return;
    }

    ofstream file;
    file.open(filename);
    if (file.is_open())
    {
        file << vertex << endl;

        for (int i = 0; i < vertex; i++)
        {
            for (int j = 0; j < vertex; j++)
            {
                file << tab[i][j] << " ";
            }
            file << endl;
        }

        file.close();
        cout << "Zapis udany: " << filename << endl << endl;
    }
    else
    {
        cout << "Nie mozna otworzyc pliku do zapisu: " << filename << endl << endl;
    }
}

//Generowanie losowych danych
void Menu::generate_data(int vertex_number, int max_weight)
{
    // Usuwanie istniej¹cych danych, jeœli s¹ wczytane
    if (tab != nullptr)
    {
        for (int i = 0; i < vertex; i++)
        {
            delete[] tab[i];
        }
        delete[] tab;
        delete[] path;
        delete[] finalpath;

        tab = nullptr;
        path = nullptr;
        finalpath = nullptr;
    }

    vertex = vertex_number;
    tab = new int* [vertex];
    path = new int[vertex + 1];
    finalpath = new int[vertex + 1];

    for (int i = 0; i < vertex; i++)
    {
        tab[i] = new int[vertex];
    }

    // Inicjalizacja generatora liczb losowych
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, max_weight);

    // Generowanie losowych wartoœci dla tablicy wag krawêdzi
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            if (i == j)
            {
                tab[i][j] = - 1; // Przekatna ustawiona na -1
            }
            else
            {
                tab[i][j] = dis(gen);
            }
        }
    }
}

//Wyswietlenie danych
void Menu::display_data()
{
    if (tab == nullptr)
    {
        cout << "Brak danych do wyswietlenia." << endl;
        return;
    }

    cout << "Wczytane dane: " << endl;
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Destruktor 
Menu::~Menu()
{
    if (tab != nullptr)
    {
        for (int i = 0; i < vertex; i++)
        {
            delete[] tab[i];
        }
        delete[] tab;
    }
    delete[] path;
    delete[] finalpath;
}