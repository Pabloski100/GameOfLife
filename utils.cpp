#include "utils.hpp"

bool isValidMousePosition(sf::Event::MouseButtonEvent mouseEvent, sf::Vector2u screenSize, sf::Vector2u displacement)
{
    bool validX = displacement.x < mouseEvent.x && mouseEvent.x < screenSize.x - displacement.x;
    bool validY = displacement.y < mouseEvent.y && mouseEvent.y < screenSize.y - displacement.y;

    return validX && validY;
}

arma::umat rotate(arma::umat& mat)
{
    arma::umat rotated(mat.n_cols, mat.n_rows);

    for (int i = 0; i < mat.n_rows; i++)
    {
        rotated.col(i) = mat.row(mat.n_rows - i - 1).as_col();
    }
    
    return rotated;
}