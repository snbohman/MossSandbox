workspace "mossSandbox"
    configurations { "debug", "release" }
    architecture "x86_64"
    includedirs { "moss/include", "entt" }
    links { "raylib", "fmt" }

    project "moss"
        kind "StaticLib"
        language "C++"
        cppdialect "C++17"
        targetdir "bin/%{cfg.buildcfg}"
        objdir "build/%{cfg.buildcfg}"

        files { "moss/src/**.cpp" }

        filter "configurations:debug"
            defines { "DEBUG" }
            symbols "On"

        filter "configurations:release"
            defines { "NDEBUG" }
            optimize "On"

    project "hexagon"
        kind "WindowedApp"
        language "C++"
        cppdialect "C++17"
        targetdir "bin/%{cfg.buildcfg}"
        objdir "build/%{cfg.buildcfg}"

        files { "hexagon/src/**.cpp" }
        includedirs { "hexagon/include" }
        links { "moss" }

        filter "configurations:debug"
            defines { "DEBUG" }
            symbols "On"

        filter "configurations:release"
            defines { "NDEBUG" }
            optimize "On"
