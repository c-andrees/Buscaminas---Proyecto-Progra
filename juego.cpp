#include "juego.h"
#include "tablero.h"

void dibujarTablero(sf::RenderWindow& window,
                    sf::Font& font,
                    int TAM) {

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {

            sf::RectangleShape celda(
                sf::Vector2f(TAM - 2, TAM - 2));

            celda.setPosition(
                sf::Vector2f(j * TAM, i * TAM));

            if (banderas[i][j]) {
                celda.setFillColor(sf::Color::Yellow);
            }
            
            else if (descubierta[i][j]) {

                if (minas[i][j])
                    celda.setFillColor(sf::Color::Red);
                else
                    celda.setFillColor(sf::Color::White);

            } else {

                celda.setFillColor(sf::Color::Blue);
            }

            window.draw(celda);

            if (descubierta[i][j] && !minas[i][j]) {

                int n = contarMinas(i, j);

                if (n > 0) {

                    sf::Text texto(font);

                    texto.setString(std::to_string(n));

                    texto.setCharacterSize(20);

                    texto.setFillColor(sf::Color::Black);

                    texto.setPosition(
                        sf::Vector2f(
                            j * TAM + 15,
                            i * TAM + 10));

                    window.draw(texto);
                }
            }
        }
    }
}