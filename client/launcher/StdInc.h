#include "../shared/StdInc.h"

int DL_RequestURL(const char* url, char* buffer, size_t bufSize);

// bootstrapper functions
// move the bootstrapper files if called by the initializer
bool Bootstrap_RunInit();

// run the bootstrapper/updater functions
bool Bootstrap_DoBootstrap();

// downloader functions
void CL_InitDownloadQueue();
void CL_QueueDownload(const char* url, const char* file, int64_t size, bool compressed);
void CL_QueueDownload(const char* url, const char* file, int64_t size, bool compressed, int segments);
//void CL_QueueDownload(const char* url, const char* file, int size, bool compressed, const uint8_t* hash, uint32_t hashLen);
bool DL_Process();

bool DL_RunLoop();

// UI functions
void UI_DoCreation();
void UI_DoDestruction();
void UI_UpdateText(int textControl, const wchar_t* text);
void UI_UpdateProgress(double percentage);
bool UI_IsCanceled();

// updater functions
bool Updater_RunUpdate(int numCaches, ...);
const char* GetUpdateChannel();

#define PRODUCT_NAME L"CitizenMP"
#define CONTENT_URL "http://content.citizen.re/iv/"
#define CONTENT_URL_WIDE L"http://content.citizen.re/iv/"

#include <citversion.h>