#include "mainmenuform.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    menuForm = qobject_cast<MainMenuForm*>(ui->stackedWidget->widget(0));
    settingsForm = qobject_cast<SettingsForm*>(ui->stackedWidget->widget(1));
    gameForm = qobject_cast<GameForm*>(ui->stackedWidget->widget(2));
    m_game = nullptr;
    //set handlings for signals from menuForm
    connectMenuSignals();
    connectSettingsSignals();
    connect(gameForm, SIGNAL(menuButtonClicked()),
            this, SLOT(showMenuForm()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showSettingsForm()
{
    //std::cout<<"SHOW SETTINGS\n"<<std::flush;
    ui->stackedWidget->setCurrentWidget(settingsForm);
}

void MainWindow::showMenuForm()
{
    ui->stackedWidget->setCurrentWidget(menuForm);
}

void MainWindow::showBoard()
{
    if (!m_game)
    {
         m_game = new CheckersGame(this);
    }
    m_game->newGame();
    gameForm->setGame(m_game);
    gameForm->drawBoard();
    ui->stackedWidget->setCurrentWidget(gameForm);
}

void MainWindow::applySettings(const QString whiteName, const QString blackName)
{
    if(!whiteName.isEmpty())
        gameForm->setWhiteName(whiteName);
    if(!blackName.isEmpty())
        gameForm->setBlackName(blackName);
    showMenuForm();
}


void MainWindow::connectMenuSignals()
{
    if(!menuForm)
        return;

    connect(menuForm, SIGNAL(playButtonClicked()),
            this, SLOT(showBoard()));
    connect(menuForm, SIGNAL(settingsButtonClicked()),
            this, SLOT(showSettingsForm()));
    connect(menuForm, SIGNAL(exitButtonClicked()),
            this, SLOT(close()));
}

void MainWindow::connectSettingsSignals()
{
   // std::cout<<"CONNECT SETTINGS\n"<<std::flush;
    if(!settingsForm)
        return;

    connect(settingsForm, SIGNAL(applyButtonClicked(const QString, const QString)),
            this, SLOT(applySettings(const QString, const QString)));

    connect(settingsForm, SIGNAL(cancelButtonClicked()),
            this, SLOT(showMenuForm()));
}

