workspace "Kali"
    architecture 'x64'

    configurations{
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glfw"] = "Kali/vendor/glfw/include"
IncludeDir["glad"] = "Kali/vendor/glad/include"
IncludeDir["glm"] = "Kali/vendor/glm"
IncludeDir["imgui"] = "Kali/vendor/imgui-docking"

include "Kali/vendor/imgui-docking"
include "Kali/vendor/glfw"
include "Kali/vendor/glad"

project "Kali"
    location "Kali"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

    pchheader "klpch.h"
    pchsource "Kali/src/klpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }
    
    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "glfw",
        "glad",
        "ImGui",
        "opengl32.lib"
    }
    
    filter "system:windows"
        systemversion "latest"

        defines
        {
            "KL_PLATFORM_WINDOWS",
            "KL_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
--            "_WINDLL"
        }

    filter "configurations:Debug"
        defines
        {
            "KL_DEBUG",
            "KL_ENABLE_ASSERTS"
        }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines
        {
            "KL_RELEASE",
            "KL_ENABLE_ASSERTS"
        }
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "KL_DIST"
        runtime "Release"
        optimize "on"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "Kali/vendor/spdlog/include",
        "%{IncludeDir.imgui}",
        "Kali/src",
        "%{IncludeDir.glm}"
    }
    
    links
    {
        "Kali"
    }

    filter "system:windows"

        systemversion "latest"

        defines
        {
            "KL_PLATFORM_WINDOWS",
--            "_WINDLL"
        }
    
    filter "configurations:Debug"
        defines {
            "KL_DEBUG",
            "KL_ENABLE_ASSERTS"
        }
        symbols "on"
        runtime "Debug"

    filter "configurations:Release"
        defines 
        {
            "KL_RELEASE",
            "KL_ENABLE_ASSERTS"
        }
        runtime "Release"
        optimize "on"
        --optimize "Size"
        --optimize "Speed"
        --optimize "Full"

    filter "configurations:Dist"
        defines "KL_DIST"
        runtime "Release"
        optimize "on"
