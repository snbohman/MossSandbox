project "hexagon"
    kind "WindowedApp"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "build/%{cfg.buildcfg}"

    files { "hexagon/**.cpp" }
    includedirs { "hexagon/generated/include", "hexagon/user/include", "../mossCore/include", "entt" }
    libdirs { "../mossCore/bin/debug" }
    links { "mossCore", "raylib", "fmt" }


project "minimal"
    kind "WindowedApp"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "build/%{cfg.buildcfg}"

    files { "minimal/**.cpp" }
    includedirs { "minimal/generated/include", "minimal/user/include", "../mossCore/include", "entt" }
    libdirs { "../mossCore/bin/debug" }
    links { "mossCore", "raylib", "fmt" }
