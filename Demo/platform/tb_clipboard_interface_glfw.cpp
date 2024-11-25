#include "tb_types.h"
#include "tb_core.h"
#include "tb_clipboard_interface_glfw.h"
#include <stdlib.h>

#include "GLFW/glfw3.h"

void tb::TBClipboardInterfaceGlfw::Empty()
{
	SetText("");
}

bool tb::TBClipboardInterfaceGlfw::HasText()
{
	if (GLFWwindow* window = glfwGetCurrentContext())
	{
		const char* str = glfwGetClipboardString(window);
		if (str && *str)
			return true;
	}
	return false;
}

bool tb::TBClipboardInterfaceGlfw::SetText(const char* text)
{
	if (GLFWwindow* window = glfwGetCurrentContext())
	{
		glfwSetClipboardString(window, text);
		return true;
	}
	return false;
}

bool tb::TBClipboardInterfaceGlfw::GetText(tb::TBStr& text)
{
	if (GLFWwindow* window = glfwGetCurrentContext())
	{
		if (const char* str = glfwGetClipboardString(window))
			return text.Set(str);
	}
	return false;
}
