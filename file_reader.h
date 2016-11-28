#ifndef _ALGO_H
#define _ALGO_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <sys/stat.h>

#include "algo.h"
#include "Base.h"

using namespace std;

#define ALGO_CHAR_LENGTH         256
#define ALGO_CHAR_LONG_LENGTH    2048

///file_reader.cpp
//------------------------------------------------------------
    int ALGO_File_Check(const char *_file_name) ;
    double ALGO_File_Char_To_Double(char* _number) ;
    void ALGO_File_Load(const char *_file_name) ;
    int ALGO_File_Quick(const char *_file_name) ;
    Base* ALGO_File(int _show_data = 0) ;
//------------------------------------------------------------


#endif // _ALGO_H
