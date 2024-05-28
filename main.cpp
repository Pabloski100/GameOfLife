#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "gamegui.hpp"
#include "game.hpp"
#include "presets.hpp"
#include "utils.hpp"

int main(int argc, char const *argv[])
{

    // Default constants

    std::string loadPath = "";
    arma::umat loadedState;
    bool succesfullLoad = false;

    // Window setup

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2u screenSize = sf::Vector2u(desktop.width, desktop.height);
    int squareSideLenght = std::max(desktop.width, desktop.height) / 100;
    sf::Vector2u tiles = sf::Vector2u(desktop.width / squareSideLenght, desktop.height / squareSideLenght);
    int horizontalRemainder = desktop.width % squareSideLenght;
    int verticalRemainder = desktop.height % squareSideLenght;
    sf::Vector2u displacement = sf::Vector2u(horizontalRemainder / 2, verticalRemainder / 2);

    sf::RenderWindow window(desktop, "Game of Life", sf::Style::Fullscreen);
    window.setFramerateLimit(30);

    // Game data

    GameGui gameGui(tiles, displacement, squareSideLenght);
    GameOfLife gof(tiles.y, tiles.x);
    sf::Clock clock;
    sf::Time delta = sf::milliseconds(50);
    float randomFactor = 0.5f;
    bool gamePaused = false;
    int selectedPreset = 0;

    if (succesfullLoad)
    {
        gof.currentGameState = loadedState;
        gamePaused = true;
        gameGui.Update(loadedState);
    }
    
    // Application loop

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close(); 
            }

            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::R:
                    gof.RandomizeCells(randomFactor);
                    gameGui.Update(gof.currentGameState);
                    break;
                case sf::Keyboard::P:
                    gamePaused = !gamePaused;
                    if (gamePaused)
                    {
                        window.setTitle("Game of Life - PAUSED");
                    } else
                    {
                        window.setTitle("Game of Life");
                    }                    
                    break;
                case sf::Keyboard::Space:
                    gamePaused = true;
                    window.setTitle("Game of Life - PAUSED");
                    gof.NextGeneration();
                    gameGui.Update(gof.currentGameState);
                    break;
                case sf::Keyboard::C:
                    gof.ClearCells();
                    gameGui.Update(gof.currentGameState);
                    break;
                case sf::Keyboard::S:
                    gamePaused = true;
                    gof.Save("./savetest.txt");
                    break;
                case sf::Keyboard::L:
                    gamePaused = true;
                    window.setTitle("Game of Life - PAUSED");
                    gof.currentGameState = loadedState;
                    gameGui.Update(loadedState);
                    break;
                default:
                    if (sf::Keyboard::Num0 <= event.key.code && event.key.code <= sf::Keyboard::Num9)
                    {
                        selectedPreset = event.key.code - sf::Keyboard::Num0;
                    }
                    break;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && isValidMousePosition(event.mouseButton, screenSize, displacement))
            {
                gamePaused = true;
                int xCell = (event.mouseButton.x - displacement.x) / squareSideLenght;
                int yCell = (event.mouseButton.y - displacement.y) / squareSideLenght;

                switch (event.mouseButton.button)
                {
                case sf::Mouse::Left:
                    gof.FlipCell(yCell, xCell);
                    gameGui.UpdateCell(yCell, xCell, gof.currentGameState);
                    break;
                case sf::Mouse::Right:
                    gof.SetCells(yCell, xCell, presets[selectedPreset]);
                    gameGui.Update(gof.currentGameState);
                    break;
                default:
                    break;
                }
            }
        }

        if (!gamePaused && clock.getElapsedTime() > delta)
        {
            gof.NextGeneration();
            gameGui.Update(gof.currentGameState);
            clock.restart();
        }

        window.clear(sf::Color::Black);
        window.draw(gameGui);
        window.display();
    }

    return 0;
}