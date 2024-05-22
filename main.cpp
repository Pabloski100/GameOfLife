#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include "gamegui.hpp"
#include "game.hpp"
#include "presets.hpp"

int main(int argc, char const *argv[])
{

    // Default constants

    int WINDOW_WIDTH = 1800;
    int WINDOW_HEIGHT = 900;
    int SQUARE_SIDE_LENGHT = 20;
    std::string loadPath = "";
    arma::umat loadedState;
    bool succesfullLoad = false;

    // Argument processing

    if (argc == 3)
    {
        loadPath = argv[1];
        SQUARE_SIDE_LENGHT = atoi(argv[2]);
        succesfullLoad = loadedState.load(loadPath, arma::arma_ascii);
        WINDOW_WIDTH = SQUARE_SIDE_LENGHT * loadedState.n_cols;
        WINDOW_HEIGHT = SQUARE_SIDE_LENGHT * loadedState.n_rows;
    }
    else if (argc == 4)
    {
        WINDOW_WIDTH = atoi(argv[1]);
        WINDOW_HEIGHT = atoi(argv[2]);
        SQUARE_SIDE_LENGHT = atoi(argv[3]);

        if (!(WINDOW_WIDTH && WINDOW_HEIGHT && SQUARE_SIDE_LENGHT))
        {
            std::cout << "Invalid arguments\n";
            return 0;
        }
    }

    // Checks

    if (WINDOW_WIDTH > sf::VideoMode::getDesktopMode().width || 
        WINDOW_HEIGHT > sf::VideoMode::getDesktopMode().height)
    {
        std::cout << "Window dimensions too big\n";
        return 0;
    }

    if (WINDOW_WIDTH < 300 || WINDOW_HEIGHT < 300)
    {
        std::cout << "Window dimensions too small\n";
        return 0;
    }

    if (WINDOW_WIDTH % SQUARE_SIDE_LENGHT != 0 ||
        WINDOW_HEIGHT % SQUARE_SIDE_LENGHT != 0)
    {
        std::cout << "Invalid square side lenght\n";
        return 0;
    }

    // Window setup

    int horzontalTiles = WINDOW_WIDTH / SQUARE_SIDE_LENGHT;
    int verticalTiles = WINDOW_HEIGHT / SQUARE_SIDE_LENGHT;


    sf::RenderWindow window(sf::VideoMode(
        WINDOW_WIDTH, WINDOW_HEIGHT
    ), "Game of Life", sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(30);
    window.setPosition(sf::Vector2i(0, 0));

    // Game data

    GameGui gameGui(verticalTiles, horzontalTiles, SQUARE_SIDE_LENGHT);
    GameOfLife gof(verticalTiles, horzontalTiles);
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

            if (event.type == sf::Event::MouseButtonReleased)
            {
                gamePaused = true;
                int xCell = event.mouseButton.x / SQUARE_SIDE_LENGHT;
                int yCell = event.mouseButton.y / SQUARE_SIDE_LENGHT;

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