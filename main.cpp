#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

#include "tablero.h"
#include "juego.h"

int main() {

    srand(time(0));

    const int TAM = 60;

    bool juegoTerminado = false;
    bool victoria = false;

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

            if (!juegoTerminado) {

                if (event->is<sf::Event::MouseButtonPressed>()) {

                    auto mouse =
                        event->getIf<sf::Event::MouseButtonPressed>();

                    int x = mouse->position.x / TAM;
                    int y = mouse->position.y / TAM;

                    if (x >= 0 && x < COLUMNAS &&
                        y >= 0 && y < FILAS) {

                        if(mouse->button == sf::Mouse::Button::Right) {
                            toggleBandera(y, x);
                        }
                        else {
                            destapar(y, x);

                            if (minas[y][x]) {
                                std::cout << "PERDISTE"<<std::endl;
                                juegoTerminado = true;
                            }
                            if (verificarVictoria()) {
                            std::cout << "GANASTE"<<std::endl;
                            juegoTerminado = true;
                            victoria = true;
                            }
                        }
                    }
                }
            }
            if (event->is<sf::Event::KeyPressed>()) {
                auto key =
                    event->getIf<sf::Event::KeyPressed>();
                
                if (key->code == sf::Keyboard::Key::R) {
                    reiniciarJuego(15);
                    juegoTerminado = false;
                    victoria = false;

                    std::cout << "Juego reiniciado" << std::endl;
                    }
            }
        }

        window.clear();

        dibujarTablero(window, font, TAM);

        window.display();
    }

    return 0;
}