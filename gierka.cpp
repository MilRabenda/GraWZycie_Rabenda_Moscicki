#include "gierka.h"
#include <QDebug>


gierka::gierka()
{
    init();
    resize(25,25);
    losowe();
}

void gierka::setKol(int cols){
    kolumny=cols;
}

void gierka::setWie(int rows){
    wiersze=rows;
}

void gierka::setSize(int rows, int cols){
    setWie(rows);
    setKol(cols);
}

void gierka::init(){
    for(int w = 0; w < wiersze; w++){
        QVector<bool> temp;
        for(int k=0; k < kolumny; k++){
            temp.push_back(false);
        }
        plansza.push_back(temp);
    }
}

void gierka::resize(int rows, int cols){

    if(rows>wiersze||cols>kolumny){
        auto temp = plansza;
        plansza=QVector<QVector<bool>>(rows,QVector<bool>(cols));
        for(int i=0;i<wiersze;i++){
            for(int j=0;j<kolumny;j++){
                plansza[i][j]=temp[i][j];
            }
        }
    }else if(rows<wiersze){
        auto xd = wiersze-rows;
        for(int i=0; i<xd;i++){
            plansza.pop_back();
        }
    }else if(cols<kolumny){
        auto xd = kolumny-cols;
        for(auto v : plansza){
            for(int i =0; i<xd;i++){
                v.pop_back();
            }
        }
    }
    wiersze=rows;
    kolumny=cols;
    emit aktualizuj();

}

void gierka::losowe(){
    for(int w=0; w<wiersze;w++){
        for(int k=0; k<kolumny;k++){
            std::random_device rand;
            int help = rand()%100;
            help>=70 ? plansza[w][k]=true : plansza[w][k]=false;
            //70% szans na komórkę martwą, 30 na żywą
        }
    }
}

void gierka::nextIter(){

    auto druga = plansza;
    for(int w=0; w<wiersze; w++){
        for(int k=0; k<kolumny;k++){
            int count = 0;
            for(int i=-1;i<2;i++){
                for(int j=-1;j<2;j++){
                    if(w+i>=0&&w+i<wiersze&&k+j>=0&&k+j<kolumny){
                        if(plansza[w+i][k+j]) ++count;
                    }
                }
            }
            if(plansza[w][k]) count--;
            if(plansza[w][k]==false&&count==3)druga[w][k]=true;
            if(plansza[w][k]&&!(count==2||count==3)) druga[w][k]=false;
        }
    }
    plansza=druga;
    emit aktualizuj();
}

void gierka::zapisz(QString src){
    std::string a = src.toStdString();
    plik.open(a,ios::out | ios::trunc);
    plik << wiersze << ";" <<kolumny<<";";
    plik.close();
    plik.open(a, ios::out | ios::app);
    for(int w = 0; w < wiersze; w++){
        for(int k=0; k < kolumny; k++){
            plik << plansza[w][k] << ";";
        }
    }
    plik.close();
}

void gierka::wczytaj(QString src){

    std::string a = src.toStdString();

    plik.open(a, ios::in);
    int ilewierszy, ilekolumn;
    char znak;
    plik >> ilewierszy >> znak >> ilekolumn >> znak;
    emit changeKolumny(ilekolumn);
    emit changeWiersze(ilewierszy);
    auto temp = QVector<QVector<bool>>(ilewierszy,QVector<bool>(ilekolumn));
    for(int w=0; w < ilewierszy; w++){
        for(int k=0; k < ilekolumn;k++){
            int cos;
            plik >> cos >> znak;
            temp[w][k] = cos;
        }
    }
    plansza=temp;
    plik.close();
    emit aktualizuj();
}

void gierka::clear(){
    for(int w=0; w<wiersze;w++){
        for(int k=0; k<kolumny;k++){
            plansza[w][k]=false;
        }
    }
}
