#ifndef PROJECT2_PARSER_H
#define PROJECT2_PARSER_H

#include "PreProc/Token.h"

int vectorCommand(std::vector<Token>& vec_tokens, std::vector<std::shared_ptr<Command>> &vecCommand,
                         State &curState) {
    int begin = -1;
    for (int i = 0; i < vec_tokens.size(); i++) {
        switch(vec_tokens[i].type_) {
            case TokenType::BEGIN:
                if (begin != -1) {
                    throw ParserExeption{"Program starts twice."};
                }
                begin = vecCommand.size();
                vecCommand.push_back(std::make_shared<Begin>());
                break;

            case TokenType::END:
                vecCommand.push_back(std::make_shared<End>());
                break;

            case TokenType::PUSH:
                if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::INTEGER_VALUE) {
                    throw ParserExeption{"Push command need value"};
                }
                i += 1;
                vecCommand.push_back(std::make_shared<Push> (stoi(vec_tokens[i].value_)));
                break;

            case TokenType::POP:
                vecCommand.push_back(std::make_shared<Pop>());
                break;

            case TokenType::PUSHR:
                if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::WORD) {
                    throw ParserExeption{"PushR command need register"};
                }
                i += 1;
                if (curState.registers.find(vec_tokens[i].value_) == curState.registers.end()) {
                    curState.registers[vec_tokens[i].value_] = 0;
                }
                vecCommand.push_back(std::make_shared<PushR>(vec_tokens[i].value_));
                break;

            case TokenType::POPR:
                if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::WORD) {
                    throw ParserExeption{"PopR command need register"};
                }
                i += 1;
                if (curState.registers.find(vec_tokens[i].value_) == curState.registers.end()) {
                    curState.registers[vec_tokens[i].value_] = 0;
                }
                vecCommand.push_back(std::make_shared<PopR>(vec_tokens[i].value_));
                break;

            case TokenType::ADD:
                vecCommand.push_back(std::make_shared<Add>());
                break;

            case TokenType::SUB:
                vecCommand.push_back(std::make_shared<Sub>());
                break;

            case TokenType::MUL:
                vecCommand.push_back(std::make_shared<Mul>());
                break;

            case TokenType::DIV:
                vecCommand.push_back(std::make_shared<Div>());
                break;

            case TokenType::OUT:
                vecCommand.push_back(std::make_shared<Out>());
                break;

            case TokenType::IN:
                vecCommand.push_back(std::make_shared<In>());
                break;

            case TokenType::GOTO:
                if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::WORD) {
                    throw ParserExeption{vec_tokens[i].value_ + " command need a label"};
                }
                vecCommand.push_back(std::make_shared<GoTo>(vec_tokens[i].value_, vec_tokens[i + 1].value_));
                i += 1;
                break;

            case TokenType::CALL:
                if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::WORD) {
                    throw ParserExeption{vec_tokens[i].value_ + " command need a label"};
                }
                vecCommand.push_back(std::make_shared<Call>(vec_tokens[i + 1].value_));
                i += 1;
                break;

            case TokenType::RET:
                vecCommand.push_back(std::make_shared<Ret>());
                break;

            case TokenType::WORD:
                if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::INIT) {
                    throw ParserExeption{"Word " + vec_tokens[i].value_ + "has no suitable function"};
                }
                if (i + 2 > vec_tokens.size() || vec_tokens[i + 2].type_ == TokenType::WORD) {
                    throw ParserExeption{"Function " + vec_tokens[i].value_ + " doesn't have any defenition"};
                }
                curState.PushFunction(vec_tokens[i].value_, vecCommand.size());
                i += 1;
                break;

            default:
                throw ParserExeption{"Error : " +  vec_tokens[i].value_};
        }
    }
    return begin;
}

#endif