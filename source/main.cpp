#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include "lexer.hpp"

std::string ReadSourceFile(const char* file_path){
    std::stringstream sstream;
    std::ifstream istr;
    std::string line;
    istr.open(file_path, std::ios::in);
    if(istr.is_open()){
        while(!istr.eof()){
            std::getline(istr, line);
            sstream << line << std::endl;
        }
        return sstream.str();
    }
    return "FILE_NOT_FOUND_ERROR";
}

int main(int argc, const char** argv) {
    if(argc < 2){std::cerr << "Too Few Arguements Provided" << std::endl; return -1;}
    std::string source = ReadSourceFile(argv[1]);
    if(source == "FILE_NOT_FOUND_ERROR"){
        std::cerr << "Cannot Find File: "<<argv[1]<<std::endl;
        return -1;
    }
    std::list<std::string> tokens;
    LexerProcess(source, tokens);

    for(std::string str : tokens){
        std::cout<<str<<std::endl;
    }
}