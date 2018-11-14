#include "scanbutton.h"

#include <QPainter>
#include <QPainterPath>
#include <QTimerEvent>
#include <QPropertyAnimation>
#include <QDebug>

ScanButton::ScanButton(QWidget *parent) : QPushButton(parent)
{
    qDebug() << "ScanButton::ScanButton";
    m_varHeight = 0;
    m_timerId = -1;
    m_scanStatus = false;
    m_nSpeed = 100;
    m_add = true;

    connect(this, &ScanButton::clicked, this, &ScanButton::onStart);
}

void ScanButton::onStart()
{
    if (m_scanStatus)
    {
        return;
    }
    //启动定时器
    m_timerId = startTimer(m_nSpeed);
    m_scanStatus = true;
}

void ScanButton::onStop()
{
    killTimer(m_timerId);
    m_timerId = -1;
    m_scanStatus = false;
}

void ScanButton::paintEvent(QPaintEvent *event)
{
    qDebug() << "m_varHeight=" << m_varHeight;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 绘制圆角矩形背景
    QPainterPath circlePath;
    circlePath.addRoundRect(rect(), 15, 15);
    painter.setClipPath(circlePath);
    painter.fillPath(circlePath, QColor(14 , 150 , 254));

//    // 绘制文字
//    painter.setPen(QPen(Qt::white));
//    QFont font("Arail", 25, QFont::Bold, false);
//    painter.setFont(font);
//    painter.drawText(rect(), Qt::AlignCenter, tr("扫描"));

    // 绘制扫描头像
    QPixmap pixmap = QPixmap(":/images/scanhead").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(QRect(rect().center().x()-pixmap.width()/2, rect().center().y()-pixmap.height()/2, pixmap.width(), pixmap.height()), pixmap, pixmap.rect());

    // 渐变效果
    if (m_scanStatus)
    {
        QLinearGradient linearGradient(0, 0, 0, height());
        linearGradient.setColorAt(0, QColor(255,255,255,100));
        linearGradient.setColorAt(1, QColor(255,255,255,0));
        painter.setBrush(linearGradient);
        painter.fillRect(QRect(rect().left(), rect().top(), rect().width(), m_varHeight), linearGradient);
    }
}

void ScanButton::timerEvent(QTimerEvent *event)
{
    qDebug() << "ScanButton::timerEvent";
    // 单向渐变
//    if (m_timerId == event->timerId())
//    {
//        if (m_varHeight > rect().height())
//        {
//            m_varHeight = rect().height()/10;
//        }

//        m_varHeight += rect().height()/10;
//        update();
//    }

    // 双向渐变
    if (m_timerId == event->timerId())
    {
        if (m_varHeight > rect().height())
            m_add = false;

        if (m_varHeight < 0)
            m_add = true;

        if (m_add)
        {
            m_varHeight += rect().height()/10;
        }
        else
        {
            m_varHeight -= rect().height()/10;
        }
        update();
    }
}

