// Zapobiega błędom programu w Visual Studio
#define _CRT_SECURE_NO_WARNINGS
// Użyte biblioteki
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Funkcja sprawdzająca czy sudoku jest poprawne
int czyPoprawneSudoku(int sudoku[9][9]) {
    // Sprawdzenie poprawności wierszy i kolumn
    for (int i = 0; i < 9; i++) {
        int wystapiloWiersz[10] = { 0 }; // Tablica pomocnicza do sprawdzenia wystąpienia liczby w wierszu
        int wystapiloKolumna[10] = { 0 }; // Tablica pomocnicza do sprawdzenia wystąpienia liczby w kolumnie

        for (int j = 0; j < 9; j++) {
            // Sprawdzenie wiersza
            if (wystapiloWiersz[sudoku[i][j]] == 1) {
                return 0; // Sudoku niepoprawne
            }
            wystapiloWiersz[sudoku[i][j]] = 1;

            // Sprawdzenie kolumny
            if (wystapiloKolumna[sudoku[j][i]] == 1) {
                return 0; // Sudoku niepoprawne
            }
            wystapiloKolumna[sudoku[j][i]] = 1;
        }
    }

    // Sprawdzenie poprawności kwadratów 3x3
    for (int m = 0; m < 9; m += 3) {
        for (int n = 0; n < 9; n += 3) {
            int wystapiloKwadrat[10] = { 0 }; // Tablica pomocnicza do sprawdzenia wystąpienia liczby w kwadracie 3x3

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (wystapiloKwadrat[sudoku[m + i][n + j]] == 1) {
                        return 0; // Sudoku niepoprawne
                    }
                    wystapiloKwadrat[sudoku[m + i][n + j]] = 1;
                }
            }
        }
    }

    return 1; // Sudoku poprawne
}

int main() {
    // Ustawienie języka konsoli na polski
    setlocale(LC_ALL, "");

    FILE* wejscie, * wyjscie;
    int sudoku[9][9];
    int liczbyWczytane = 0;

    // Otworzenie pliku wejściowego
    wejscie = fopen("dane5.txt", "r");
    if (wejscie == NULL) {
        printf("Nie udalo sie otworzyc pliku dane5.txt\n");
        return 1;
    }

    // Wczytanie danych sudoku z pliku
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (fscanf(wejscie, "%d", &sudoku[i][j]) != 1) {
                printf("Blad wczytywania danych z pliku\n");
                fclose(wejscie);
                return 1;
            }

            // Sprawdzenie zakresu liczby
            if (sudoku[i][j] < 1 || sudoku[i][j] > 9) {
                printf("Liczby w pliku musza byc z zakresu od 1 do 9\n");
                fclose(wejscie);
                return 1;
            }

            liczbyWczytane++;
        }
    }

    // Zamknięcie pliku wejściowego
    fclose(wejscie);

    // Sprawdzenie ilości wczytanych liczb
    if (liczbyWczytane != 81) {
        printf("W pliku musi byc dokladnie 81 liczby\n");
        return 1;
    }

    // Sprawdzenie poprawności sudoku
    int poprawne = czyPoprawneSudoku(sudoku);

    // Otwarcie pliku wyjściowego
    wyjscie = fopen("wynik5.txt", "w");
    if (wyjscie == NULL) {
        printf("Nie udalo sie otworzyc pliku wynik5.txt\n");
        return 1;
    }

    // Zapisanie wyniku do pliku wyjściowego
    if (poprawne) {
        fprintf(wyjscie, "TAK\n");
    }
    else {
        fprintf(wyjscie, "NIE\n");
    }

    // Zamknięcie pliku wyjściowego
    fclose(wyjscie);

    return 0;
}