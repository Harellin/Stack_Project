#ifndef PROJECT2_STATE_H
#define PROJECT2_STATE_H

#include<iostream>
#include <map>
#include<vector>
#include <string>
#include "../myStack/myStack.h"

class State {
public:
    bool isgoing = false;
    std::vector<myStack::Stack<int>> stack;
    std::map<std::string, int> registers;
    std::map<std::string, int> functions;
    std::vector<int> position;

    void Start();

    bool isStart();

    void SetPos(int pos);

    void End();

    void Push(int value);

    void Pop();

    int Top();

    int GetReg(std::string reg);

    void WriteReg(std::string reg, int value);

    void PushFunction(std::string function, int pos);

    void GoTo(std::string function);

    void Call(std::string function);

    void Ret();

    bool CanNext(int size);
};

class StateException: std::exception {
public:
    StateException(const char *message){}
    virtual std::string what() {
        return message_;
    }
private:
    std::string message_;
};

#endif //PROJECT2_STATE_H
