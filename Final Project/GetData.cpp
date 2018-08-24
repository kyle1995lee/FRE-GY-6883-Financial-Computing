#include "Getdata.hpp"
#include <string> 
#include <iostream>
#include <sstream>  
#include <vector>
#include <locale>
#include <iomanip>
#include <map>
#include "curl.h"
#include <thread>
#include <mutex>
using namespace std;

int write_data(void *ptr, int size, int nmemb, FILE *stream)
{
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return written;
}

void *myrealloc(void *ptr, size_t size)
{
	/* There might be a realloc() out there that doesn't like reallocing
	NULL pointers, so we take care of it here */
	if (ptr)
		return realloc(ptr, size);
	else
		return malloc(size);
}

int write_data2(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)data;

	mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory) {
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}
	return realsize;
}

string getTimeinSeconds(string Time)
{
	std::tm t = { 0 };
	std::istringstream ssTime(Time);
	char time[100];
	memset(time, 0, 100);
	if (ssTime >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S"))
	{
		//cout << std::put_time(&t, "%c %Z") << "\n"
		//<< std::mktime(&t) << "\n";
		sprintf(time, "%lld", mktime(&t));
		return string(time);
	}
	else
	{
		cout << "Parse failed\n";
		return "";
	}
}

void pricehandle(map<string, Stock>& all_stocks, string& sCrumb, string& sCookies)
{

	map<string, Stock>::iterator itr = all_stocks.begin();
	int num = 0;
	string startTime = getTimeinSeconds("2016-09-01T16:00:00");
	string endTime = getTimeinSeconds("2018-04-30T16:00:00");
	////file pointer to create file that store the data  
	//FILE *fp;

	////name of files  
	//const char outfilename[FILENAME_MAX] = "Output.txt";
	//const char resultfilename[FILENAME_MAX] = "Results.txt";

	/* declaration of an object CURL */
	CURL *handle;

	/* result of the whole process */
	CURLcode result;

	/* the first functions */
	/* set up the program environment that libcurl needs */
	curl_global_init(CURL_GLOBAL_ALL);

	/* curl_easy_init() returns a CURL easy handle that you're gonna reuse in other easy functions*/
	handle = curl_easy_init();

	/* if everything's all right with the easy handle... */
	if (handle)
	{

		for (itr = all_stocks.begin(); itr != all_stocks.end(); itr++)

		{
			struct MemoryStruct data;
			data.memory = NULL;
			data.size = 0;

			string urlA = "https://query1.finance.yahoo.com/v7/finance/download/";
			string symbol = itr->first;
			string urlB = "?period1=";
			string urlC = "&period2=";
			string urlD = "&interval=1d&events=history&crumb=";

			string url = urlA + symbol + urlB + startTime + urlC + endTime + urlD + sCrumb;
			const char * cURL = url.c_str();
			const char * cookies = sCookies.c_str();
			//cout << url;
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
			curl_easy_setopt(handle, CURLOPT_COOKIE, cookies);   // Only needed for 1st stock
			curl_easy_setopt(handle, CURLOPT_URL, cURL);
			curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "cookies.txt");
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);
			result = curl_easy_perform(handle);
			if (result != CURLE_OK)
			{
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				//return stock_price;
			}

			istringstream sData(data.memory);
			string sValue, sDate;
			double dValue = 0.0;
			string line;
			map<Date, double> curprice;
			stack<Date> dates;
			stack<double> adj;
			int count = 0;
			getline(sData, line);
			while (getline(sData, line)) {
				//cout << line << endl;
				sDate = line.substr(0, line.find_first_of(','));
				line.erase(line.find_last_of(','));
				sValue = line.substr(line.find_last_of(',') + 1);
				dValue = strtod(sValue.c_str(), NULL);

				tm t{};
				istringstream d(sDate);
				d >> get_time(&t, "%Y-%m-%d");
				int year = t.tm_year + 1900;
				int mon = t.tm_mon + 1;
				int day = t.tm_mday;
				Date dd(year, mon, day);
				if (dd > itr->second.GetReportDate()) {
					dates.push(dd);
					adj.push(dValue);
					count++;
				}
				else {
					dates.push(dd);
					adj.push(dValue);
					//cout << count;
				}
				if (count == 30) {
					break;
				}
			}
			while (!dates.empty()) {
				if (dates.top() < itr->second.GetReportDate()) {
					curprice[dates.top()] = adj.top();
					dates.pop();
					adj.pop();
					count--;
				}
				else {
					curprice[dates.top()] = adj.top();
					dates.pop();
					adj.pop();

				}
				if (count == -30) {
					break;
				}
			}
			itr->second.SetPrice(curprice);
			itr->second.SetStartDate((curprice.begin())->first);
			itr->second.SetEndDate((--curprice.end())->first);
			std::map<Date, double> ret;
			for (auto i = curprice.begin(); i != --curprice.end(); i++) {
				auto j = i;
				j++;
				ret[j->first] = (j->second - i->second) / i->second;
				itr->second.SetReturn(ret);
			}
			cout << itr->first << endl;
			//itr++;
			num++;
			free(data.memory);
			data.size = 0;
		}
	}
	else
	{
		fprintf(stderr, "Curl init failed!\n");

	}

	/* cleanup since you've used curl_easy_init */
	curl_easy_cleanup(handle);
	/* this function releases resources acquired by curl_global_init() */
	curl_global_cleanup();
	cout << num << "stocks completed!" << endl;
}

