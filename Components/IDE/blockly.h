#ifndef BLOCKLY_H
#define BLOCKLY_H

#include <QUrl>
#include <QMainWindow>

#include <QtWebEngine/QtWebEngine>
#include <QtWebEngineWidgets/QWebEngineView>

class Blockly : public QObject
{
    Q_OBJECT

public:
    Blockly(QMainWindow* parent, QString* textEditor);

    QWebEngineView* getWebView();

private slots:
    void downloadRequested(QWebEngineDownloadItem* item);

private:
    QString *textEditor;
    QWebEngineView *view;
    QMainWindow *parent;
};

#endif // BLOCKLY_H
