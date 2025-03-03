workspace "moss"
    configurations { "debug", "release" }
    architecture "x86_64"
    location "scripts"
    toolset "clang"
    buildoptions { "-Wno-macro-redefined"}

    includedirs { "../mossCore/include", "entt" }
    libdirs { "../mossCore/bin/debug" }
    links { "mossCore", "raylib", "fmt" }

    project "hexagon"
        kind "WindowedApp"
        language "C++"
        cppdialect "C++17"
        targetdir "bin/%{cfg.buildcfg}"
        objdir "build/%{cfg.buildcfg}"

        files { "hexagon/**.cpp" }
        includedirs { "hexagon/generated/include", "hexagon/user/include" }

        filter "configurations:debug"
            defines { "DEBUG" }
            symbols "On"

        filter "configurations:release"
            defines { "NDEBUG" }
            optimize "On"
