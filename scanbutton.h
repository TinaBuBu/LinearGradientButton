#ifndef SCANBUTTON_H
#define SCANBUTTON_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QPushButton>

/**************************************************************************
Copyright:
Author:
Date:2018-011-09
Description:自定义按钮

自定义动态线性渐变按钮，当点击按钮时，处于扫描状态，会不断重新绘制自己实现动态线性渐变


**************************************************************************/

class ScanButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ScanButton(QWidget *parent = nullptr);

signals:

public slots:
    void onStart();// 开始扫描
    void onStop();// 停止扫描 可以由外围信号触发

protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);

    int m_varHeight; // 渐变的高度
    int m_timerId;   // 渐变定时器id
    int m_nSpeed;    // 渐变的速度
    int m_scanStatus;// 是否扫描状态
    bool m_add;      // 渐变的高度递增
};
#endif // SCANBUTTON_H
