#pragma once
#include "curl.h"
#include "Share.h"
#include <stdio.h>
#include <string> 
#include <iostream>
#include <sstream>  
#include <vector>
#include <locale>
#include <locale.h>
#include <iomanip>
#include <fstream>
#include <thread>
#include <stack>
#include <map>
#include <ctime>
#include <mutex>
static std::mutex barrier;

void MulGetspyAlsoGetCrumb(Share& spy, std::string& sCrumb, std::string& sCookies);
void MulAllStock(std::map<std::string, Stock>& all_stocks);
void MulTimeForMagic(std::map<std::string, Stock>& all_stocks, Share& spy);