#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <exception>
#include <memory>
#include "HuffmanTree.h"
#include "CodeVector.h"
#include "StreamGuard.h"

const unsigned int SIZE_ARRAY_SYMBOL = 256; // Размер алфавита ASCII 
const char ID[21] = "d/g5y09v$4nf$jkf$hg%"; // Маска закодированного файла

void encode();
void decode();
void compare();

#endif