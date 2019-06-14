#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsForm(QWidget *parent = nullptr);
    ~SettingsForm();

signals:
    void cancelButtonClicked();
    void applyButtonClicked(const QString whiteName, const QString blackName);
private slots:


    void on_applyButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H
