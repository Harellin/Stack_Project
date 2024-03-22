#ifndef PROJECT2_TOKEN_H
#define PROJECT2_TOKEN_H

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

struct Token {
    std::string value_;
    TokenType type_;
    Token(std::string value, TokenType type): value_(value), type_(type) {}
};

class ParserExeption {
public:
    ParserExeption(const std::string& message): message_(message){}
    virtual std::string what() {
        return message_;
    }
private:
    std::string message_;
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

#endif //PROJECT2_TOKEN_H
