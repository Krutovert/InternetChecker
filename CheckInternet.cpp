#include "includes.h"
#include "FontImage.h"

#define DEBUG 0

using namespace std;

void sound()
{
	PlaySound("Internet.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void internet()
{	
#if DEBUG == 1
	printf_s("1 Step: Initialization \n");
#endif
	HINTERNET *hInternetSession = new HINTERNET;
	HINTERNET *hURL = new HINTERNET;
	char cBuffer[512];            // I'm only going to access 512B of info.
	BOOL bResult;
	DWORD *dwBytesRead = new DWORD;
	
#if DEBUG == 1
	printf_s("2 step: Make Internet Connection \n");
#endif  
	*hInternetSession = InternetOpen(
		"Internet Checker",			   // agent
		INTERNET_OPEN_TYPE_PRECONFIG,  // access
		NULL, NULL, 0);                // defaults

	// Make connection to desired page.
#if DEBUG == 1
	printf_s("3 step: make connection to page \n");
#endif
	*hURL = InternetOpenUrl(
		*hInternetSession,                       // session handle
		"http://www.google.com",				 // URL to access
		NULL, 0, 0, 0);							 // defaults

	if (*hURL != 0)
	{
#if DEBUG == 0
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
		// Read page into memory buffer.
#if DEBUG == 1
		printf_s("4 step: Read page into memory buffer \n");
#endif
		bResult = InternetReadFile(
			hURL,              // handle to URL
			(LPSTR)cBuffer,    // pointer to buffer
			(DWORD)512,       // size of buffer
			&*dwBytesRead);	   // pointer to var to hold return value

		// Close down connections
#if DEBUG == 1
		printf_s("5 step: Close connections, Internet TRUE \n");
#endif
		printf_s("True internet\n");
		InternetCloseHandle(*hURL);
		InternetCloseHandle(*hInternetSession);
		delete dwBytesRead;
		delete hURL;
		delete hInternetSession;
	}
	else
	{
#if DEBUG == 1
		printf_s("Close connections, Internet FALSE \n");
#endif
		InternetCloseHandle(*hURL);
		InternetCloseHandle(*hInternetSession);
		delete dwBytesRead;
		delete hURL;
		delete hInternetSession;
		ShowWindow(GetConsoleWindow(), SW_SHOW);
		FontImage();
		sound();
	}
}

int main()
{ 
	int i	 = 0,
		time = 0;

	printf_s("Refresh Time in second: ");
	scanf_s("%d", &time);
	time = time * 1000;

	while (true)
	{
		i++;
		printf_s("Check #: %d \n", i);
		internet();
		Sleep(time);
		system("cls");
	}

	getchar();
	return 0;
}
