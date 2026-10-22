-- Used for Github Actions unit testing
local is_standalone = _ACTION and not _G.__root_workspace_defined

if is_standalone then
    _G.__root_workspace_defined = true

    workspace("MossDivided")
        language "C++"
        -- cppdialect "C++latest"
        architecture "x86_64"
        toolset "clang"

        buildoptions { "-std=c++20" } 

        location "scripts"
        flags { "MultiProcessorCompile" }
        configurations { "debug", "release" }

        startproject("mossSandbox") -- Helpful in IDE
end

project "mossSandbox"
    kind "ConsoleApp"
    location "scripts"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "build/%{cfg.buildcfg}/%{prj.name}"

    files { "src/gradient.cpp", "external/VkBootstrap.cpp" }
    includedirs {
        "include",
        "../extensions/include",
        "../core/include",
        "external",
        "$(VULKAN_SDK)/Include",
        "$(GLFW_ROOT)/Include"
    }

    libdirs {
        "../extensions/bin/debug",
        "external",
        "$(VULKAN_SDK)/Lib",
        "$(GLFW_ROOT)/lib-vc2022"
    }

    links {
        "mossExtensions",
        "vulkan-1",
        "glfw3",
        "User32",
        "Gdi32",
        "Shell32"
    }

    filter "configurations:debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:release"
        defines { "NDEBUG" }
        optimize "On"
