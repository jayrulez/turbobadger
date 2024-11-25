// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================
#pragma once

#ifndef TB_SYSTEM_INTERFACE_H
#define TB_SYSTEM_INTERFACE_H

#include "tb_export.h"
#include "tb_str.h"
#include <cstdarg>

namespace tb {
	class TB_DLLCLASS TBSystemInterface
	{
	public:
        virtual ~TBSystemInterface() = default;
        
		// Debug

		virtual void DebugOut(const char* str) = 0;
		virtual void DebugPrint(const char* str, ...)
		{
			va_list args;
			va_start(args, str);
			tb::TBStr tmp; tmp.SetFormatted(str, args); DebugOut(tmp);
			va_end(args);
		}

		// Platform

		/** Get the system time in milliseconds since some undefined epoch. */
		virtual double GetTimeMS() = 0;

		/** Called when the need to call TBMessageHandler::ProcessMessages has changed due to changes in the
			message queue. fire_time is the new time is needs to be called.
			It may be 0 which means that ProcessMessages should be called asap (but NOT from this call!)
			It may also be TB_NOT_SOON which means that ProcessMessages doesn't need to be called. */
		virtual void RescheduleTimer(double fire_time) = 0;

		/** Get how many milliseconds it should take after a touch down event should generate a long click
			event. */
		virtual int GetLongClickDelayMS() = 0;

		/** Get how many pixels of dragging should start panning scrollable widgets. */
		virtual int GetPanThreshold() = 0;

		/** Get how many pixels a typical line is: The length that should be scrolled when turning a mouse
			wheel one notch. */
		virtual int GetPixelsPerLine() = 0;

		/** Get Dots Per Inch for the main screen. */
		virtual int GetDPI() = 0;
	};
} // namespace tb

#endif // TB_SYSTEM_INTERFACE_H