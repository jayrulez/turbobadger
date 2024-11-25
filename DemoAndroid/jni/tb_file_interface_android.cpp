#include "tb_file_interface_android.h"

namespace
{
	size_t allocateFileId()
	{
		static size_t s_fileId = 0;
		return ++s_fileId;
	}
}

AAssetManager *g_pManager = NULL;

void SetAssetManager(AAssetManager *pManager)
{
	g_pManager = pManager;
}

namespace tb {

tb::TBFileHandle TBFileInterfaceAndroid::Open(const char* filename, TBFileMode mode)
{
	AAsset* f = nullptr;
	switch (mode)
	{
	case MODE_READ:
		f = AAssetManager_open(g_pManager, filename, AASSET_MODE_UNKNOWN);
		break;
	default:
		break;
	}
	if (!f)
		return 0;

	size_t fileId = allocateFileId();
	m_openFiles.emplace(fileId, f);
	return static_cast<tb::TBFileHandle>(fileId);
}

void TBFileInterfaceAndroid::Close(tb::TBFileHandle file)
{
	size_t fileId = static_cast<size_t>(file);

	if (m_openFiles.find(fileId) != m_openFiles.end())
	{
		AAsset_close(m_openFiles[fileId]);
		m_openFiles.erase(fileId);
	}
}

long TBFileInterfaceAndroid::Size(tb::TBFileHandle file)
{
	size_t fileId = static_cast<size_t>(file);

	if (m_openFiles.find(fileId) != m_openFiles.end())
	{
		return AAsset_getLength(m_openFiles[fileId]);
	}

	return 0;
}

size_t TBFileInterfaceAndroid::Read(tb::TBFileHandle file, void* buf, size_t elemSize, size_t count)
{
	size_t fileId = static_cast<size_t>(file);

	if (m_openFiles.find(fileId) != m_openFiles.end())
	{
		return AAsset_read(m_openFiles[fileId], buf, elemSize * count);
	}

	return 0;
}

} // namespace tb
