#pragma once

#include <unordered_set>
#include <mutex>
#include "fiDevice.h"

struct ResourceDownload
{
	std::string sourceUrl;
	std::string targetFilename;
	std::string filename;
	std::string resname;
};

class ResourceData;

struct ResourceFile
{
	std::string filename;

	std::string hash;
};

class ResourceData
{
private:
	std::string m_name;

	std::vector<ResourceFile> m_files;

	std::string m_baseUrl;

	bool m_processed;

public:
	inline ResourceData() {}

	ResourceData(std::string name, std::string baseUrl);

	void AddFile(std::string filename, std::string hash);

	inline std::string GetBaseURL() const { return m_baseUrl; }

	inline const std::vector<ResourceFile>& GetFiles() const { return m_files; }

	inline std::string GetName() const { return m_name; }

	inline bool IsProcessed() const { return m_processed;  }

	inline void SetProcessed() { m_processed = true; }
};

struct StreamingResource : ResourceFile
{
	ResourceData resData;
	uint32_t rscFlags;
	uint32_t rscVersion;
	uint32_t size;
};

struct CacheEntry
{
	std::string resource;
	std::string filename;
	std::string hash;

	bool operator==(const CacheEntry& right) const;
	bool operator!=(const CacheEntry& right) const;
};

namespace std
{
	template<>
	struct hash < CacheEntry >
	{
		size_t operator()(const CacheEntry& entry) const
		{
			return std::hash<std::string>()(entry.filename) ^ (std::hash<std::string>()(entry.resource) << 1) ^ (std::hash<std::string>()(entry.hash) << 2);
		}
	};
}

class ResourceCache
{
private:
	std::vector<CacheEntry> m_cache;

	std::unordered_set<CacheEntry> m_cacheSet;

	std::unordered_map<std::string, CacheEntry> m_markList;

	rage::fiDevice* m_cacheDevice;

	std::mutex m_dataLock;

private:
	void AddEntry(std::string fileName, std::string resourceName, std::string hash);

	bool ParseFileName(const char* inString, std::string& fileNameOut, std::string& resourceNameOut, std::string& hashOut);

public:
	ResourceDownload GetResourceDownload(const ResourceData& resource, const ResourceFile& file);

	void Initialize();

	void LoadCache(rage::fiDevice* device);

	void AddFile(std::string& sourcePath, std::string& filename, std::string& resource);

	void ClearMark();

	void MarkList(std::vector<ResourceData>& resourceList);

	void MarkStreamingList(std::vector<StreamingResource>& streamList);

	inline rage::fiDevice* GetCacheDevice() { return m_cacheDevice; }

	std::string GetMarkedFilenameFor(std::string resource, std::string filename);

	std::vector<ResourceDownload> GetDownloadsFromList(std::vector<ResourceData>& resourceList);
};