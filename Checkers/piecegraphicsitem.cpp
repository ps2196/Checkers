#include "checkersgame.h"
#include "piecegraphicsitem.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <checkersboard.h>


QRectF PieceGraphicsItem::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void PieceGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(!m_piece)
        return;
    QColor color = (m_piece == CheckersBoard::BLACK_PAWN || m_piece == CheckersBoard::BLACK_QUEEN  ) ?
                    Qt::black : Qt::white;
    painter->setBrush(color);
    QPen pen(m_highlight ? Qt::yellow:Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen);
    painter->drawEllipse(10, 10, 80, 80);
    if(m_piece == CheckersBoard::WHITE_QUEEN || m_piece == CheckersBoard::BLACK_QUEEN)
    {
        painter->setBrush(Qt::red);
        painter->drawEllipse(30,30,40,40);
    }
}

void PieceGraphicsItem::highlight()
{
    m_highlight = true;
}

void PieceGraphicsItem::unhighlight()
{
    m_highlight = false;
}

char PieceGraphicsItem::pieceColor() const
{
    if(m_piece == CheckersBoard::WHITE_PAWN || m_piece == CheckersBoard::WHITE_QUEEN)
        return CheckersGame::WHITE;
    return CheckersGame::BLACK;
}
