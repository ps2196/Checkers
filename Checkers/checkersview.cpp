#include "boardsquare.h"
#include "checkersgame.h"
#include "checkersview.h"
#include "piecegraphicsitem.h"

#include <QGraphicsGridLayout>
#include <QPainter>
#include <iostream>
#include <iomanip>
#include <QPropertyAnimation>
#include <QTimer>

CheckersView::CheckersView(QWidget *parent) : QGraphicsView(parent)
{
    _board = nullptr;
    _squareSize = QSize(10,10);
    scene = nullptr;
    m_selected_piece_col = m_selected_piece_row = -1;
    m_active_player = CheckersGame::WHITE_PLAYER;
}

void CheckersView::setBoard(CheckersBoard *board)
{
    if(board == _board)
        return;
    _board = board;
    drawBoard();
}

QSize CheckersView::minimumSizeHint() const
{
    return QSize(400,400);
}

QSize CheckersView::sizeHint() const
{
    return QSize(800,800);
}

//Draw board and pieces in standard starting positions
void CheckersView::drawBoard()
{
    if(scene)
        delete scene;
    if(_board)
    {
        scene = new QGraphicsScene(this);
        scene->setSceneRect(0,0, 800, 800);
        scene->setItemIndexMethod(QGraphicsScene::NoIndex);

        qreal square_size = 800/8;//width() /8.0 + 70;
        //Draw board
        for (int row = 0; row < _board->rows(); ++row) {
            for(int col = 0; col < _board->columns(); ++col)
            {
                //Squares
                QColor color = (row+col)%2 ? palette().color(QPalette::Light) : palette().color(QPalette::Mid);
                BoardSquare *square = new BoardSquare(color, square_size);
                square->setPos(col * square_size,
                               row * square_size);
                connect(square, SIGNAL(selected(int, int)), this, SLOT(emitMoveEvent(int, int)));
                scene->addItem(square);
                //Pieces
                int sq_value = _board->square(row, col);
                if(sq_value != CheckersBoard::EMPTY_SQUARE)
                {         
                    PieceGraphicsItem *piece = new PieceGraphicsItem(sq_value);
                    connect(piece, SIGNAL(selected(int, int)), this, SLOT(emitPieceSelectionEvent(int, int)));
                    piece->setPos(col * square_size,
                                  row * square_size);
                    piece->setZValue(10); // make sure pieces will always be drawn on top of squares

                    scene->addItem(piece);
                }
            }
        }
        setScene(scene);
        setRenderHint(QPainter::Antialiasing);
//       setCacheMode(QGraphicsView::CacheBackground);
        show();
       // fitInView(sceneRect(), Qt::AspectRatioMode::KeepAspectRatioByExpanding);
    }
}

//Return square at given position
BoardSquare *CheckersView::squareAtPos(int row, int col)
{
     QGraphicsItem *item = scene->itemAt(col*100, row*100, transform());
     if(!item)
         return nullptr;
     BoardSquare *sq  = dynamic_cast<BoardSquare*>(item);
     return sq;
}

//Return piece at given position
PieceGraphicsItem *CheckersView::pieceAtPos(int row, int col)
{
    QGraphicsItem *item = scene->itemAt(col*100, row*100, transform());
    if(!item)
        return nullptr;
    PieceGraphicsItem *piece = dynamic_cast<PieceGraphicsItem*>(item);
    return piece;
}


//Handler for CheckersGame movesCalculated signal - higlhights squares valid for selected piece to move
void CheckersView::markAvailableMoves(int row , int col, QList<QPair<int, int>> availablePos )
{
    unhighlightAllSquares();
    PieceGraphicsItem *piece = pieceAtPos(row, col);
    if(piece)
        piece->highlight();
    for(auto pos = availablePos.begin(); pos != availablePos.end(); ++pos )
    {
        BoardSquare *sq = squareAtPos(pos->first, pos->second);
        if(sq)
            sq->highlight();
    }
}

//Change piece postion on the board
void CheckersView::movePiece(int srow, int scol, int trow, int tcol)
{
    unhighlightAllSquares();
    PieceGraphicsItem *piece = pieceAtPos(srow, scol);
    if(piece)
    { //Animate piece movement
        QPropertyAnimation *animation = new QPropertyAnimation(piece, "pos");
        animation->setDuration(1000);

        animation->setStartValue(piece->pos());
        animation->setEndValue(QPointF(tcol*100, trow*100));

        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void CheckersView::capturePiece(int row, int col)
{
    PieceGraphicsItem *piece = pieceAtPos(row,col);
    if(piece)
    {
        QPropertyAnimation *animation = new QPropertyAnimation(piece, "opacity");
        animation->setDuration(1000);

        animation->setStartValue(1);
        animation->setEndValue(0);

        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void CheckersView::promotePiece(int row, int col, int promoteTo)
{
    PieceGraphicsItem *piece = pieceAtPos(m_selected_piece_row, m_selected_piece_col);
    if(piece){
        piece->setPiece(promoteTo);
    }
}

void CheckersView::unhighlightAllSquares()
{
    auto all_items = scene->items();
    for(auto item = all_items.begin(); item != all_items.end(); ++item)
    {
        if(*item == nullptr)
            continue;
        BoardSquare *sq = dynamic_cast<BoardSquare*>(*item);
        if(sq)
            sq->unhighlight();
        else{
            PieceGraphicsItem *piece = dynamic_cast<PieceGraphicsItem*>(*item);
            if(piece)
                piece->unhighlight();
        }
    }
}

void CheckersView::emitMoveEvent(int target_row, int target_col)
{
    emit mousePieceMove(m_selected_piece_row, m_selected_piece_col, target_row, target_col);
}

void CheckersView::emitPieceSelectionEvent(int row, int col)
{
    PieceGraphicsItem *piece = pieceAtPos(row, col);
    if(piece)
    {
        char piece_color = piece->pieceColor();
        if((piece_color == CheckersGame::WHITE && (m_active_player == CheckersGame::BLACK_PLAYER)) ||
            (piece_color == CheckersGame::BLACK && (m_active_player == CheckersGame::WHITE_PLAYER)))
            return;
    }
    m_selected_piece_row = row;
    m_selected_piece_col = col;
    emit pieceSelected(row,col);
}
