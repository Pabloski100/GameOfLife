#include <SFML/Graphics.hpp>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include "gamegui.hpp"
#include "game.hpp"
#include "presets.hpp"
#include "utils.hpp"

int main(int argc, char const *argv[])
{
    // Check arguments

    if (argc < 2)
    {
        std::cout << "ERROR: game name missing" << std::endl;
        return 0;
    }

    // Load saved game (if exists)

    std::string gameFileName(argv[1]);
    GameOfLife gof;
    bool gameLoaded = false;

    if (std::filesystem::exists(gameFileName))
    {
        gof = GameOfLife(gameFileName);
        gameLoaded = true;
    }
    
    // Window setup

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2u screenSize = sf::Vector2u(desktop.width, desktop.height);

    int squareSideLenght;
    sf::Vector2u tiles;

    if (gameLoaded)
    {
        tiles = sf::Vector2u(gof.GetCols(), gof.GetRows());
        squareSideLenght = std::min(desktop.width / tiles.x, desktop.height / tiles.y);
    } else
    {
        int gameSize = (argc > 2) ? std::stoi(argv[2]) : 100;
        squareSideLenght = std::max(desktop.width, desktop.height) / gameSize;
        tiles = sf::Vector2u(desktop.width / squareSideLenght, desktop.height / squareSideLenght);
    }

    int horizontalRemainder = desktop.width % squareSideLenght;
    int verticalRemainder = desktop.height % squareSideLenght;
    sf::Vector2u displacement = sf::Vector2u(horizontalRemainder / 2, verticalRemainder / 2);
    sf::RenderWindow window(desktop, "Game of Life", sf::Style::Fullscreen);
    window.setFramerateLimit(30);

    // Game data

    float randomFactor = 0.5f;
    bool gamePaused = false;
    int selectedPreset = 0;
    sf::Clock clock;
    sf::Time delta = sf::milliseconds(50);
    GameGui gameGui(tiles, displacement, squareSideLenght);
    if (gameLoaded){
        gameGui.Update(gof.GetGameState());
        gamePaused = true;
    } else
    {
        gof = GameOfLife(tiles.y, tiles.x);
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
                    gameGui.Update(gof.GetGameState());
                    break;
                case sf::Keyboard::P:
                    gamePaused = !gamePaused;
                    break;
                case sf::Keyboard::Space:
                    gamePaused = true;
                    gof.NextGeneration();
                    gameGui.Update(gof.GetGameState());
                    break;
                case sf::Keyboard::C:
                    gof.ClearCells();
                    gameGui.Update(gof.GetGameState());
                    break;
                case sf::Keyboard::S:
                    gamePaused = true;
                    gof.Save(gameFileName);
                    break;
                case sf::Keyboard::T:
                    rotate(presets[selectedPreset]);
                    break;
                case sf::Keyboard::M:
                    mirror(presets[selectedPreset]);
                    break;
                case sf::Keyboard::Down:
                    delta = (delta < sf::milliseconds(250)) ? delta + sf::milliseconds(20) : delta;
                    break;
                case sf::Keyboard::Up:
                    delta = (delta > sf::milliseconds(30)) ? delta - sf::milliseconds(20) : delta;
                    break;
                case sf::Keyboard::Left:
                    randomFactor = (randomFactor > 0.15f) ? randomFactor - 0.1f : randomFactor;
                    break;
                case sf::Keyboard::Right:
                    randomFactor = (randomFactor < 0.85f) ? randomFactor + 0.1f : randomFactor;
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
                    gameGui.UpdateCell(yCell, xCell, gof.GetGameState());
                    break;
                case sf::Mouse::Right:
                    gof.SetCells(yCell, xCell, presets[selectedPreset]);
                    gameGui.Update(gof.GetGameState());
                    break;
                default:
                    break;
                }
            }
        }

        if (!gamePaused && clock.getElapsedTime() > delta)
        {
            gof.NextGeneration();
            gameGui.Update(gof.GetGameState());
            clock.restart();
        }

        window.clear(sf::Color::Black);
        window.draw(gameGui);
        window.display();
    }

    return 0;
}