#pragma once
#include <string> 
#include <vector>
#include <fstream>
#include <iostream>
#include "Date.h"
#include "Share.h"
#include <stack>
#include <map>

struct MemoryStruct {
	char *memory;
	size_t size;
};

int write_data(void *ptr, int size, int nmemb, FILE *stream);
void *myrealloc(void *ptr, size_t size);
int write_data2(void *ptr, size_t size, size_t nmemb, void *data);
std::string getTimeinSeconds(std::string Time);
void GetspyAlsoGetCrumb(Share& spy, std::string& sCrumb, std::string& sCookies);
void AllStock(std::map<std::string, Stock>& all_stocks);
void pricehandle(std::map<std::string, Stock>& all_stocks, std::string& sCrumb, std::string& sCookies);