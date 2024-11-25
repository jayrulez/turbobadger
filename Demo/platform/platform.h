#if defined(__linux) || defined(__linux__)
#	define TB_TARGET_LINUX
#elif MACOSX
#	define TB_TARGET_MACOSX
#elif defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
#	define TB_TARGET_WINDOWS
#endif