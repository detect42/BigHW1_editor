#ifndef VARIABLETABLE_H
#define VARIABLETABLE_H

#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QDebug>
#include <QFile>
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
#include <map>

class VariableTable : public QDialog {
public:
    VariableTable(QWidget *parent = nullptr);

    QTableWidget *tableWidget;
    void setupUi();

    void populateTable();

    void updateVariable(int row, int column);
    ~VariableTable();
};


#endif // VARIABLETABLE_H
