// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Seger�s      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================
#pragma once

#ifndef TB_FILE_INTERFACE_H
#define TB_FILE_INTERFACE_H

#include "tb_types.h"

namespace tb {
	class TBFileInterface
	{
	public:
        virtual ~TBFileInterface() = default;
		enum TBFileMode { MODE_READ };

		virtual TBFileHandle Open(const char* filename, TBFileMode mode) = 0;
		virtual void Close(TBFileHandle file) = 0;

		virtual long Size(TBFileHandle file) = 0;
		virtual size_t Read(TBFileHandle file, void* buf, size_t elemSize, size_t count) = 0;
	};
} // namespace tb

#endif // TB_FILE_INTERFACE_H