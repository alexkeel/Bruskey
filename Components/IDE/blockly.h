#ifndef BLOCKLY_H
#define BLOCKLY_H

#include <QtWebKitWidgets/QWebView>
#include <QUrl>
#include <QMainWindow>

class Blockly
{
public:
    Blockly(QMainWindow* parent);

    QWebView* getWebView();

private:
    QWebView *webView;
};

#endif // BLOCKLY_H
