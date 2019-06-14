#ifndef GAMEFORM_H
#define GAMEFORM_H

#include "checkersgame.h"
#include <QPointer>
#include <QWidget>

namespace Ui {
class GameForm;
}

class GameForm : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QPointer<CheckersGame> game READ game WRITE setGame)

public:
    explicit GameForm(QWidget *parent = nullptr);
    ~GameForm();
    void drawBoard();
    QPointer<CheckersGame> game() {return m_game;}
    void setGame(CheckersGame* game);

public slots:
    void manageInfoLabel(bool activePlayer);
    void setWhiteName(const QString name);
    void setBlackName(const QString name);
    void endGame(bool winner);

signals:
    void menuButtonClicked();

private:
    Ui::GameForm *ui;
protected:
    QPointer<CheckersGame> m_game;
};

#endif // GAMEFORM_H
