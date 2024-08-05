#include "utils.hpp"

bool isValidMousePosition(sf::Event::MouseButtonEvent mouseEvent, sf::Vector2u screenSize, sf::Vector2u displacement)
{
    bool validX = displacement.x < mouseEvent.x && mouseEvent.x < screenSize.x - displacement.x;
    bool validY = displacement.y < mouseEvent.y && mouseEvent.y < screenSize.y - displacement.y;

    return validX && validY;
}

void rotate(arma::umat& mat)
{
    mat = arma::fliplr(arma::trans(mat));
}

void mirror(arma::umat& mat)
{
    mat = arma::fliplr(mat);
}