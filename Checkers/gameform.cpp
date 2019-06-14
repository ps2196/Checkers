#include "gameform.h"
#include "ui_gameform.h"

GameForm::GameForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameForm)
{
    ui->setupUi(this);
}

GameForm::~GameForm()
{
    delete ui;
}

void GameForm::drawBoard()
{
    ui->boardView->drawBoard();
}

void GameForm::setGame(CheckersGame *game)
{
    m_game = game;
    ui->boardView->setBoard(m_game->board());
    ui->boardView->setActivePlayer(m_game->activePlayer());

    connect(ui->mainMenuButton, SIGNAL(clicked()),
            this, SIGNAL(menuButtonClicked()));

    connect(ui->boardView, SIGNAL(pieceSelected(int, int)),
            m_game, SLOT(calculateMovesForPiece(int,int)));

    connect(m_game,SIGNAL(availableMovesCalculated(int, int, QList<QPair<int, int>>)),
            ui->boardView, SLOT(markAvailableMoves(int, int, QList<QPair<int, int>>)));

    connect(ui->boardView, SIGNAL(mousePieceMove(int, int, int, int)),
            m_game, SLOT(movePiece(int,int, int, int)));

    connect(m_game->board(), SIGNAL(pieceMoved(int,int,int,int)),
            ui->boardView, SLOT(movePiece(int,int,int,int)));

    connect(m_game->board(), SIGNAL(pieceCaptured(int,int)),
            ui->boardView, SLOT(capturePiece(int,int)));

    connect(m_game->board(), SIGNAL(piecePromoted(int,int,int)),
            ui->boardView, SLOT(promotePiece(int,int,int)));

    connect(m_game, SIGNAL(activePlayerChanged(bool)),
            this, SLOT(manageInfoLabel(bool)));

    connect(m_game, SIGNAL(gameEnded(bool)),
            this, SLOT(endGame(bool)));
}

void GameForm::manageInfoLabel(bool activePlayer)
{
    if(activePlayer == CheckersGame::WHITE_PLAYER)
        ui->gameInfoLabel->setText("White player turn!");
    else
        ui->gameInfoLabel->setText("Black player turn!");

    ui->boardView->setActivePlayer(activePlayer);
}

void GameForm::setWhiteName(const QString name)
{
    ui->whiteNameLabel->setText(name);
}

void GameForm::setBlackName(const QString name)
{
    ui->blackNameLabel->setText(name);
}

void GameForm::endGame(bool winner)
{
    if(winner == CheckersGame::WHITE_PLAYER)
    {
        ui->gameInfoLabel->setText("White won!");
        ui->boardView->setActivePlayer(CheckersGame::BLACK_PLAYER);
    }
    else if(winner == CheckersGame::BLACK_PLAYER)
    {
        ui->gameInfoLabel->setText("Black won!");
        ui->boardView->setActivePlayer(CheckersGame::WHITE_PLAYER);
    }
}

