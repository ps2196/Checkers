#include "boardsquare.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <iostream>

BoardSquare::BoardSquare(QColor color, qreal size)
{
    m_color = color;
    m_highlight = false;
    m_size = size;
}

QRectF BoardSquare::boundingRect() const
{
    return QRectF(0, 0, m_size, m_size);
}

void BoardSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QColor color = m_highlight ? highlightColor() : m_color;
    painter->setBrush(color);
    painter->drawRect(0, 0, static_cast<int>(m_size), static_cast<int>(m_size));
}

void BoardSquare::unhighlight()
{
    m_highlight = false;
    update();
}

void BoardSquare::highlight()
{
    m_highlight = true;
    update();
}


QColor BoardSquare::highlightColor()
{// mix m_color with red
    return QColor(255* (0.25) + m_color.red()*0.75,
                  m_color.green()*0.75,
                  m_color.blue()*0.75,
                  255);
}

void BoardSquare::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    if(!m_highlight)
        return; // Only highlited squares are available for selection as move target
    int row = static_cast<int>(y()/100 );
    int col = static_cast<int>( x()/100 );
    emit selected(row, col);
}
