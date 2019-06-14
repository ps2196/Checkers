#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "checkersgame.h"
#include "checkersview.h"
#include "gameform.h"
#include "mainmenuform.h"
#include "settingsform.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MainMenuForm *menuForm;
    SettingsForm *settingsForm;
    GameForm *gameForm;
    CheckersGame *m_game;
protected slots:
    void showSettingsForm();
    void showMenuForm();
    void connectMenuSignals();
    void connectSettingsSignals();
    void showBoard();
    void applySettings(const QString, const QString);
};

#endif // MAINWINDOW_H
