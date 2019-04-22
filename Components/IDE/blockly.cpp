#include "blockly.h"

Blockly::Blockly(QMainWindow* parent)
{
    view = new QWebEngineView(parent);
    view->load(QUrl("file:///home//alex//Bruskey//Components//IDE//index.html"));
    view->show();
}

QWebEngineView* Blockly::getWebView()
{
    return this->view;
}
