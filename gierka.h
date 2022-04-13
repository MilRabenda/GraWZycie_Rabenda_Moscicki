#ifndef GIERKA_H
#define GIERKA_H
#include <random>
#include <QVector>
#include <QObject>
#include <fstream>
using namespace std;

class gierka : public QObject
{
    Q_OBJECT
public:
    gierka();
    void resize(int,int);
    void setKol(int);
    void setWie(int);
    void setSize(int, int);
    void init();
    void losowe();
    int wiersze = 20;
    int kolumny = 20;
    QVector<QVector<bool>> plansza;
    void nextIter();
    fstream plik;
    void zapisz(QString);
    void wczytaj(QString);
    void clear();

signals:
    void aktualizuj();
    void changeWiersze(int);
    void changeKolumny(int);

};

#endif // GIERKA_H
