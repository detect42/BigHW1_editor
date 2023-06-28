#include "texteditor.h"
using namespace std;
extern map<string,int> Map;
bool OK=0;
extern bool EverythingOK=0;

extern Variable Variable;
extern CommandManager commandManager;

TextEditor::TextEditor(QWidget *parent) : QMainWindow(parent) {
    resize(800, 600);
    textEdit = new QTextEdit(this);
    textEdit->setFontPointSize(22);
    setCentralWidget(textEdit);

    // 创建状态栏并设置给主窗口
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    // 在状态栏中显示文本
    statusBar->showMessage("Edit status");


    // 创建菜单栏
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // 创建文件菜单
    QMenu *fileMenu = menuBar->addMenu("File");
    // 创建 Save 动作
    QAction *saveAction = new QAction("Save", this);
    fileMenu->addAction(saveAction);
    // 创建 Open 动作
    QAction *openAction = new QAction("Open", this);
    fileMenu->addAction(openAction);
    // 连接 Save 和 Open 动作的信号与槽
    connect(saveAction, &QAction::triggered, this, &TextEditor::saveFile);
    connect(openAction, &QAction::triggered, this, &TextEditor::openFile);

    //编辑调试模式
    QMenu *modeMenu = menuBar->addMenu("Mode");
    // 创建编辑模式动作
    editModeAction = new QAction("Edit Mode", this);
    modeMenu->addAction(editModeAction);
    // 创建调试模式动作
    debugModeAction = new QAction("Debug Mode", this);
    modeMenu->addAction(debugModeAction);
    // 默认为编辑模式
    editModeAction->setCheckable(true);
    editModeAction->setChecked(true);
    // 连接动作的信号与槽
    connect(editModeAction, &QAction::triggered, this, &TextEditor::switchToEditMode);
    // 设置断开连接的信号与槽
    connect(debugModeAction, &QAction::triggered, this, &TextEditor::switchToDebugMode);
    //connect(debugModeAction, &QAction::triggered, this, &TextEditor::disconnectEditMode);

    debugModeButton = new QAction("Debug", this);
    menuBar->addAction(debugModeButton);
    debugModeButton->setVisible(false);
    showdata=new QAction("show data",this);
    menuBar->addAction(showdata);
    showdata->setVisible(false);
    undoButton=new QAction("undo",this);
    menuBar->addAction(undoButton);
    undoButton->setVisible(false);

    table=new VariableTable();

    //编辑状态下随时高亮
    connect(textEdit, &QTextEdit::textChanged, this, &TextEditor::highlightLines);
}

bool TextEditor::iseverythingOK(){
    return EverythingOK;
}
void TextEditor::switchToEditMode() {
    statusBar->showMessage("Edit status");
    disconnect(debugModeButton, &QAction::triggered,this,&TextEditor::SendWarning);
    textEdit->setReadOnly(false);
    editModeAction->setChecked(true);
    debugModeAction->setChecked(false);
    QMessageBox::information(this, "Mode", "Switched to Edit Mode.");
    debugModeButton->setVisible(false);
    showdata->setVisible(false);
    undoButton->setVisible(false);
    clearHighlight();Map.clear();
    // 建立连接
    connect(textEdit, &QTextEdit::textChanged, this, &TextEditor::highlightLines);
    disconnect(debugModeButton, &QAction::triggered, this, &TextEditor::highlightNextLine);
    disconnect(showdata,&QAction::triggered,this,&TextEditor::ShowData);
    disconnect(undoButton,&QAction::triggered,this,&TextEditor::Undooperation);
}

