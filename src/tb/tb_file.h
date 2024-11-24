// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_FILE_H
#define TB_FILE_H

#include "tb_export.h"

namespace tb {
	/** TBFile is a porting interface for file access. */
	class TB_DLLCLASS TBFile
	{
	public:
		enum TBFileMode { MODE_READ };

		virtual ~TBFile() {}
		virtual long Size() = 0;
		virtual size_t Read(void* buf, size_t elemSize, size_t count) = 0;
	};

} // namespace tb

#endif // TB_FILE_H
