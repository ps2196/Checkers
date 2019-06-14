#ifndef CHECKERSVIEW_H
#define CHECKERSVIEW_H

#include "boardsquare.h"
#include "checkersboard.h"
#include "piecegraphicsitem.h"
#include <QGraphicsView>
#include <QPointer>

// Class providing user interface - handles board drawing, forwards user actions to model
class CheckersView : public QGraphicsView
{
    Q_OBJECT
private:
    QPointer<CheckersBoard> _board; //  pointer to an actual board data is derived from
    bool m_active_player;
    QSize _squareSize;
    QGraphicsScene *scene;
    int m_selected_piece_row; int m_selected_piece_col;

public:
    explicit CheckersView(QWidget *parent = nullptr);
    void setBoard(CheckersBoard* board);
    void drawBoard();
    BoardSquare* squareAtPos(int row, int col);
    PieceGraphicsItem* pieceAtPos(int row, int col);


protected slots:

    void emitPieceSelectionEvent(int row, int col);
    void emitMoveEvent(int target_row, int target_col);
signals:
    void pieceSelected(int row, int col);
    void mousePieceMove(int srow, int scol, int trow, int tcol);

public slots:
    void markAvailableMoves(int, int, QList<QPair<int, int>>);
    void movePiece(int srow, int scol, int trow, int tcol);
    void capturePiece(int row, int col);
    void promotePiece(int row, int col, int promoteTo);
    void setActivePlayer(bool activePlayer){m_active_player = activePlayer;}
protected:
    virtual QSize sizeHint() const;
    virtual QSize minimumSizeHint() const;
    void unhighlightAllSquares();
};

#endif // CHECKERSVIEW_H
