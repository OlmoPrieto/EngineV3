#!lua

solution_dir = "../Project"
project_name = ""

-- A solution contains projects, and defines the available configurations
solution "Project"
  configurations { "Debug", "Release" }
  platforms { "native", "x64", "x32" }
  location ( "./" ) -- Location of the solutions

-- =======================================================================
  -- Project
  project "Game"
    project_name = "Game"
    kind "ConsoleApp"
    language "C++"
    location  (solution_dir .. "/") 
    targetdir (solution_dir .. "/bin/")

    --buildoptions_cpp("-std=c++17")
    --buildoptions_objcpp("-std=c++17")
    
    includedirs { 
      solution_dir .. "/include", 
      solution_dir .. "/dependencies",
      solution_dir .. "/dependencies/glew/include/",
      solution_dir .. "/dependencies/GLFW/deps/"
    }
      
    -- INCLUDE FILES
    files { -- GLEW
      group = "GLEW", solution_dir .. "/dependencies/glew/include/glew.c", 
    }
    
    --files{ group = "include", solution_dir .."/include/**.h" } -- include filter and get the files
    files{ group = "include/" .. project_name, solution_dir .. "/include/" .. project_name .. "/**.h" }
    files{ group = "src", solution_dir .."/src/**.cc", solution_dir .."/src/**.cpp" } -- src filter and get the files
    files{ group = "src/Game", solution_dir .."/src/" .. project_name .. "/**.cc", solution_dir .."/src/" .. project_name .."/**.cpp" }

    excludes {
      -- temporal exclude until windows support for sockets is implemented
      solution_dir .. "/include/Engine/sockets.h",
      solution_dir .. "/src/Engine/sockets.cpp"
    }

    -- only when compiling as library
    --defines { "GLEW_STATIC" }
  
    configuration { "windows" }
      files {  -- GLFW
        group = "GLFW", 
          solution_dir .. "/dependencies/GLFW/src/context.c", 
          solution_dir .. "/dependencies/GLFW/src/init.c", 
          solution_dir .. "/dependencies/GLFW/src/input.c",
          solution_dir .. "/dependencies/GLFW/src/monitor.c",
          solution_dir .. "/dependencies/GLFW/src/wgl_context.c",
          solution_dir .. "/dependencies/GLFW/src/win32_init.c",
          solution_dir .. "/dependencies/GLFW/src/win32_monitor.c",
          solution_dir .. "/dependencies/GLFW/src/win32_time.c",
          solution_dir .. "/dependencies/GLFW/src/win32_tls.c",
          solution_dir .. "/dependencies/GLFW/src/win32_window.c",
          solution_dir .. "/dependencies/GLFW/src/window.c",
          solution_dir .. "/dependencies/GLFW/src/winmm_joystick.c",
      }
      
      links {
        "opengl32"
      }
      defines { "__PLATFORM_WINDOWS__","_GLFW_WIN32", "_GLFW_WGL", "_GLFW_USE_OPENGL" }
      buildoptions_cpp("/Y-")
      buildoptions_cpp("/std:c++17")
      windowstargetplatformversion "10.0.15063.0"
       
    configuration { "macosx" }
      files {  -- GLFW
        group = "GLFW", 
          solution_dir .. "/dependencies/GLFW/src/context.c", 
          solution_dir .. "/dependencies/GLFW/src/init.c", 
          solution_dir .. "/dependencies/GLFW/src/input.c",
          solution_dir .. "/dependencies/GLFW/src/monitor.c",
          solution_dir .. "/dependencies/GLFW/src/nsgl_context.m",
          solution_dir .. "/dependencies/GLFW/src/cocoa_init.m",
          solution_dir .. "/dependencies/GLFW/src/cocoa_monitor.m",
          solution_dir .. "/dependencies/GLFW/src/mach_time.c",
          solution_dir .. "/dependencies/GLFW/src/posix_tls.c",
          solution_dir .. "/dependencies/GLFW/src/cocoa_window.m",
          solution_dir .. "/dependencies/GLFW/src/window.c",
          solution_dir .. "/dependencies/GLFW/src/iokit_joystick.m",
      }
      links  {
        "Cocoa.framework", "OpenGL.framework", "IOKit.framework", "CoreVideo.framework",
      }
      linkoptions { "-framework Cocoa","-framework QuartzCore", "-framework OpenGL", "-framework OpenAL" }
      buildoptions_cpp("-std=c++17")
      buildoptions_objcpp("-std=c++17")
      defines { "__PLATFORM_MACOSX__", "_GLFW_COCOA", "_GLFW_NSGL", "_GLFW_USE_OPENGL" }
       
    configuration { "linux" }
      files {  -- GLFW
        group = "GLFW", 
        	solution_dir .. "/dependencies/GLFW/src/context.c", 
          solution_dir .. "/dependencies/GLFW/src/init.c", 
          solution_dir .. "/dependencies/GLFW/src/input.c",
          solution_dir .. "/dependencies/GLFW/src/monitor.c",
          solution_dir .. "/dependencies/GLFW/src/glx_context.c",
          solution_dir .. "/dependencies/GLFW/src/x11_init.c",
          solution_dir .. "/dependencies/GLFW/src/x11_monitor.c",
          solution_dir .. "/dependencies/GLFW/src/posix_time.c",
          solution_dir .. "/dependencies/GLFW/src/posix_tls.c",
          solution_dir .. "/dependencies/GLFW/src/x11_window.c",
          solution_dir .. "/dependencies/GLFW/src/window.c",
          solution_dir .. "/dependencies/GLFW/src/linux_joystick.c",
          solution_dir .. "/dependencies/GLFW/src/xkb_unicode.c",
      }
      links {
        -- https://stackoverflow.com/questions/33149878/experimentalfilesystem-linker-error
        "X11", "Xrandr", "Xcursor", "Xinerama", "Xi", "Xxf86vm", "rt", "pthread", "GL", "glut", "GLU", "m", "stdc++fs"
      }
      includedirs {
        "/usr/include/GL/"
      }
      libdirs {
        "/usr/bin/",
        "/usr/lib/"
      }
      buildoptions_cpp("-std=c++17")
      buildoptions_objcpp("-std=c++17")
      defines { "__PLATFORM_LINUX__", "_GLFW_X11", "_GLFW_HAS_GLXGETPROCADDRESS", "_GLFW_GLX", "_GLFW_USE_OPENGL" }

    configuration "debug"
      defines { "DEBUG" }
      flags { "Symbols", "ExtraWarnings"}

    configuration "release"
      defines { "NDEBUG" }
      flags { "Optimize", "ExtraWarnings" }