void GetspyAlsoGetCrumb(Share& spy, string& sCrumb, string& sCookies) {
	string startTime = getTimeinSeconds("2016-08-01T16:00:00");
	string endTime = getTimeinSeconds("2018-04-30T16:00:00");
	spy.SetTicker("spy");
	struct MemoryStruct data;
	data.memory = NULL;
	data.size = 0;
	FILE *fp;
	CURL * handle;
	CURLcode result;
	curl_global_init(CURL_GLOBAL_ALL);
	handle = curl_easy_init();

	if (handle)
	{

		curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/AMZN/history");
		curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(handle, CURLOPT_COOKIEJAR, "cookies.txt");
		curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "cookies.txt");
		curl_easy_setopt(handle, CURLOPT_ENCODING, "");
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
		curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);

		/* perform, then store the expected code in 'result'*/
		result = curl_easy_perform(handle);

		/* Check for errors */
		if (result != CURLE_OK)
		{
			/* if errors have occured, tell us what is wrong with 'result'*/
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
			//return 1;
		}

		char cKey[] = "CrumbStore\":{\"crumb\":\"";
		char *ptr1 = strstr(data.memory, cKey);
		char *ptr2 = ptr1 + strlen(cKey);
		char *ptr3 = strstr(ptr2, "\"}");
		if (ptr3 != NULL)
			*ptr3 = NULL;

		sCrumb = ptr2;
		fp = fopen("cookies.txt", "r");
		char cCookies[100];
		if (fp) {
			while (fscanf(fp, "%s", cCookies) != EOF);
			fclose(fp);
		}
		else
			cerr << "cookies.txt does not exists" << endl;

		sCookies = cCookies;
		free(data.memory);
		data.memory = NULL;
		data.size = 0;

		string urlA = "https://query1.finance.yahoo.com/v7/finance/download/";
		string symbol = spy.GetTicker();
		string urlB = "?period1=";
		string urlC = "&period2=";
		string urlD = "&interval=1d&events=history&crumb=";
		string url = urlA + symbol + urlB + startTime + urlC + endTime + urlD + sCrumb;
		const char * cURL = url.c_str();
		const char * cookies = sCookies.c_str();
		curl_easy_setopt(handle, CURLOPT_COOKIE, cookies);   // Only needed for 1st stock
		curl_easy_setopt(handle, CURLOPT_URL, cURL);
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
		curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);
		result = curl_easy_perform(handle);

		/* Check for errors */
		if (result != CURLE_OK)
		{
			/* if errors have occurred, tell us what is wrong with 'result'*/
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
			//return 1;
		}

		stringstream sData;
		sData.str(data.memory);
		string sValue, sDate;
		double dValue = 0;
		string line;
		map<Date, double> curprice;
		stack<Date> dates;
		stack<double> adj;
		getline(sData, line);
		while (getline(sData, line)) {
			//cout << line << endl;
			sDate = line.substr(0, line.find_first_of(','));
			line.erase(line.find_last_of(','));
			sValue = line.substr(line.find_last_of(',') + 1);
			dValue = strtod(sValue.c_str(), NULL);
			tm t{};
			istringstream d(sDate);
			d >> get_time(&t, "%Y-%m-%d");
			int year = t.tm_year + 1900;
			int mon = t.tm_mon + 1;
			int day = t.tm_mday;
			Date dd(year, mon, day);
			dates.push(dd);
			adj.push(dValue);
		}

		while (!dates.empty()) {
			curprice[dates.top()] = adj.top();
			dates.pop();
			adj.pop();
		}

		spy.SetPrice(curprice);
		spy.SetStartDate((curprice.begin())->first);
		spy.SetEndDate((--curprice.end())->first);
		std::map<Date, double> ret;//spy return
		for (auto i = curprice.begin(); i != --curprice.end(); i++) {
			auto j = i;
			j++;
			ret[j->first] = (j->second - i->second) / i->second;
		}
		spy.SetReturn(ret);

		free(data.memory);
		data.size = 0;

	}
	else
	{
		fprintf(stderr, "Curl init failed!\n");
	}
	cout << "SPY download completed" << endl;
	curl_easy_cleanup(handle);
	curl_global_cleanup();
}

void AllStock(map<string, Stock>& all_stocks) {

	ifstream file("SP500.csv");
	string line;
	if (!file.is_open()) {
		cerr << "Load SP500data.csv Failed" << endl;
		system("pause");
	}

	while (getline(file, line)) {
		istringstream ss(line);
		string token;
		Stock temp;
		getline(ss, token, ',');
		temp.SetTicker(token);
		getline(ss, token, ',');
		string date = token;
		getline(ss, token, ',');
		double est = stod(token);
		getline(ss, token, ',');
		temp.SetSurprise((stod(token) - est) / est * 100);
		getline(ss, token, ',');
		int y = stoi(token);
		getline(ss, token, ',');
		int m = stoi(token);
		getline(ss, token, ',');
		int d = stoi(token);
		Date rep(y, m, d);
		temp.SetReportDate(rep);
		all_stocks[temp.GetTicker()] = temp;
	}
	cout << "Reading Mission Completed" << endl;
}
