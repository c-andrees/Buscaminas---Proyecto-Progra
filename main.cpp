#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

#include "tablero.h"
#include "juego.h"

int main() {

    srand(time(0));

    const int TAM = 50;

    bool juegoTerminado = false;
    bool victoria = false;
    bool enMenu = true;

    sf::RenderWindow window(
        sf::VideoMode({600, 600}),
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
                
                //Manejo del mouse
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
            //Manejo del teclado 
            if (event->is<sf::Event::KeyPressed>()) {
                auto key =
                    event->getIf<sf::Event::KeyPressed>();
                
                if (key->code == sf::Keyboard::Key::R) {
                    reiniciarJuego(15);
                    juegoTerminado = false;
                    victoria = false;

                    std::cout << "Juego reiniciado" << std::endl;
                }
                if (key->code == sf::Keyboard::Key::Enter) {
                    enMenu = false ;;
                }
            }
        }

        window.clear();

        if (enMenu) {
            sf::Text titulo(font);
            titulo.setString("BUSCAMINAS");
            titulo.setCharacterSize(40);
            titulo.setFillColor(sf::Color::White);
            titulo.setPosition(
                sf::Vector2f(150, 150));
            
            sf::Text iniciar(font);
            iniciar.setString("Presiona ENTER para jugar");
            iniciar.setCharacterSize(25);
            iniciar.setFillColor(sf::Color::White);
            iniciar.setPosition(
                sf::Vector2f(120, 300));

            window.draw(titulo);
            window.draw(iniciar);

            window.display();

            continue;
        }
    
        dibujarTablero(window, font, TAM);

        window.display();
    }

    return 0;
}