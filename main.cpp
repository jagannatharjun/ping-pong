#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#include "pingpong.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QWidget w;
    QVBoxLayout l(&w);
    w.setLayout(&l);

    PingPongTable table;
    l.addWidget(&table, 10);
    table.setStyleSheet("border: 1px solid darkgrey");

    QHBoxLayout l2;
    l.addLayout(&l2, 1);

    QLabel high;
    l2.addWidget(&high);
    high.setText("High Score: 0");
    high.setStyleSheet("font: 22px \"Courier New\"");

    QLabel score;
    l2.addWidget(&score);
    score.setText("Score: 0");
    score.setStyleSheet("font: 22px \"Courier New\"");
    score.setAlignment(Qt::AlignRight | Qt::AlignCenter);

    QObject::connect(&table, &PingPongTable::scoreChanged, [&]() {
        static int previousHighScore = 0;
        score.setText("Score: " + QString::number(table.score()));
        if (table.score() > previousHighScore) {
            high.setText("High Score: " + QString::number(table.score()));
            previousHighScore = table.score();
        }
    });

    table.setFocus();
    w.resize(800, 450);
    w.show();
    return a.exec();
}
