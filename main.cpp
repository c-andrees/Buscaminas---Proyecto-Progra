#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

#include "tablero.h"
#include "juego.h"

int main() {

    srand(time(0));

    const int TAM = 50;

    sf::RenderWindow window(
        sf::VideoMode({700, 700}),
        "Buscaminas");

    sf::Font font;

    if (!font.openFromFile("arial.ttf")) {
        std::cout << "Error cargando fuente\n";
    }

    generarMinas(15);

    while (window.isOpen()) {

        while (auto event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::MouseButtonPressed>()) {

                auto mouse =
                    event->getIf<sf::Event::MouseButtonPressed>();

                int x = mouse->position.x / TAM;
                int y = mouse->position.y / TAM;

                if (x >= 0 && x < COLUMNAS &&
                    y >= 0 && y < FILAS) {

                    destapar(y, x);

                    if (minas[y][x]) {
                        std::cout << "💣 PERDISTE\n";
                    }
                }
            }
        }

        window.clear();

        dibujarTablero(window, font, TAM);

        window.display();
    }

    return 0;
}