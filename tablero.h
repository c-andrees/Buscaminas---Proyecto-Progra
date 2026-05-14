#pragma once

const int FILAS = 10;
const int COLUMNAS = 10;

extern bool descubierta[FILAS][COLUMNAS];
extern bool minas[FILAS][COLUMNAS];
extern bool banderas[FILAS][COLUMNAS];


void generarMinas(int totalMINAS);

int contarMinas(int f, int c);

void destapar(int f, int c);

bool verificarVictoria();

void toggleBandera(int f, int c);

void reiniciarJuego(int totalMINAS);