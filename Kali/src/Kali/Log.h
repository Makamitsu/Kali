#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Kali {

	class KALI_API Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return sCoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return sClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> sCoreLogger;
		static std::shared_ptr<spdlog::logger> sClientLogger;
	};

}

// Core log macros
#define KL_CORE_ERROR(...) ::Kali::Log::GetCoreLogger()->error(__VA_ARGS__)
#define KL_CORE_WARN(...)  ::Kali::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KL_CORE_INFO(...)  ::Kali::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KL_CORE_TRACE(...) ::Kali::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define KL_CORE_FATAL(...) ::Kali::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define KL_ERROR(...) ::Kali::Log::GetClientLogger()->error(__VA_ARGS__)
#define KL_WARN(...)  ::Kali::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KL_INFO(...)  ::Kali::Log::GetClientLogger()->info(__VA_ARGS__)
#define KL_TRACE(...) ::Kali::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KL_FATAL(...) ::Kali::Log::GetClientLogger()->fatal(__VA_ARGS__)
