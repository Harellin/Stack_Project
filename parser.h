#ifndef PROJECT2_PARSER_H
#define PROJECT2_PARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include "Command.h"

enum class TokenType {
    BEGIN,
    END,
    PUSH,
    POP,
    PUSHR,
    POPR,
    ADD,
    SUB,
    MUL,
    DIV,
    OUT,
    IN,
    GOTO,
    INIT,
    CALL,
    RET,
    UNDEFINED,
    INTEGER_VALUE,
    WORD,
};

std::map<TokenType, std::regex> token_regex_ = {
        {TokenType::BEGIN,std::regex("BEGIN")},
        {TokenType::END,std::regex("END")},
        {TokenType::PUSH,std::regex("PUSH")},
        {TokenType::POP,std::regex("POP")},
        {TokenType::PUSHR,std::regex("PUSHR")},
        {TokenType::POPR,std::regex("POPR")},
        {TokenType::ADD,std::regex("ADD")},
        {TokenType::SUB,std::regex("SUB")},
        {TokenType::MUL,std::regex("MUL")},
        {TokenType::DIV,std::regex("DIV")},
        {TokenType::OUT,std::regex("OUT")},
        {TokenType::IN,std::regex("IN")},
        {TokenType::GOTO,std::regex("JMP|JEQ|JNE|JAE|JBE|JA|JB")},
        {TokenType::CALL,std::regex("CALL")},
        {TokenType::RET,std::regex("RET")},
        {TokenType::INIT,std::regex(":")},
        {TokenType::UNDEFINED,std::regex(".*")},
        {TokenType::INTEGER_VALUE,std::regex("[-+]?[0-9]+")},
        {TokenType::WORD,std::regex("[a-zA-Z_][a-zA-Z0-9_]*")},

};

std::vector<TokenType> tokens = {TokenType::BEGIN,
                                 TokenType::END,
                                 TokenType::PUSH,
                                 TokenType::POP,
                                 TokenType::PUSHR,
                                 TokenType::POPR,
                                 TokenType::ADD,
                                 TokenType::SUB,
                                 TokenType::MUL,
                                 TokenType::DIV,
                                 TokenType::OUT,
                                 TokenType::IN,
                                 TokenType::GOTO,
                                 TokenType::CALL,
                                 TokenType::RET,
                                 TokenType::INIT,
                                 TokenType::INTEGER_VALUE,
                                 TokenType::WORD,
                                 TokenType::UNDEFINED};

class ParserExeption {
public:
    ParserExeption(const std::string& message): message_(message){}
    virtual std::string what() {
        return message_;
    }
private:
    std::string message_;
};

struct Token {
    std::string value_;
    TokenType type_;
    Token(std::string value, TokenType type): value_(value), type_(type) {}
};

std::vector<Token> FileParser(std::ifstream & file) {

    std::vector<Token> result;

    if (!file.is_open()) {
        throw ParserExeption{"File is not open"};
    }

    std::string cur_str;
    std::vector<std::string> str;
    while (file >> cur_str) {
        str.push_back(cur_str);
    }

    for (int i = 0 ; i < str.size(); i++) {
        for (int j = 0; j < tokens.size(); j++) {
            if (std::regex_match(str[i], token_regex_[tokens[j]])) {
                if (tokens[j] == TokenType::UNDEFINED) {
                    throw ParserExeption{"TokenType::UNDEFINED : " + str[i]};
                }
                Token new_token(str[i], tokens[j]);
                result.push_back(new_token);
                break;
            }
        }
    }

    return result;
}

int vectorCommand(std::vector<Token>& vec_tokens, std::vector<Command *> &vecCommand,
                         State &curState) {
    int begin = -1;
    for (int i = 0; i < vec_tokens.size(); i++) {
        switch(vec_tokens[i].type_) {
            case TokenType::BEGIN:
                if (begin != -1) {
                    throw ParserExeption{"Program starts twice."};
                }
                begin = vecCommand.size();
                vecCommand.push_back(new Begin());
                break;

            case TokenType::END:
                vecCommand.push_back(new End());
                break;

            case TokenType::PUSH:
                if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::INTEGER_VALUE) {
                    throw ParserExeption{"Push command need value"};
                }
                i += 1;
                vecCommand.push_back(new Push(stoi(vec_tokens[i].value_)));
                break;

            case TokenType::POP:
                vecCommand.push_back(new Pop());
                break;

            case TokenType::PUSHR:
                if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::WORD) {
                    throw ParserExeption{"PushR command need register"};
                }
                i += 1;
                if (curState.registers.find(vec_tokens[i].value_) == curState.registers.end()) {
                    curState.registers[vec_tokens[i].value_] = 0;
                }
                vecCommand.push_back(new PushR(vec_tokens[i].value_));
                break;

            case TokenType::POPR:
                if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::WORD) {
                    throw ParserExeption{"PopR command need register"};
                }
                i += 1;
                if (curState.registers.find(vec_tokens[i].value_) == curState.registers.end()) {
                    curState.registers[vec_tokens[i].value_] = 0;
                }
                vecCommand.push_back(new PopR(vec_tokens[i].value_));
                break;

            case TokenType::ADD:
                vecCommand.push_back(new Add());
                break;

            case TokenType::SUB:
                vecCommand.push_back(new Sub());
                break;

            case TokenType::MUL:
                vecCommand.push_back(new Mul());
                break;

            case TokenType::DIV:
                vecCommand.push_back(new Div());
                break;

            case TokenType::OUT:
                vecCommand.push_back(new Out());
                break;

            case TokenType::IN:
                vecCommand.push_back(new In());
                break;

            case TokenType::GOTO:
                if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::WORD) {
                    throw ParserExeption{vec_tokens[i].value_ + " command need a label"};
                }
                vecCommand.push_back(new GoTo(vec_tokens[i].value_, vec_tokens[i + 1].value_));
                i += 1;
                break;

            case TokenType::CALL:
                if (i + 1 > vec_tokens.size() || vec_tokens[i + 1].type_ != TokenType::WORD) {
                    throw ParserExeption{vec_tokens[i].value_ + " command need a label"};
                }
                vecCommand.push_back(new Call(vec_tokens[i + 1].value_));
                i += 1;
                break;

            case TokenType::RET:
                vecCommand.push_back(new Ret());
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
