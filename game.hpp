#pragma once
#include <armadillo>

class GameOfLife
{
private:
    int mGameRows;
    int mGameCols;
    arma::umat mCurrentGameState;
    const static arma::umat mKernel;
    arma::umat PaddState(arma::umat& gameState);
    arma::umat NextState(arma::umat& gameState);
public:
    GameOfLife(int rows, int cols);
    GameOfLife(const std::string& filePath);
    GameOfLife();
    ~GameOfLife();
    const arma::umat& GetGameState();
    int GetRows();
    int GetCols();
    void NextGeneration();
    void FlipCell(int row, int col);
    bool SetCells(int row, int col, const arma::umat& cellMatrix);
    void RandomizeCells(float aliveProbability);
    void ClearCells();
    bool Save(const std::string& filePath);
};
