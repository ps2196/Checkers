#include "settingsform.h"
#include "ui_settingsform.h"

SettingsForm::SettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);
}

SettingsForm::~SettingsForm()
{
    delete ui;
}


void SettingsForm::on_applyButton_clicked()
{
    QString whiteName = ui->whiteNameLine->text();
    QString blackName = ui->blackNameLine->text();
    emit applyButtonClicked(static_cast<const QString>(whiteName), static_cast<const QString>(blackName));
}

void SettingsForm::on_cancelButton_clicked()
{
    emit cancelButtonClicked();
}
