workspace "softbody"
    configurations { "debug", "release" }
    architecture "x86_64"

project "softbody"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "build/%{cfg.buildcfg}"

    files { "src/**.cpp" }
    includedirs { "include", "entt", "glm", "json" }
    links { "raylib", "fmt" }

    filter "configurations:debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:release"
        defines { "NDEBUG" }
        optimize "On"
