#include <iostream>
#include <map>
#include <stack>
#include <string>
#include "command.h"

extern Variable Variable;
extern CommandManager commandManager;
int Variable::getValue(const std::string& name) const {
    if (variables.count(name) > 0) {
        return variables.at(name);
    }
    return 0; // 默认返回0或者抛出异常，根据实际需求来定
}

void Variable::setValue(const std::string& name, int newValue) {
    variables[name] = newValue;
}
Variable::~Variable(){
    variables.clear();
}

Command::~Command(){}

VariableCommand::VariableCommand(class::Variable& variable, const std::string& variableName, int newValue)
    : variable(variable), variableName(variableName), newValue(newValue){oldValue=0;}

void VariableCommand::execute(){
  //  std::cerr<<variableName<<" -> "<<oldValue<<" -> "<<newValue<<std::endl;
    oldValue = variable.getValue(variableName);
    variable.setValue(variableName, newValue);
}

void VariableCommand::undo(){
    variable.setValue(variableName, oldValue);
}
VariableCommand::~VariableCommand(){}


// 命令管理器类

CommandManager::~CommandManager() {
    while (!undoStack.empty()) {
        delete undoStack.top();
        undoStack.pop();
    }
}

void CommandManager::executeCommand(Command* command) {
    command->execute();
    undoStack.push(command);
}

void CommandManager::undo() {
    if (!undoStack.empty()) {
        Command* command = undoStack.top();
        undoStack.pop();
        command->undo();
        delete command;
    }
}
