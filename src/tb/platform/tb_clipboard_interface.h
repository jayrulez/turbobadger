// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================
#pragma once

#ifndef TB_CLIPBOARD_INTERFACE_H
#define TB_CLIPBOARD_INTERFACE_H

#include "tb_str.h"

namespace tb {
	class TBClipboardInterface
	{
	public:
		virtual ~TBClipboardInterface() = default;
        
		/** Empty the contents of the clipboard. */
		virtual void Empty() = 0;

		/** Return true if the clipboard currently contains text. */
		virtual bool HasText() = 0;

		/** Set the text of the clipboard in UTF-8 format. */
		virtual bool SetText(const char* text) = 0;

		/** Get the text from the clipboard in UTF-8 format.
			Returns true on success. */
		virtual bool GetText(TBStr& text) = 0;
	};
} // namespace tb

#endif // TB_CLIPBOARD_INTERFACE_H