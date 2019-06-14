#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H

#include <QGraphicsObject>

class BoardSquare : public QGraphicsObject
{
    Q_OBJECT
private:
    QColor  m_color;
    qreal m_size;
    bool m_highlight;

public:
    BoardSquare(QColor, qreal);
    QColor color() {return m_color;}
    void setColor(QColor color){ m_color = color;}
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    qreal size() {return m_size;}
    void setSize(qreal size) {m_size = size;}
    void highlight();
    void unhighlight();

private:
    QColor highlightColor();

signals:
    void selected(int row, int col);

protected:
     virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override;
};

#endif // BOARDSQUARE_H
