#include "mainmenuform.h"
#include "ui_mainmenuform.h"
#include "mainwindow.h"

MainMenuForm::MainMenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuForm)
{
    ui->setupUi(this);
    connect(ui->playButton,SIGNAL(clicked()),
            this, SIGNAL(playButtonClicked()));

    connect(ui->settingsButton, SIGNAL(clicked()),
            this, SIGNAL(settingsButtonClicked()));

    connect(ui->exitButton, SIGNAL(clicked()),
            this, SIGNAL(exitButtonClicked()));
}

MainMenuForm::~MainMenuForm()
{
    delete ui;
}


QSize MainMenuForm::sizeHint() const
{
    return QSize(800, 600);
}

QSize MainMenuForm::minimumSizeHint() const
{
    return QSize(0, 0);
}
