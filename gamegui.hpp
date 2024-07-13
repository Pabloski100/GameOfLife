#pragma once
#include <SFML/Graphics.hpp>
#include <armadillo>

class GameGui : public sf::Drawable, public sf::Transformable
{
private:
    sf::VertexArray mVertices;
public:
    GameGui(sf::Vector2u boardSize, sf::Vector2u displacement, int cellLength);
    ~GameGui();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void Update(const arma::umat& state);
    void UpdateCell(int row, int col, const arma::umat& state);
};
