#pragma once

#include "Core/Log.h"
#include "Core/PlatformDetector.h"

#ifdef DEBUG
	#if defined(PLATFORM_WINDOWS)
		#define DEBUGBREAK() __debugbreak()
	#elif (defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS))
		#include <signal.h>
		#define DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define ASSERT(check, ...) { if(!(check)) { LOG_ERROR("Assertion Failed: ", __VA_ARGS__); DEBUGBREAK(); } }
#else
	#define DEBUGBREAK()
	#define ASSERT(...)
#endif
