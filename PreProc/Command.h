#ifndef PROJECT2_COMMAND_H
#define PROJECT2_COMMAND_H

#include "State.h"

class Command{
public:
    virtual void execute(State &curState) = 0;
    virtual std::string name() = 0;
};

void Next(std::vector<std::shared_ptr<Command>> & vec_command, State & all) {
    vec_command[all.position.back()] -> execute(all);
    all.position[all.position.size() - 1] += 1;
}

class Begin: public Command{
public:
    virtual void execute(State &curState) override {
        if(curState.isStart()) {
            throw StateException{"The process has already been begun"};
            };
        curState.Start();
    }
    std::string name() override {
        return "BEGIN";
    }
};

class End: public Command{
public:
    virtual void execute(State &curState) override {
        if(!curState.isStart()) {
            throw StateException{"The process has already been ended"};
        }
        curState.End();
    }
    std::string name() override {
        return "END";
    }
};

class Push: public Command{
public:
    int value;
    Push(int value):value(value){}
    virtual void execute(State &curState) override {
        if(!curState.isStart()) {
            throw StateException{"The process has already been begun"};
        }
        curState.Push(value);
    }
    std::string name() override {
        return "PUSH";
    }
};

class Pop: public Command{
public:
    virtual void execute(State &curState) override {
        if(!curState.isStart()) {
            throw StateException{"The process has already been begun"};
        }
        curState.Pop();
    }
    std::string name() override {
        return "POP";
    }
};

class PushR: public Command{
public:
    std::string reg;
    PushR(std::string reg):reg(reg){}
    virtual void execute(State &curState) override {
        if(!curState.isStart()) {
            throw StateException{"The process has already been begun"};
        }
        curState.Push(curState.GetReg(reg));
    }
    std::string name() override {
        return "PUSHR";
    }
};

class PopR: public Command{
public:
    std::string reg;
    PopR(std::string reg):reg(reg){}
    virtual void execute(State &curState) override {
        if(!curState.isStart()) {
            throw StateException{"The process has already been begun"};
        }
        curState.WriteReg(reg, curState.Top());
        curState.Pop();
    }
    std::string name() override {
        return "POPR";
    }
};

class Add: public Command{
public:
    virtual void execute(State &curState) override {
        if(!curState.isStart()) {
            throw StateException{"The process has already been begun"};
        }
        int first = curState.Top();
        curState.Pop();
        int second = curState.Top();
        curState.Pop();
        curState.Push(first+second);
    }
    std::string name() override {
        return "ADD";
    }
};

class Sub: public Command{
public:
    virtual void execute(State &curState) override {
        if(!curState.isStart()) {
            throw StateException{"The process has already been begun"};
        }
        int first = curState.Top();
        curState.Pop();
        int second = curState.Top();
        curState.Pop();
        curState.Push(first-second);
    }
    std::string name() override {
        return "SUB";
    }
};

class Mul: public Command{
public:
    virtual void execute(State &curState) override {
        if(!curState.isStart()) {
            throw StateException{"The process has already been begun"};
        }
        int first = curState.Top();
        curState.Pop();
        int second = curState.Top();
        curState.Pop();
        curState.Push(first*second);
    }
    std::string name() override {
        return "MUL";
    }
};

class Div: public Command{
public:
    virtual void execute(State &curState) override {
        if(!curState.isStart()) {
            throw StateException{"The process has already been begun"};
        }
        int first = curState.Top();
        curState.Pop();
        int second = curState.Top();
        curState.Pop();
        curState.Push(first/second);
    }
    std::string name() override {
        return "DIV";
    }
};

class Out: public Command{
public:
    virtual void execute(State &curState) override {
        if(!curState.isStart()) {
            throw StateException{"The process has already been begun"};
        }
        int value = curState.Top();
        curState.Pop();
        std::cout << value << '\n';
    }
    std::string name() override {
        return "OUT";
    }
};

class In: public Command{
public:
    virtual void execute(State &curState) override {
        if(!curState.isStart()) {
            throw StateException{"The process has already been begun"};
        }
        int value;
        std::cin >> value;
        curState.Push(value);
    }
    std::string name() override {
        return "IN";
    }
};

class GoTo: public Command{
public:
    std::string type, process;
    GoTo(std::string type, std::string label): type(type), process(process) {}
    virtual void execute(State &curState) override {
        int first = curState.Top();
        curState.Pop();
        int second = curState.Top();
        curState.Pop();
        curState.Push(second);
        curState.Push(first);
        if(!curState.isStart()) {
            throw StateException{"The process has already been begun"};
        }
        if(type == "JMP") {
            curState.GoTo(process);
        } else if(type == "JEQ") {
            if(first == second) {
                curState.GoTo(process);
            }
        } else if(type == "JNE") {
            if(first != second) {
                curState.GoTo(process);
            }
        } else if(type == "JA") {
            if(first > second) {
                curState.GoTo(process);
            }
        } else if(type == "JAE") {
            if(first >= second) {
                curState.GoTo(process);
            }
        } else if(type == "JB") {
            if(first < second) {
                curState.GoTo(process);
            }
        } else if(type == "JBE") {
            if (first <= second) {
                curState.GoTo(process);
            }
        }
    }
    std::string name() override {
        return type;
    }
};

class JMP: public GoTo{
public:
    std::string type, process;
    virtual void execute(State &curState) override {
        curState.GoTo(process);
    }
};

class Call: public Command{
public:
    std::string process;
    Call(std::string process):process(process){}
    virtual void execute(State &curState) override {
        if (!curState.isStart()) {
            throw StateException{"The process is not started"};
        }
        curState.Call(process);
    }
    std::string name() override{
        return "CALL";
    }
};

class Ret: public Command{
public:
    virtual void execute(State &curState) override {
        if (!curState.isStart()) {
            throw StateException{"The process is not started"};
        }
        curState.Ret();
    }
    std::string name() override{
        return "RET";
    }
};

void State::Start() {
    isgoing = true;
    stack.push_back(myStack::Stack<int>());
}

bool State::isStart() {
    return isgoing;
}

void State::SetPos(int pos) {
    position.push_back(pos);
}

void State::End() {
    isgoing = false;
    stack.clear();
}

void State::Push(int value) {
    stack[stack.size() - 1].push(value);
}

void State::Pop() {
    stack[stack.size() - 1].pop();
}

int State::Top() {
    return stack[stack.size() - 1].top();
}

int State::GetReg(std::string reg) {
    return registers[reg];
}

void State::WriteReg(std::string reg, int value) {
    registers[reg] = value;
}

void State::PushFunction(std::string function, int pos) {
    if(functions.find(function) != functions.end()) {
        throw StateException{"The function is already determined."};
    }
    functions[function] = pos;
}

void State::GoTo(std::string function) {
    position.back() = functions[function] - 1;
}

void State::Call(std::string function) {
    position.push_back(functions[function] - 1);
    stack.push_back(stack.back());
}

void State::Ret() {
    position.pop_back();
    stack.pop_back();
}

bool State::CanNext(int size) {
    return position.back() < size;
}

#endif //PROJECT2_COMMAND_H
