
#if !defined(TB_STATIC)
#	if defined (_MSC_VER)
#		define TB_DLLIMPORT __declspec(dllimport)
#		define TB_DLLEXPORT __declspec(dllexport)
#	else
#		define TB_DLLIMPORT __attribute__((visibility("default")))
#		define TB_DLLEXPORT __attribute__((visibility("default")))
#	endif
#else
#	define TB_DLLIMPORT
#	define TB_DLLEXPORT
#endif

#undef TB_API
#if defined(TB_COMPILING)
#	define TB_API TB_DLLEXPORT
#else
#	define TB_API TB_DLLIMPORT
#endif

#if defined (_MSC_VER)
// <type> needs to have dll-interface to be used by clients
#pragma warning(disable : 4251)
#endif