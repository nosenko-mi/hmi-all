#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "RenderArea.h"

#include <QMainWindow>
#include <qpushbutton.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleButtonClick();
    void handleClearButtonClick();
    void handleStyleChange(int index);
    void handleColorChange(int index);
    void handleWidthChange(int value);
    void penChanged();
    // void changePrecision(int decimals);

private:
    RenderArea *renderArea;

    Ui::MainWindow *ui;
    void init();
    void showMessageBox(QString message);
    bool isInputCorrect();
    // void paintEvent(QPaintEvent *);

};
#endif // MAINWINDOW_H
