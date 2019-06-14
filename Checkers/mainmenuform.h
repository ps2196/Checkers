#ifndef MAINMENUFORM_H
#define MAINMENUFORM_H

#include <QWidget>

namespace Ui {
class MainMenuForm;
}

class MainMenuForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuForm(QWidget *parent = nullptr);
    ~MainMenuForm();

protected:
    virtual QSize sizeHint() const;
    virtual QSize minimumSizeHint() const;
private slots:

signals:
    void playButtonClicked();
    void settingsButtonClicked();
    void exitButtonClicked();
private:
    Ui::MainMenuForm *ui;
};

#endif // MAINMENUFORM_H
