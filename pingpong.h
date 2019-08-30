#ifndef PINGPONG_H
#define PINGPONG_H

#include <QFrame>
#include <QPropertyAnimation>
#include <QWidget>

class Ball : public QWidget {
    Q_OBJECT
public:
    using QWidget::QWidget;

    float radius() const;
    void setRadius(float radius);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    void paintEvent(QPaintEvent *event) override;
    float m_radius;
};

class Slider : public QWidget {
    Q_OBJECT
public:
    using QWidget::QWidget;

private:
    void paintEvent(QPaintEvent *event) override;
};

class PingPongTable : public QFrame {
    Q_OBJECT
public:
    PingPongTable(QWidget *parent = nullptr);
    int score() const;

signals:
    void scoreChanged();

private:
    Ball m_ball;
    Slider m_slider;
    QPropertyAnimation m_anim;

    int m_score;

    void keyPressEvent(QKeyEvent *event) override;
};

#endif // PINGPONG_H
