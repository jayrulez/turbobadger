// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_file_interface_posix.h"

#include <stdio.h>

namespace
{
	size_t allocateFileId()
	{
		static size_t s_fileId = 0;
		return ++s_fileId;
	}
}

namespace tb {

tb::TBFileHandle TBFileInterfacePosix::Open(const char* filename, TBFileMode mode)
{
	FILE* f = nullptr;
	switch (mode)
	{
	case MODE_READ:
		f = fopen(filename, "rb");
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

void TBFileInterfacePosix::Close(tb::TBFileHandle file)
{
	size_t fileId = static_cast<size_t>(file);

	if (m_openFiles.find(fileId) != m_openFiles.end())
	{
		fclose(m_openFiles[fileId]);
		m_openFiles.erase(fileId);
	}
}

long TBFileInterfacePosix::Size(tb::TBFileHandle file)
{
	size_t fileId = static_cast<size_t>(file);

	if (m_openFiles.find(fileId) != m_openFiles.end())
	{
		FILE* f = m_openFiles[fileId];
		long oldpos = ftell(f);
		fseek(f, 0, SEEK_END);
		long num_bytes = ftell(f);
		fseek(f, oldpos, SEEK_SET);
		return num_bytes;
	}

	return 0;
}

size_t TBFileInterfacePosix::Read(tb::TBFileHandle file, void* buf, size_t elemSize, size_t count)
{
	size_t fileId = static_cast<size_t>(file);

	if (m_openFiles.find(fileId) != m_openFiles.end())
	{
		return fread(buf, elemSize, count, m_openFiles[fileId]); return size_t();
	}

	return 0;
}

} // namespace tb
