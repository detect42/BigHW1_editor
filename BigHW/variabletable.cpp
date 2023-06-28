#include "variabletable.h"
#include "command.h"
using namespace std;
extern map<string,int> Map;
extern Variable Variable;
extern CommandManager commandManager;

VariableTable::VariableTable(QWidget *parent)
: QDialog(parent)
{
    setupUi();
    populateTable();
    connect(tableWidget, &QTableWidget::cellChanged, this, &VariableTable::updateVariable);
}

void VariableTable::setupUi() {
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(2);
    tableWidget->setHorizontalHeaderLabels({ "Variable", "Value" });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tableWidget);

    setLayout(layout);
}

void VariableTable::populateTable() {

    tableWidget->setRowCount(Map.size());

    int row = 0;
    for (auto it = Map.begin(); it != Map.end(); ++it) {
        QTableWidgetItem *variableItem = new QTableWidgetItem(QString::fromStdString(it->first));
        QTableWidgetItem *valueItem = new QTableWidgetItem(QString::number(it->second));

        tableWidget->setItem(row, 0, variableItem);
        tableWidget->setItem(row, 1, valueItem);

        ++row;
    }
}

void VariableTable::updateVariable(int row, int column) {
    if (column == 1) {
        QTableWidgetItem *valueItem = tableWidget->item(row, column);
        QTableWidgetItem *variableItem = tableWidget->item(row, column - 1);

        if (valueItem && variableItem) {
            QString variable = variableItem->text();
            int value = valueItem->text().toInt();
            if(value!=Map[variable.toStdString()]){
                commandManager.executeCommand(new VariableCommand(Variable,variable.toStdString() , value));
            }
            Map[variable.toStdString()] = value;

            qDebug() << "Updated Variable:" << variable << "Value:" << value;
        }
    }
}
VariableTable::~VariableTable(){
    delete tableWidget;
}

