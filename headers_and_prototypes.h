#ifndef HEADERS_AND_PROTOTYPES_H_INCLUDED
#define HEADERS_AND_PROTOTYPES_H_INCLUDED

//header files
#include<iostream>
#include<fstream>
#include<string.h>
#include<cctype>
#include<vector>

//prototypes
int show_Words(const std::string &result_file,std::vector<Word> &w);
int instructions(std::string &open_file,std::string &result_file);
int fill_the_Word_vec(const std::string &open_file,std::vector<Word> &w);
int Sort(std::vector<Word> &w);
int character_mode(std::string &open_file,std::string &result_file);

#endif // HEADERS_AND_PROTOTYPES_H_INCLUDED
