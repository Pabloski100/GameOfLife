#pragma once
#include <SFML/Graphics.hpp>

bool isValidMousePosition(sf::Event::MouseButtonEvent mouseEvent, sf::Vector2u screenSize, sf::Vector2u displacement);