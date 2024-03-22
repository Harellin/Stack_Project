#include <iostream>
#include <memory>
#include "parser.h"

int main() {

    std::string curfile;
    std::cin >> curfile;
    std::ifstream file;
    file.open(curfile);

    try{
        std::vector<Token> tokens = FileParser(file);
        State curState;
        std::vector<std::shared_ptr<Command>> vec_command;
        int begin = vectorCommand(tokens, vec_command, curState);
        curState.SetPos(begin);

        while (curState.CanNext(vec_command.size())) {
            Next(vec_command, curState);
        }
    }  catch (ParserExeption& error) {
        std::cout << error.what();
    } catch (StateException& error) {
        std::cout << error.what();
    }

    return 0;
}