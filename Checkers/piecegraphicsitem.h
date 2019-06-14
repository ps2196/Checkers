#ifndef PIECEGRAPHICSITEM_H
#define PIECEGRAPHICSITEM_H

#include <QPointer>
#include <QGraphicsObject>
#include <iostream>

class PieceGraphicsItem : public QGraphicsObject
{
   Q_OBJECT
private:
    int m_piece;
    bool m_highlight;
public:
    PieceGraphicsItem(QGraphicsItem *parent = nullptr): QGraphicsObject(parent)
    { m_highlight = false; m_piece=0;}

    PieceGraphicsItem(int piece, QGraphicsItem *parent = nullptr): QGraphicsObject(parent)
    {
        m_piece = piece;
        m_highlight = false;
    }

    int piece() const {return m_piece;}
    void setPiece(int piece){m_piece = piece; update();}

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void highlight();
    void unhighlight();
    char pieceColor() const;
signals:
    void selected(int row, int col);
protected:
     virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override
    {
        int row = (int) (y()/100 );
        int col = (int)( x()/100 );
        emit selected(row, col);
    }

};

#endif // PIECEGRAPHICSITEM_H