// 切换到调试模式
void TextEditor::switchToDebugMode() {
    statusBar->showMessage("Debug status");
    if(iseverythingOK()){
        nowline=0;
        totalLines = textEdit->document()->blockCount();
        textEdit->setReadOnly(true);
        editModeAction->setChecked(false);
        debugModeAction->setChecked(true);
        QMessageBox::information(this, "Mode", "Switched to Debug Mode.");
        debugModeButton->setVisible(true);
        connect(debugModeButton, &QAction::triggered, this, &TextEditor::highlightNextLine);
        showdata->setVisible(true);
        connect(showdata,&QAction::triggered,this,&TextEditor::ShowData);
        undoButton->setVisible(true);
        connect(undoButton,&QAction::triggered,this,&TextEditor::Undooperation);
        clearHighlight();Map.clear();
        // 断开连接
        disconnect(textEdit, &QTextEdit::textChanged, this, &TextEditor::highlightLines);
    }
    else{
         QMessageBox::warning(this, "Mode", "Cannot switch to Debug Mode. Expression syntax error");
    }

}
// 文本改变处理槽函数
/* void handleTextChanged() {
    QMessageBox::information(this, "Text Changed", "Text has been changed.");
}*/

// 编辑模式下断开连接的槽函数
/*void disconnectEditMode() {
    disconnect(textEdit, &QTextEdit::textChanged, this, &TextEditor::highlightLines);
}
*/
void TextEditor::Undooperation(){
    commandManager.undo();
    for (auto it = Map.begin(); it != Map.end(); ++it) {
        if(Variable.getValue(it->first)!=it->second){
            it->second=Variable.getValue(it->first);
        }
    }
    UpdateData();
}
void TextEditor::ShowData(){
   // table->resize(400,600);
    table->tableWidget->clear();
    table->populateTable();
    table->show();
    QCoreApplication::processEvents();

}
void TextEditor::UpdateData(){
    table->tableWidget->clear();
    table->populateTable();
   // table->show();
    QCoreApplication::processEvents();
}
void TextEditor::highlightNextLine(){

    QTextBlock block = textEdit->document()->findBlockByNumber(nowline);
    nowline++;
    clearHighlight();
    qDebug()<<block.text();
    if (block.isValid())
    {
        QTextCursor nextCursor(block);
        nextCursor.select(QTextCursor::LineUnderCursor);
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(Qt::yellow);
        selection.cursor = nextCursor;
        highlightSelections.append(selection);
        textEdit->setExtraSelections(highlightSelections);
    }

    string content = block.text().toStdString();
    Execute(content);
    UpdateData();
    if(totalLines==nowline){
        disconnect(debugModeButton, &QAction::triggered, this, &TextEditor::highlightNextLine);
        connect(debugModeButton, &QAction::triggered,this,&TextEditor::SendWarning);
    }
}
void TextEditor::clearHighlight()
{
    highlightSelections.clear();
    textEdit->setExtraSelections(highlightSelections);
}

void TextEditor::highlightLines() {
    textEdit->setFontPointSize(22);
    Map.clear();
    QString text = textEdit->toPlainText();
    QTextCursor cursor(textEdit->document());
    EverythingOK=true;
    QList<QTextEdit::ExtraSelection> extraSelections;
    while (!cursor.atEnd()) {
        cursor.select(QTextCursor::LineUnderCursor);
        QString line = cursor.selectedText();
        string content = line.toStdString();

        if (isvaild(content)) {
            QTextEdit::ExtraSelection selection;
            selection.format.setBackground(Qt::red);
            selection.cursor = cursor;
            extraSelections.append(selection);
            if(content!="") EverythingOK=false;
        }

        cursor.movePosition(QTextCursor::NextBlock);
    }

    textEdit->setExtraSelections(extraSelections);
}
// 保存文件槽函数
void TextEditor::saveFile() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", QString(), "Text Files (*.txt)");

    if (!filePath.isEmpty()) {
        QFile file(filePath);

        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << textEdit->toPlainText();
            file.close();

            QMessageBox::information(this, "Save", "File saved successfully.");
        } else {
            QMessageBox::warning(this, "Save", "Failed to save file.");
        }
    }
}

// 打开文件槽函数
void TextEditor::openFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", QString(), "Text Files (*.txt)");

    if (!filePath.isEmpty()) {
        QFile file(filePath);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            textEdit->setPlainText(in.readAll());
            file.close();

            QMessageBox::information(this, "Open", "File opened successfully.");
        } else {
            QMessageBox::warning(this, "Open", "Failed to open file.");
        }
    }
}
void TextEditor::SendWarning(){
    QMessageBox::warning(this, "Warning", "There is nothing remaining");
}

