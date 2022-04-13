#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gierka.h>
#include <iostream>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    gierka *game = nullptr;
    void updatePlansza();
    int uikolumny=20;
    int uiwiersze=20;

private:
    Ui::MainWindow *ui;
    void init();
    QTimer *timer = nullptr;

public slots:
    void updatepl();

private slots:
    void on_krok_clicked();
    void on_losuj_clicked();
    void on_wczytaj_clicked();
    void on_zapisz_clicked();
    void on_spinWiersze_valueChanged(int arg1);
    void zmienWiersze(int);
    void zmienKolumny(int);
    void on_spinKolumny_valueChanged(int arg1);
    void on_spinSekundy_valueChanged(int arg1);
    void on_playButton_clicked();
    void onTimeout();

    void on_pauseButton_clicked();
    void on_stopButton_clicked();
};
#endif // MAINWINDOW_H
