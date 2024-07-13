
#include "gamegui.hpp"

GameGui::GameGui(sf::Vector2u boardSize, sf::Vector2u displacement, int cellLength)
{
    mVertices.setPrimitiveType(sf::Quads);
    mVertices.resize(boardSize.x * boardSize.y * 4);

    for (int i = 0; i < boardSize.x; i++)
    {
        for (int j = 0; j < boardSize.y; j++)
        {
            sf::Vertex* quad = &mVertices[(i + j * boardSize.x) * 4];

            quad[0].position = sf::Vector2f(i * cellLength + displacement.x, j * cellLength + displacement.y);
            quad[1].position = sf::Vector2f((i + 1) * cellLength + displacement.x, j * cellLength + displacement.y);
            quad[2].position = sf::Vector2f((i + 1) * cellLength + displacement.x, (j + 1) * cellLength + displacement.y);
            quad[3].position = sf::Vector2f(i * cellLength + displacement.x, (j + 1) * cellLength + displacement.y);

            quad[0].color = sf::Color::Black;
            quad[1].color = sf::Color::Black;
            quad[2].color = sf::Color::Black;
            quad[3].color = sf::Color::Black;
        }
    }
}

GameGui::~GameGui()
{
}

void GameGui::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mVertices, states);
}

void GameGui::Update(const arma::umat& state)
{
    for (int i = 0; i < state.n_cols; i++)
    {
        for (int j = 0; j < state.n_rows; j++)
        {
            sf::Vertex* quad = &mVertices[(i + j * state.n_cols) * 4];

            if (state(j, i))
            {
                quad[0].color = sf::Color::White;
                quad[1].color = sf::Color::White;
                quad[2].color = sf::Color::White;
                quad[3].color = sf::Color::White;
            } else
            {
                quad[0].color = sf::Color::Black;
                quad[1].color = sf::Color::Black;
                quad[2].color = sf::Color::Black;
                quad[3].color = sf::Color::Black;
            }
        }
    }
}

void GameGui::UpdateCell(int row, int col, const arma::umat& state)
{
    sf::Vertex* quad = &mVertices[(col + row * state.n_cols) * 4];

    if (state(row, col))
    {
        quad[0].color = sf::Color::White;
        quad[1].color = sf::Color::White;
        quad[2].color = sf::Color::White;
        quad[3].color = sf::Color::White;
    } else
    {
        quad[0].color = sf::Color::Black;
        quad[1].color = sf::Color::Black;
        quad[2].color = sf::Color::Black;
        quad[3].color = sf::Color::Black;
    }
}
