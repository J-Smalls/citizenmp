#include "StdInc.h"
#include "Streaming.h"

uint32_t WRAPPER CImgManager::registerIMGFile(const char* name, uint32_t offset, uint32_t size, uint8_t imgNum, uint32_t index, uint32_t resourceType) { EAXJMP(0xBCC2E0); }

StreamingFile::~StreamingFile()
{

}

CImgManager* CImgManager::GetInstance()
{
	return (CImgManager*)0xF21C60;
}

static StreamingFile* g_files[65535];
static StreamingModule* g_streamingModule;

void CStreaming::SetStreamingModule(StreamingModule* module)
{
	g_streamingModule = module;
}

void CStreaming::ScanImgEntries()
{
	g_streamingModule->ScanEntries();
}

uint32_t CStreaming::OpenImgEntry(uint32_t handle)
{
	auto file = g_streamingModule->GetEntryFromIndex(handle);

	if (!file)
	{
		FatalError("Unknown streaming file %d from streaming module", handle);
	}

	file->Open();

	g_files[handle] = file;

	return handle;
}

StreamingFile* CStreaming::GetImgEntry(uint32_t handle)
{
	return g_files[handle];
}

uint32_t CStreaming::CloseImgEntry(uint32_t handle)
{
	g_files[handle]->Close();
	g_files[handle] = nullptr;

	return -1;
}