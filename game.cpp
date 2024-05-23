
#include "game.hpp"

GameOfLife::GameOfLife(int rows, int cols)
    : mGameRows(rows), mGameCols(cols)
{
    currentGameState = arma::umat(rows, cols, arma::fill::zeros);
}

GameOfLife::~GameOfLife()
{
}

const arma::umat GameOfLife::mKernel = arma::umat(
    {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    }
);

arma::umat GameOfLife::PaddState(arma::umat& gameState)
{
    arma::umat paddedState(mGameRows + 2, mGameCols + 2);
    paddedState.submat(1, 1, mGameRows, mGameCols) = gameState;
    paddedState.submat(0, 1, 0, mGameCols) = gameState.row(mGameRows - 1);
    paddedState.submat(mGameRows + 1, 1, mGameRows + 1, mGameCols) = gameState.row(0);
    paddedState.submat(1, 0, mGameRows, 0) = gameState.col(mGameCols - 1);
    paddedState.submat(1, mGameCols + 1, mGameRows, mGameCols + 1) = gameState.col(0);
    paddedState(0, 0) = gameState(mGameRows - 1, mGameCols - 1);
    paddedState(mGameRows + 1, mGameCols + 1) = gameState(0, 0);
    paddedState(0, mGameCols + 1) = gameState(mGameRows - 1, 0);
    paddedState(mGameRows + 1, 0) = gameState(0, mGameCols - 1);
    return paddedState;
}

arma::umat GameOfLife::NextState(arma::umat& gameState)
{
    arma::umat paddedState = PaddState(gameState);
    arma::umat paddedNeighbourCount = arma::conv2(paddedState, GameOfLife::mKernel, "same");
    arma::umat neighbourCount = paddedNeighbourCount.submat(1, 1, mGameRows, mGameCols);
    arma::umat canExist = neighbourCount == 2;
    arma::umat mustExist = neighbourCount == 3;
    arma::umat newState = (gameState && canExist) || mustExist;
    return newState;
}

void GameOfLife::NextGeneration()
{
    currentGameState = NextState(currentGameState);
};

void GameOfLife::FlipCell(int row, int col)
{   
    currentGameState(row, col) = !currentGameState(row, col);
};

bool GameOfLife::SetCells(int row, int col, const arma::umat& cellMatrix)
{
    if (row + cellMatrix.n_rows - 1 >= mGameRows || col + cellMatrix.n_cols - 1 >= mGameCols) { return false; }
    currentGameState.submat(row, col, row + cellMatrix.n_rows - 1, col + cellMatrix.n_cols - 1) = cellMatrix;
    return true;
};

void GameOfLife::RandomizeCells(float aliveProbability)
{
    arma::arma_rng::set_seed_random();
    arma::mat randMatrix = arma::randu(mGameRows, mGameCols);
    currentGameState = randMatrix < aliveProbability;
};

void GameOfLife::ClearCells()
{
    currentGameState = arma::umat(mGameRows, mGameCols, arma::fill::zeros);
};

bool GameOfLife::Save(const std::string& filePath)
{
    bool ok = currentGameState.save(filePath, arma::arma_ascii);
    return ok;
};

bool GameOfLife::Load(const std::string& filePath)
{
    arma::umat temp;
    bool ok = temp.load(filePath, arma::arma_ascii);
    if (ok)
    {
        currentGameState = temp;
        mGameRows = temp.n_rows;
        mGameCols = temp.n_cols;
    }
    return ok;
};