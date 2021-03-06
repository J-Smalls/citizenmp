#pragma once

#include "sysAllocator.h"

namespace rage
{
struct fiFindData
{
	char fileName[512];
	uint64_t fileSize;
	FILETIME lastWriteTime;
	DWORD fileAttributes;
};

class GAMESPEC_EXPORT_VMT __declspec(novtable) fiDevice : public sysUseAllocator
{
public:
	static fiDevice* GetDevice(const char* path, bool allowRoot);

	static void Unmount(const char* rootPath);

	static void SetInitialMountHook(void(*callback)(void*));

public:
	virtual ~fiDevice() = 0;

	virtual uint32_t open(const char* fileName, bool readOnly) = 0;

	virtual uint32_t openBulk(const char* fileName, uint64_t* ptr) = 0;

	virtual uint32_t createLocal(const char* fileName) = 0;

	virtual uint32_t create(const char* fileName);

	virtual uint32_t read(uint32_t handle, void* buffer, uint32_t toRead) = 0;

	virtual uint32_t readBulk(uint32_t handle, uint64_t ptr, void* buffer, uint32_t toRead) = 0;

	virtual uint32_t writeBulk(int, int, int, int, int) = 0;

	virtual uint32_t write(int, void*, int) = 0;

	virtual uint32_t seek(uint32_t handle, int32_t distance, uint32_t method) = 0;

	virtual void close(uint32_t handle) = 0;

	virtual void closeBulk(uint32_t handle) = 0;

	virtual int fileLength(uint32_t handle) = 0;

	virtual int m_34() = 0;
	virtual bool rm(const char* file) = 0;
	virtual int rename(const char* from, const char* to) = 0;
	virtual int mkdir(const char* dir) = 0;

	virtual int rmdir(const char * dir) = 0;
	virtual LARGE_INTEGER fileLengthLong(const char* file) = 0;
	virtual uint32_t fileTime(const char* file) = 0;
	virtual bool setFileTime(const char* file, FILETIME fileTime) = 0;

	virtual int findFirst(const char* path, fiFindData* findData) = 0;
	virtual bool findNext(int handle, fiFindData* findData) = 0;
	virtual int findClose(int handle) = 0;
	virtual bool truncate(uint32_t handle) = 0;

	virtual uint32_t getFileAttributes(const char* path) = 0;
	virtual bool setFileAttributes(const char* file, uint32_t FileAttributes) = 0;
	virtual int m_6C() = 0;
	virtual uint32_t getParentHandle() = 0;
};

class GAMESPEC_EXPORT_VMT fiDeviceImplemented : public fiDevice
{
protected:
	fiDeviceImplemented();

public:
	virtual ~fiDeviceImplemented();

	virtual uint32_t open(const char* fileName, bool);

	virtual uint32_t openBulk(const char* fileName, uint64_t* ptr);

	virtual uint32_t createLocal(const char* fileName);

	virtual uint32_t create(const char*);

	virtual uint32_t read(uint32_t handle, void* buffer, uint32_t toRead);

	virtual uint32_t readBulk(uint32_t handle, uint64_t ptr, void* buffer, uint32_t toRead);

	virtual uint32_t writeBulk(int, int, int, int, int);

	virtual uint32_t write(int, void*, int);

	virtual uint32_t seek(uint32_t handle, int32_t distance, uint32_t method);

	virtual void close(uint32_t handle);

	virtual void closeBulk(uint32_t handle);

	virtual int fileLength(uint32_t handle);

	virtual int m_34();
	virtual bool rm(const char* file);
	virtual int rename(const char* from, const char* to);
	virtual int mkdir(const char* dir);

	virtual int rmdir(const char * dir);
	virtual LARGE_INTEGER fileLengthLong(const char* file);
	virtual uint32_t fileTime(const char* file);
	virtual bool setFileTime(const char* file, FILETIME fileTime);

	virtual int findFirst(const char* path, fiFindData* findData);
	virtual bool findNext(int handle, fiFindData* findData);
	virtual int findClose(int handle);
	virtual bool truncate(uint32_t handle);

	virtual uint32_t getFileAttributes(const char* path);
	virtual bool setFileAttributes(const char* file, uint32_t FileAttributes);
	virtual int m_6C();
	virtual uint32_t getParentHandle();
};

class GAMESPEC_EXPORT_VMT fiDeviceRelative : public fiDeviceImplemented
{
private:
	char m_pad[524];
public:
	fiDeviceRelative();

	// any RAGE path can be used; including root-relative paths
	void setPath(const char* relativeTo, bool allowRoot);

	// mounts the device in the device stack
	void mount(const char* mountPoint);
};

class GAMESPEC_EXPORT_VMT fiPackfile : public fiDeviceImplemented
{
private:
	char m_pad[1144];
public:
	fiPackfile();

	// any RAGE path can be used; including root-relative paths
	void openArchive(const char* archive, bool bTrue, bool bFalse, int type);

	// mounts the device in the device stack
	void mount(const char* mountPoint);

	// closes the package file
	void closeArchive();
};
}