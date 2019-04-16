#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSessionManager>
#include <QPlainTextEdit>
#include "highlighter.h"
#include "blockly.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    void loadFile(const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void run();
    void about();
    void documentWasModified();
    #ifndef QT_NO_SESSIONMANAGER
        void commitData(QSessionManager &);
    #endif

private:
    void setupEditor();
    void setupTabs();
    void setupFileMenu();
    void setupHelpMenu();
    void createActions();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    bool saveFile(const QString &fileName);
    bool setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    Blockly *blockly;
    QPlainTextEdit *textEdit;
    QString curFile;
    Highlighter *highlighter;

};

#endif // MAINWINDOW_H

