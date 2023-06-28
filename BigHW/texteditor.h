#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H


#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QDebug>
#include <QFile>
#include "Statement.h"
#include <iostream>
#include <QTextStream>
#include <QDir>
#include <stdio.h>
#include <QString>
#include <QDataStream>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QPushButton>
#include <QTextEdit>
#include <QFileDialog>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTextBlock>
#include <QTableWidget>
#include<QVBoxLayout>
#include "variabletable.h"
using namespace std;

class TextEditor : public QMainWindow {
public:
    TextEditor(QWidget *parent = nullptr);

    // 切换到调试模式
    void switchToDebugMode();
    void switchToEditMode();
    bool iseverythingOK();

    void Undooperation();
    void ShowData();
    void UpdateData();
    void highlightNextLine();
    void clearHighlight();
    void highlightLines();
    // 保存文件槽函数
    void saveFile();
    // 打开文件槽函数
    void openFile();
    void SendWarning();

private:
    QTextEdit *textEdit;
    QAction *editModeAction;
    QAction *debugModeAction;
    QAction *debugModeButton;
    QAction *showdata;
    QAction *undoButton;
    QStatusBar* statusBar;
    int nowline,totalLines;
    QList<QTextEdit::ExtraSelection> highlightSelections;
    VariableTable *table;
};

#endif // TEXTEDITOR_H
