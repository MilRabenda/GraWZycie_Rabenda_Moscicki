#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer(new QTimer(this))
{
    ui->setupUi(this);
    game = new gierka();

    connect(game,SIGNAL(aktualizuj()),this,SLOT(updatepl()));
    connect(game,SIGNAL(changeWiersze(int)),this,SLOT(zmienWiersze(int)));
    connect(game,SIGNAL(changeKolumny(int)),this,SLOT(zmienKolumny(int)));
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeout()));

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::init(){
    QPixmap pixmap("play.png");
    QIcon ButtonIcon(pixmap);
    ui->playButton->setIcon(ButtonIcon);
    ui->playButton->setIconSize(QSize(50,50));

    QPixmap pixmap2("pause.png");
    QIcon ButtonIcon2(pixmap2);
    ui->pauseButton->setIcon(ButtonIcon2);
    ui->pauseButton->setIconSize(QSize(50,50));

    QPixmap pixmap3("stop.png");
    QIcon ButtonIcon3(pixmap3);
    ui->stopButton->setIcon(ButtonIcon3);
    ui->stopButton->setIconSize(QSize(50,50));



    timer->setInterval(ui->spinSekundy->value());

    ui->plansza_gry->setDisabled(true);
    ui->plansza_gry->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->plansza_gry->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->plansza_gry->horizontalHeader()->hide();
    ui->plansza_gry->verticalHeader()->hide();
    game->resize(15,15);
    ui->spinWiersze->setValue(game->wiersze);
    ui->spinKolumny->setValue(game->kolumny);
    game->losowe();
    updatePlansza();
}

void MainWindow::updatePlansza(){

    ui->plansza_gry->setRowCount(game->wiersze);
    ui->plansza_gry->setColumnCount(game->kolumny);

    ui->plansza_gry->resizeColumnsToContents();
    ui->plansza_gry->resizeRowsToContents();

    int w = 0; // verticalHeader()->width()
    int h = 0; // horizontalHeader()->height()
    for ( int i = 0; i < ui->plansza_gry->rowCount(); i++ )
    {
        h += ui->plansza_gry->rowHeight( i );
    }
    for ( int j = 0; j < ui->plansza_gry->columnCount(); j++ )
    {
        w += ui->plansza_gry->columnWidth( j );
    }
    ui->plansza_gry->setFixedSize( w, h );

    for (int i=0; i<uiwiersze; i++ ) {
            for (int j=0; j<uikolumny; j++) {
                ui->plansza_gry->setItem(i, j, new QTableWidgetItem);
                game->plansza[i][j] ? ui->plansza_gry->item(i,j)->setBackground(Qt::black) : ui->plansza_gry->item(i,j)->setBackground(Qt::white);
            }
        }

}
void MainWindow::updatepl(){

    uikolumny=game->kolumny;
    uiwiersze=game->wiersze;

}



void MainWindow::on_krok_clicked()
{
    game->nextIter();
    updatePlansza();
}


void MainWindow::on_losuj_clicked()
{
    game->losowe();
    updatePlansza();
    ui->playButton->setDisabled(false);
    ui->pauseButton->setDisabled(false);
    ui->krok->setDisabled(false);
}


void MainWindow::on_wczytaj_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open Saved Game","","Games (*.txt)");
    game->wczytaj(fileName);
    updatePlansza();
}

void MainWindow::on_zapisz_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save Game","","Games (*.txt)");
    game->zapisz(fileName);
    updatePlansza();
}

void MainWindow::on_spinWiersze_valueChanged(int arg1)
{
    game->resize(arg1,game->kolumny);
    updatePlansza();
}

void MainWindow::zmienWiersze(int w){
    ui->spinWiersze->setValue(w);
}
void MainWindow::zmienKolumny(int w){
    ui->spinKolumny->setValue(w);
}

void MainWindow::on_spinKolumny_valueChanged(int arg1)
{
    game->resize(game->wiersze,arg1);
    updatePlansza();
}

void MainWindow::on_spinSekundy_valueChanged(int arg1)
{
    timer->setInterval(arg1);
}

void MainWindow::on_playButton_clicked()
{
    timer->start();
}
void MainWindow::onTimeout(){
    game->nextIter();
    updatePlansza();
}

void MainWindow::on_pauseButton_clicked()
{
    timer->stop();
}

void MainWindow::on_stopButton_clicked()
{
    timer->stop();
    game->clear();
    updatePlansza();
    ui->playButton->setDisabled(true);
    ui->pauseButton->setDisabled(true);
    ui->krok->setDisabled(true);

}




