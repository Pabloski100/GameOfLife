#pragma once
#include <armadillo>

class GameOfLife
{
private:
    int mGameRows;
    int mGameCols;
    const static arma::umat mKernel;
    arma::umat PaddState(arma::umat& gameState);
    arma::umat NextState(arma::umat& gameState);
public:
    arma::umat currentGameState;
    GameOfLife(int rows, int cols);
    ~GameOfLife();
    void NextGeneration();
    void FlipCell(int row, int col);
    bool SetCells(int row, int col, const arma::umat& cellMatrix);
    void RandomizeCells(float aliveProbability);
    void ClearCells();
    bool Save(const std::string& filePath);
    bool Load(const std::string& filePath);
};
