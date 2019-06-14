#ifndef CHERCKERSPIECE_H
#define CHERCKERSPIECE_H

#include <QObject>

// Checker piece hold information about a piece and its current position on the board
class CheckersPiece : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool queen READ queen)
    Q_PROPERTY(bool color READ color)
    Q_PROPERTY(int row READ row)
    Q_PROPERTY(int column READ column)
private:
    int _row; int _column;
    bool _queen; bool _color;
public:
    explicit CheckersPiece(QObject *parent = nullptr);
    CheckersPiece(int, int, bool, bool, QObject *parent = nullptr);
    CheckersPiece(const CheckersPiece &other);
    static const bool BLACK = true; static const bool WHITE = false;
    bool operator==(const CheckersPiece& other) const;


signals:

public slots:
    bool queen()const {return _queen;}
    bool color() const {return _color;}
    int row() const {return _row;}
    int column() const{return _column;}
};

#endif // CHERCKERSPIECE_H
