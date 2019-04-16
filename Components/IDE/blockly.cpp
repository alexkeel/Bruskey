#include "blockly.h"

Blockly::Blockly(QMainWindow* parent)
{
    this->webView = new QWebView(parent);
    this->webView->setGeometry(0, 0, 200, 200);
    this->webView->load(QUrl("file:///home/alex/Bruskey/Components/IDE/google-blockly/demos/fixed/index.html"));
}

QWebView* Blockly::getWebView()
{
    return this->webView;
}
