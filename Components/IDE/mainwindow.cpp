#include <QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow()
{
    setupEditor();

    setCurrentFile(QString());
    // Add tabs and sets them as the central widget
    this->setupTabs();
    createActions();
    createStatusBar();

    readSettings();

    connect(textEdit->document(), &QTextDocument::contentsChanged, this, &MainWindow::documentWasModified);

    #ifndef QT_NO_SESSIONMANAGER
        QGuiApplication::setFallbackSessionManagementEnabled(false);
        connect(qApp, &QGuiApplication::commitDataRequest, this, &MainWindow::commitData);
    #endif

    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::setupTabs()
{
    QTabWidget *tabs = new QTabWidget();
    QWidget *codeTab = new QWidget();
    QWidget *blocklyTab = new QWidget();

    tabs->addTab(codeTab, "Code");
    tabs->addTab(blocklyTab, "Blockly");

    tabs->setTabPosition(QTabWidget::South);

    // Add text edit to "blockly" tab, this will appear when the "code" tab is selected
    this->blockly = new Blockly(this, this->curFile);

    blocklyTab->setLayout(new QVBoxLayout());
    blocklyTab->layout()->addWidget(this->blockly->getWebView());
    blocklyTab->setLayout(blocklyTab->layout());
    connect(tabs, SIGNAL(currentChanged(int)), this, SLOT(onTabChanged(int)));

    // Add text edit to "code" tab, this will appear when the "code" tab is selected
    codeTab->setLayout(new QVBoxLayout());
    codeTab->layout()->addWidget(textEdit);
    codeTab->setLayout(codeTab->layout());

    this->setCentralWidget(tabs);
    this->setLayout(this->layout());
}

void MainWindow::onTabChanged(int tabIndex)
{
    if(tabIndex == 0)
    {
        if(!curFile->isEmpty())
        {
            this->loadFile(*curFile);
        }
    }
}

void MainWindow::setupEditor()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    this->textEdit = new QPlainTextEdit();
    this->textEdit->setFont(font);

    highlighter = new Highlighter(this->textEdit->document());

    QFile file("mainwindow.h");
    if(file.open(QFile::ReadOnly | QFile::Text))
    {
        this->textEdit->setPlainText(file.readAll());
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybeSave())
    {
        writeSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    if(maybeSave())
    {
        textEdit->clear();
        setCurrentFile(QString());
    }
}

void MainWindow::open()
{
    if(maybeSave())
    {
        QString fileName = QFileDialog::getOpenFileName(this);
        if(!fileName.isEmpty())
        {
            loadFile(fileName);
        }
    }
}

bool MainWindow::save()
{
    if(curFile->isEmpty())
    {
        return saveAs();
    }
    else
    {
        return saveFile(*curFile);
    }
}

bool MainWindow::saveAs()
{
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if(dialog.exec() != QDialog::Accepted)
    {
        return false;
    }
    return saveFile(dialog.selectedFiles().first());
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Application"), tr("This is an IDE for the Brusky programming language."));
}

void MainWindow::documentWasModified()
{
    setWindowModified(textEdit->document()->isModified());
}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&file"));
    QToolBar *fileToolbar = addToolBar(tr("File"));
    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    QAction *newAct = new QAction(newIcon, tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newAct);
    fileToolbar->addAction(newAct);

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    QAction *openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);
    fileToolbar->addAction(openAct);

    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
    QAction *saveAct = new QAction(saveIcon, tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAct);
    fileToolbar->addAction(saveAct);

    const QIcon runIcon = QIcon(":/images/compile.png");
    QAction *runAct = new QAction(runIcon, tr("&Compile code..."), this);
    runAct->setShortcuts(QKeySequence::Preferences);
    runAct->setStatusTip(tr("Compile code"));
    connect(runAct, &QAction::triggered, this, &MainWindow::run);
    fileMenu->addAction(runAct);
    fileToolbar->addAction(runAct);

    const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
    QAction *saveAsAct = fileMenu->addAction(saveAsIcon, tr("Save &As..."), this, &MainWindow::saveAs);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));

    fileMenu->addSeparator();

    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    QToolBar *editToolBar = addToolBar(tr("Edit"));
#ifndef QT_NO_CLIPBOARD
    const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(":/images/cut.png"));
    QAction *cutAct = new QAction(cutIcon, tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, &QAction::triggered, textEdit, &QPlainTextEdit::cut);
    editMenu->addAction(cutAct);
    editToolBar->addAction(cutAct);

    const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon(":/images/copy.png"));
    QAction *copyAct = new QAction(copyIcon, tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, &QAction::triggered, textEdit, &QPlainTextEdit::copy);
    editMenu->addAction(copyAct);
    editToolBar->addAction(copyAct);

    const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon(":/images/paste.png"));
    QAction *pasteAct = new QAction(pasteIcon, tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, &QAction::triggered, textEdit, &QPlainTextEdit::paste);
    editMenu->addAction(pasteAct);
    editToolBar->addAction(pasteAct);

    menuBar()->addSeparator();

#endif // !QT_NO_CLIPBOARD

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));


    QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));

#ifndef QT_NO_CLIPBOARD
    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
    connect(textEdit, &QPlainTextEdit::copyAvailable, cutAct, &QAction::setEnabled);
    connect(textEdit, &QPlainTextEdit::copyAvailable, copyAct, &QAction::setEnabled);
#endif // !QT_NO_CLIPBOARD
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if(geometry.isEmpty())
    {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
    else
    {
        restoreGeometry(geometry);
    }
}

void MainWindow::writeSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
}

bool MainWindow::maybeSave()
{
    if(!textEdit->document()->isModified())
    {
        return true;
    }
    const QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("Application"), tr("The document has been modified. \n Do you want to keep your changes?"),
                                                                 QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch(ret)
    {
        case QMessageBox::Save:
            return save();
        case QMessageBox::Cancel:
            return false;
        default:
            break;
    }
    return true;
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1 : \n%2.").arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
    #ifndef QT_NO_CURSOR
        QApplication::setOverrideCursor(Qt::WaitCursor);
    #endif
        textEdit->setPlainText(in.readAll());
    #ifndef QT_NO_CURSOR
        QApplication::restoreOverrideCursor();
    #endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"), tr("Cannot write file %1:\n%2.").arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << textEdit->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("file saved"), 2000);
    return true;
}

bool MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = new QString(fileName);
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = *curFile;
    if(curFile->isEmpty())
    {
        shownName = "untitled.txt";
    }
    setWindowFilePath(shownName);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::run()
{
    this->save();
    // Generate C file
    QProcess process;
    process.setStandardOutputFile("output.c");
    process.setStandardInputFile(*curFile);
    process.start("Brusky");
    process.waitForFinished();
    // Format C File
    process.setStandardOutputFile("output_formatted.c");
    QStringList arguments;
    arguments << "-st" << "-bap" << "-bli0" << "-i4" << "-l79" << "-ncs" << "-npsl" << "-fca" << "-lc79" << "-ts4" << "output.c";
    process.start("indent", arguments);
    process.waitForFinished();

}

#ifndef QT_NO_SESSIONMANAGER
void MainWindow::commitData(QSessionManager &manager)
{
    if(manager.allowsInteraction())
    {
        if(!maybeSave())
        {
            manager.cancel();
        }
        else
        {
            if(textEdit->document()->isModified())
            {
                save();
            }
        }
    }
}
#endif


