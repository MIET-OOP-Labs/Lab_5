#include "myTextBrowser.h"

myTextBrowser::myTextBrowser(QWidget* parent):QTextBrowser(parent) {
}

void myTextBrowser::RedText(QString text){
    auto color = this->textColor();
    this->setTextColor(Qt::red);
    this->append(text);
    this->setTextColor(color);
}
