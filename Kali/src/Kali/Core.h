#pragma once

#ifdef KL_PLATFORM_WINDOWS
	#if HZ_DYNAMIC_LINK
		#ifdef KL_BUILD_DLL
			#define KALI_API __declspec(dllexport)
		#else
			#define KALI_API __declspec(dllimport)
		#endif
	#else
		#define KALI_API
	#endif
#else
	#error KALI is window only
#endif

#ifdef KL_ENABLE_ASSERTS
	#define KL_ASSERT(x, ...) {if(!x){KL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define KL_CORE_ASSERT(x, ...) {if(!x){KL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define KL_ASSERT(x, ...) {}
	#define KL_CORE__ASSERT(x, ...) {}
#endif

#define BIT(x) (1 << x)

#define KL_BIND_EVENT_FN(fn) std::bind(&(fn), this, std::placeholders::_1)
#define KL_BIND_EVENT_LAMBDA(dispatcher, eventType, function) dispatcher.Dispatch<eventType>([&](eventType event)->bool {return (function)(event); });


