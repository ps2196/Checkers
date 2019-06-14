#include "checkerspiece.h"

CheckersPiece::CheckersPiece(QObject *parent) : QObject(parent)
{

}

CheckersPiece::CheckersPiece(const CheckersPiece &other) : QObject()
{
    setParent(other.parent());
    _row = other.row();
    _column = other.column();
    _color = other.color();
    _queen = other.queen();
}

CheckersPiece::CheckersPiece(int row, int column, bool color, bool queen, QObject *parent): QObject(parent)
{
    _row = row;
    _column = column;
    _color = color;
    _queen = queen;
}

bool CheckersPiece::operator==(const CheckersPiece &other) const
{
    return (_row == other.row() && _column == other.column() &&
            _color == other.color() && _queen == other.queen());
}
