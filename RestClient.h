#pragma once
#include <iostream>
#include <curl/curl.h>
#include <Windows.h>

#ifdef ASYNCREFRESH_EXPORTS
#define RESTCLIENT_API __declspec(dllexport)
#else
#define RESTCLIENT_API __declspec(dllimport)
#endif

class RestClient
{
public:
	RestClient(double* currencyAddress, std::string currencyAPI, unsigned int delay = 0);
	RestClient& RunAsyncLoop();
	RestClient& PauseAsyncLoop();
	~RestClient();
	bool IsThreadActive() const;
private:
	CURL* hCurl;
	std::string currencyAPI;
	void* currencyAddress;
	unsigned int delay;
	HANDLE hThread;
	unsigned int errCount;
	bool isThreadActive;

	static void ThreadFunc(RestClient* currentClient);
	static size_t write_callback(char* data, size_t size, size_t nmemb, void* userp);
};

