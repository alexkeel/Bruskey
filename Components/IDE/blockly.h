#ifndef BLOCKLY_H
#define BLOCKLY_H

#include <QUrl>
#include <QMainWindow>

#include <QtWebEngine/QtWebEngine>
#include <QtWebEngineWidgets/QWebEngineView>

class Blockly
{
public:
    Blockly(QMainWindow* parent);

    QWebEngineView* getWebView();

private:
    QWebEngineView *view;
};

#endif // BLOCKLY_H
