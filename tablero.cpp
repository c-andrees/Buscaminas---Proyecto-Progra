#include "tablero.h"
#include <cstdlib>

bool descubierta[FILAS][COLUMNAS] = {false};
bool minas[FILAS][COLUMNAS] = {false};

void generarMinas(int totalMinas) {

    while (totalMinas > 0) {

        int f = rand() % FILAS;
        int c = rand() % COLUMNAS;

        if (!minas[f][c]) {
            minas[f][c] = true;
            totalMinas--;
        }
    }
}

int contarMinas(int f, int c) {

    int contador = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {

            int nf = f + i;
            int nc = c + j;

            if (nf >= 0 && nf < FILAS &&
                nc >= 0 && nc < COLUMNAS) {

                if (minas[nf][nc]) {
                    contador++;
                }
            }
        }
    }

    return contador;
}

void destapar(int f, int c) {

    if (f < 0 || f >= FILAS ||
        c < 0 || c >= COLUMNAS)
        return;

    if (descubierta[f][c])
        return;

    descubierta[f][c] = true;

    if (minas[f][c])
        return;

    int n = contarMinas(f, c);

    if (n > 0)
        return;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {

            destapar(f + i, c + j);
        }
    }
}