-- =======================================================================

  -- Project
  project "Engine"
    project_name = "Engine"
    kind "StaticLib"
    language "C++"
    location  (solution_dir .. "/") 
    targetdir (solution_dir .. "/bin/")

    --buildoptions_cpp("-std=c++17")
    --buildoptions_objcpp("-std=c++17")
    
    includedirs { 
      solution_dir .. "/include", 
      solution_dir .. "/dependencies",
      solution_dir .. "/dependencies/glew/include/",
      solution_dir .. "/dependencies/GLFW/deps/"
    }
      
    -- INCLUDE FILES
    files { -- GLEW
      group = "GLEW", solution_dir .. "/dependencies/glew/include/glew.c", 
    }
    
    --files{ group = "include", solution_dir .."/include/**.h" } -- include filter and get the files
    files{ group = "include/" .. project_name, solution_dir .. "/include/" .. project_name .. "/**.h" }
    files{ group = "src/Game", solution_dir .."/src/" .. project_name .. "/**.cc", solution_dir .."/src/" .. project_name .."/**.cpp" }

    excludes {
      -- temporal exclude until windows support for sockets is implemented
      solution_dir .. "/include/Engine/sockets.h",
      solution_dir .. "/src/Engine/sockets.cpp"
    }

    -- only when compiling as library
    defines { "GLEW_STATIC" }
  
    configuration { "windows" }
      files {  -- GLFW
        group = "GLFW", 
          solution_dir .. "/dependencies/GLFW/src/context.c", 
          solution_dir .. "/dependencies/GLFW/src/init.c", 
          solution_dir .. "/dependencies/GLFW/src/input.c",
          solution_dir .. "/dependencies/GLFW/src/monitor.c",
          solution_dir .. "/dependencies/GLFW/src/wgl_context.c",
          solution_dir .. "/dependencies/GLFW/src/win32_init.c",
          solution_dir .. "/dependencies/GLFW/src/win32_monitor.c",
          solution_dir .. "/dependencies/GLFW/src/win32_time.c",
          solution_dir .. "/dependencies/GLFW/src/win32_tls.c",
          solution_dir .. "/dependencies/GLFW/src/win32_window.c",
          solution_dir .. "/dependencies/GLFW/src/window.c",
          solution_dir .. "/dependencies/GLFW/src/winmm_joystick.c",
      }
      
      links {
        "opengl32"
      }
      defines { "__PLATFORM_WINDOWS__","_GLFW_WIN32", "_GLFW_WGL", "_GLFW_USE_OPENGL" }
      buildoptions_cpp("/Y-")
      buildoptions_cpp("/std:c++17")
      windowstargetplatformversion "10.0.15063.0"
       
    configuration { "macosx" }
      files {  -- GLFW
        group = "GLFW", 
          solution_dir .. "/dependencies/GLFW/src/context.c", 
          solution_dir .. "/dependencies/GLFW/src/init.c", 
          solution_dir .. "/dependencies/GLFW/src/input.c",
          solution_dir .. "/dependencies/GLFW/src/monitor.c",
          solution_dir .. "/dependencies/GLFW/src/nsgl_context.m",
          solution_dir .. "/dependencies/GLFW/src/cocoa_init.m",
          solution_dir .. "/dependencies/GLFW/src/cocoa_monitor.m",
          solution_dir .. "/dependencies/GLFW/src/mach_time.c",
          solution_dir .. "/dependencies/GLFW/src/posix_tls.c",
          solution_dir .. "/dependencies/GLFW/src/cocoa_window.m",
          solution_dir .. "/dependencies/GLFW/src/window.c",
          solution_dir .. "/dependencies/GLFW/src/iokit_joystick.m",
      }
      links  {
        "Cocoa.framework", "OpenGL.framework", "IOKit.framework", "CoreVideo.framework",
      }
      linkoptions { "-framework Cocoa","-framework QuartzCore", "-framework OpenGL", "-framework OpenAL" }
      buildoptions_cpp("-std=c++17")
      buildoptions_objcpp("-std=c++17")
      defines { "__PLATFORM_MACOSX__", "_GLFW_COCOA", "_GLFW_NSGL", "_GLFW_USE_OPENGL" }
       
    configuration { "linux" }
      files {  -- GLFW
        group = "GLFW", 
          solution_dir .. "/dependencies/GLFW/src/context.c", 
          solution_dir .. "/dependencies/GLFW/src/init.c", 
          solution_dir .. "/dependencies/GLFW/src/input.c",
          solution_dir .. "/dependencies/GLFW/src/monitor.c",
          solution_dir .. "/dependencies/GLFW/src/glx_context.c",
          solution_dir .. "/dependencies/GLFW/src/x11_init.c",
          solution_dir .. "/dependencies/GLFW/src/x11_monitor.c",
          solution_dir .. "/dependencies/GLFW/src/posix_time.c",
          solution_dir .. "/dependencies/GLFW/src/posix_tls.c",
          solution_dir .. "/dependencies/GLFW/src/x11_window.c",
          solution_dir .. "/dependencies/GLFW/src/window.c",
          solution_dir .. "/dependencies/GLFW/src/linux_joystick.c",
          solution_dir .. "/dependencies/GLFW/src/xkb_unicode.c",
      }
      links {
        -- https://stackoverflow.com/questions/33149878/experimentalfilesystem-linker-error
        "X11", "Xrandr", "Xcursor", "Xinerama", "Xi", "Xxf86vm", "rt", "pthread", "GL", "glut", "GLU", "m", "stdc++fs"
      }
      includedirs {
        "/usr/include/GL/"
      }
      libdirs {
        "/usr/bin/",
        "/usr/lib/"
      }
      buildoptions_cpp("-std=c++17")
      buildoptions_objcpp("-std=c++17")
      defines { "__PLATFORM_LINUX__", "_GLFW_X11", "_GLFW_HAS_GLXGETPROCADDRESS", "_GLFW_GLX", "_GLFW_USE_OPENGL" }

    configuration "debug"
      defines { "DEBUG" }
      flags { "Symbols", "ExtraWarnings"}

    configuration "release"
      defines { "NDEBUG" }
      flags { "Optimize", "ExtraWarnings" }