#if defined (_MSC_VER)
#	if !defined (TB_STATIC) && !defined (__CLR_VER)
#		define TB_DLLIMPORT __declspec(dllimport)
#		define TB_DLLEXPORT __declspec(dllexport)
#	endif
#else
#	if !defined(TB_STATIC)
#		define TB_DLLIMPORT __attribute__((visibility("default")))
#		define TB_DLLEXPORT __attribute__((visibility("default")))
#	endif
#endif

#if !defined(TB_DLLIMPORT)
#	define TB_DLLIMPORT
#endif
#if !defined(TB_DLLEXPORT)
#	define TB_DLLEXPORT
#endif

#undef TB_DLLCLASS
#if !defined(TB_EXPORT)
#define TB_DLLCLASS TB_DLLEXPORT
#else
#define TB_DLLCLASS TB_DLLIMPORT
#endif