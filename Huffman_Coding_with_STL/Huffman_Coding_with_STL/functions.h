#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include "HuffmanTree.h"
#include "StreamGuard.h"

const size_t SIZE_ARRAY_SYMBOL = 256; // Размер алфавита ASCII 
const char ID[21] = "d/g5y09v$4nf$jkf$hg%"; // id закодированного файла

void encode();
void decode();
void compare();

#endif