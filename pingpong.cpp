#include "pingpong.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QtDebug>
#include <cmath>

void Ball::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setPen(Qt::transparent);
    p.setBrush(QBrush(Qt::black));
    p.setRenderHint(QPainter::RenderHint::Antialiasing);
    p.drawEllipse(event->rect());
    event->accept();
}

float Ball::radius() const { return m_radius; }

void Ball::setRadius(float radius) { m_radius = radius; }

QSize Ball::sizeHint() const { return minimumSizeHint(); }

QSize Ball::minimumSizeHint() const {
    auto r = std::ceil(m_radius * 2);
    return QSize(r, r);
}

PingPongTable::PingPongTable(QWidget *parent)
    : QFrame(parent), m_ball(this), m_slider(this), m_score(0) {
    m_ball.setRadius(18);

    m_slider.setGeometry(0, 0, 10, 100);

    m_anim.setTargetObject(&m_ball);
    m_anim.setPropertyName("pos");
    m_anim.setDuration(1400);

    m_anim.setStartValue(QPoint(0, 0));
    m_anim.setEndValue(QPoint(width() - m_ball.width(), rand() % height()));

    connect(&m_anim, &QPropertyAnimation::finished, [&]() {
        m_anim.setStartValue(m_ball.pos());
        if (m_ball.x() != 0) {
            m_anim.setEndValue(
                QPoint(0, rand() % (height() - m_ball.height())));
        } else {
            m_anim.setEndValue(QPoint(width() - m_ball.width(),
                                      rand() % (height() - m_ball.height())));

            if (m_ball.y() >= m_slider.y() && m_ball.y() <= m_slider.y() + m_slider.height())  {
                m_score++;
            } else {
                m_score = 0;
            }
            emit scoreChanged();
        }
        m_anim.start();
    });

    m_anim.start();
}

int PingPongTable::score() const
{
    return m_score;
}

void PingPongTable::keyPressEvent(QKeyEvent *event) {
    auto k = event->key();
    event->accept();

    if (k == Qt::Key_Down) {
        m_slider.move(m_slider.x(),
                      std::min(m_slider.y() + 10, height() - m_slider.height()));
    } else if (k == Qt::Key_Up) {
        m_slider.move(m_slider.x(), std::max(m_slider.y() - 10, 0));
    }
}

void Slider::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setBrush(QBrush(Qt::black));
    p.drawRect(event->rect());
    event->accept();
}
