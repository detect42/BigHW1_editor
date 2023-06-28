#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <map>
#include <stack>
#include <string>

// 变量类
class Variable {
private:
    std::map<std::string, int> variables;
public:

    int getValue(const std::string& name) const;

    void setValue(const std::string& name, int newValue) ;
    ~Variable();
};

// 命令接口
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() =0;
};

// 变量命令类
class VariableCommand : public Command {
private:
    Variable& variable;
    std::string variableName;
    int oldValue;
    int newValue;

public:
    VariableCommand(Variable& variable, const std::string& variableName, int newValue);

    void execute() override;

    void undo() override ;
    ~VariableCommand() override;
};

// 命令管理器类
class CommandManager {
private:
    std::stack<Command*> undoStack;

public:
    ~CommandManager() ;


    void executeCommand(Command* command) ;

    void undo() ;
};
#endif // COMMAND_H
