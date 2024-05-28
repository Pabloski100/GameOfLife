#pragma once
#include <SFML/Graphics.hpp>
#include <armadillo>

bool isValidMousePosition(sf::Event::MouseButtonEvent mouseEvent, sf::Vector2u screenSize, sf::Vector2u displacement);
arma::umat rotate(arma::umat& mat);