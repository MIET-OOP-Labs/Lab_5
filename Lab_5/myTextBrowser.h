#ifndef MYTEXTBROWSER_H
#define MYTEXTBROWSER_H


#include <QTextBrowser>

namespace Ui { class MainWindow; }

class myTextBrowser: public QTextBrowser {
public:
    myTextBrowser(QWidget* parent);
    void RedText(QString text);
};

#endif // MYTEXTBROWSER_H
