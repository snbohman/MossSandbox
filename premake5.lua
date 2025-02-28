workspace "mossSandbox"
    configurations { "debug", "release" }
    architecture "x86_64"
    location "scripts"
    includedirs { "moss/include", "entt" }
    links { "raylib", "fmt" }

    -- project "rls"
    --     kind "StaticLib"
    --     language "C++"
    --     cppdialect "C++17"
    --     targetdir "bin/%{cfg.buildcfg}"
    --     objdir "build/%{cfg.buildcfg}"
    --
    --     files { "rls/src/**.cpp" }
    --     includedirs { "rls/include" }
    --
    --     filter "configurations:debug"
    --         defines { "DEBUG" }
    --         symbols "On"
    --
    --     filter "configurations:release"
    --         defines { "NDEBUG" }
    --         optimize "On"

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
