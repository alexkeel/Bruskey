#include "blockly.h"
#include <QWebEngineProfile>
#include <QFileDialog>

Blockly::Blockly(QMainWindow* parent, QString *textEditor) : QObject(parent)
{
    this->parent = parent;
    this->textEditor = textEditor;
    view = new QWebEngineView(parent);
    view->load(QUrl("file:///home//alex//Bruskey//Components//IDE//index.html"));
    view->show();

    connect(view->page()->profile(), &QWebEngineProfile::downloadRequested, this, &Blockly::downloadRequested);
}

QWebEngineView* Blockly::getWebView()
{
    return this->view;
}

void Blockly::downloadRequested(QWebEngineDownloadItem *item)
{
    if(this->textEditor->isEmpty())
    {
        QFileDialog dialog(parent);
        dialog.setWindowModality(Qt::WindowModal);
        dialog.setAcceptMode(QFileDialog::AcceptSave);
        if(dialog.exec() != QDialog::Accepted)
        {
            return;
        }
        *this->textEditor = dialog.selectedFiles().first();
        item->setPath(dialog.selectedFiles().first());
        item->accept();
    }
    else
    {
        item->setPath(*this->textEditor);
        item->accept();
    }
}
