#pragma once
#include <SFML/Graphics.hpp>
#include <armadillo>

class GameGui : public sf::Drawable, public sf::Transformable
{
private:
    sf::VertexArray mVertices;
public:
    GameGui(int rows, int cols, int sideLength);
    ~GameGui();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void Update(arma::umat& state);
    void UpdateCell(int row, int col, arma::umat& state);
};
