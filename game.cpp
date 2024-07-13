
#include "game.hpp"

GameOfLife::GameOfLife(int rows, int cols)
    : mGameRows(rows), mGameCols(cols)
{
    mCurrentGameState = arma::umat(rows, cols, arma::fill::zeros);
}

GameOfLife::GameOfLife(const std::string& filePath)
{
    arma::umat temp;
    bool ok = temp.load(filePath, arma::arma_ascii);
    if (ok)
    {
        mCurrentGameState = temp;
        mGameRows = temp.n_rows;
        mGameCols = temp.n_cols;
    }
    else
    {
        throw "Failed to load GameOfLife file";
    }
}

GameOfLife::GameOfLife()
    : mGameRows(0), mGameCols(0), mCurrentGameState(arma::umat(0, 0))
{
}

GameOfLife::~GameOfLife()
{
}

const arma::umat& GameOfLife::GetGameState()
{
    return mCurrentGameState;
}

int GameOfLife::GetRows()
{
    return mGameRows;
}

int GameOfLife::GetCols()
{
    return mGameCols;
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
    mCurrentGameState = NextState(mCurrentGameState);
};

void GameOfLife::FlipCell(int row, int col)
{   
    mCurrentGameState(row, col) = !mCurrentGameState(row, col);
};

bool GameOfLife::SetCells(int row, int col, const arma::umat& cellMatrix)
{
    if (row + cellMatrix.n_rows - 1 >= mGameRows || col + cellMatrix.n_cols - 1 >= mGameCols) { return false; }
    mCurrentGameState.submat(row, col, row + cellMatrix.n_rows - 1, col + cellMatrix.n_cols - 1) = cellMatrix;
    return true;
};

void GameOfLife::RandomizeCells(float aliveProbability)
{
    arma::arma_rng::set_seed_random();
    arma::mat randMatrix = arma::randu(mGameRows, mGameCols);
    mCurrentGameState = randMatrix < aliveProbability;
};

void GameOfLife::ClearCells()
{
    mCurrentGameState = arma::umat(mGameRows, mGameCols, arma::fill::zeros);
};

bool GameOfLife::Save(const std::string& filePath)
{
    bool ok = mCurrentGameState.save(filePath, arma::arma_ascii);
    return ok;
};