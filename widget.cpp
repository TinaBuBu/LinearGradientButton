#include "widget.h"
#include "scanbutton.h"
#include <QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    ScanButton *button = new ScanButton(this);
    button->setFixedSize(100, 100);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(button);

    setLayout(layout);
}

Widget::~Widget()
{

}
