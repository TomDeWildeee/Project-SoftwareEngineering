//============================================================================
// Name        : TicTacToeUtils.h
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style (Added isNumber function)
//============================================================================

// Below are two lines serving as a so-called ``header guard''.
// Prevents from loading the same .h file multiple times
#ifndef Utils_H
#define Utils_H


#include <iostream>

bool DirectoryExists(const std::string dirname);

bool FileExists(const std::string dirname);

bool FileIsEmpty(const std::string filename);

bool FileCompare(const std::string leftFileName, const std::string rightFileName);

bool isNumber(std::string& s);

std::string ToString(int i);

// Closing of the ``header guard''.
#endif