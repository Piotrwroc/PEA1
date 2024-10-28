#ifndef MENU_H
#define MENU_H

#include "BruteForce.h"
#include "DynamicTSP.h"


class Menu
{
    int vertex, weight;
    int** tab = nullptr; // Deklaracja tablicy dynamicznej do przechowywania danych
    int* path = nullptr; // Deklaracja tablicy dynamicznej do przechowywania �cie�ki
    int* finalpath = nullptr; // Deklaracja tablicy dynamicznej do przechowywania ostatecznej �cie�ki

public:
    void f_menu();
    void load_data(const char* filename);
    void save_data(const char* filename);
    void generate_data(int vertex_number, int max_weight);
    void display_data();

    int** get_tab() const { return tab; } // Funkcja zwraca tablic� tab
    int get_vertex() const { return vertex; } // Funkcja zwraca liczb� wierzcho�k�w
    ~Menu();
};

#endif // MENU_H