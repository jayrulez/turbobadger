// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================
#pragma once

#ifndef TB_CONTEXT_H
#define TB_CONTEXT_H

#include "tb_export.h"
#include "tb_types.h"

namespace tb {

	class TBWidget;

	class TB_DLLCLASS TBContext
	{
	public:
		// TBWidget related globals
		TBWidget* hovered_widget;	///< The currently hovered widget, or nullptr.
		TBWidget* captured_widget;	///< The currently captured widget, or nullptr.
		TBWidget* focused_widget;	///< The currently focused widget, or nullptr.
		int pointer_down_widget_x;	///< Pointer x position on down event, relative to the captured widget.
		int pointer_down_widget_y;	///< Pointer y position on down event, relative to the captured widget.
		int pointer_move_widget_x;	///< Pointer x position on last pointer event, relative to the captured widget (if any) or hovered widget.
		int pointer_move_widget_y;	///< Pointer y position on last pointer event, relative to the captured widget (if any) or hovered widget.
		bool cancel_click;			///< true if the pointer up event should not generate a click event.
		bool update_widget_states;	///< true if something has called InvalidateStates() and it still hasn't been updated.
		bool update_skin_states;		///< true if something has called InvalidateStates() and skin still hasn't been updated.
		bool show_focus_state;		///< true if the focused state should be painted automatically.
	};
} // namespace tb

#endif // TB_CONTEXT_H