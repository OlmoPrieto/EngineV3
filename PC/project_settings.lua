#!lua

pd = "../Project"

-- A solution contains projects, and defines the available configurations
solution "Project"
  configurations { "Debug", "Release" }
  platforms { "native", "x64", "x32" }
  location ( "./" ) -- Location of the solutions
         
  -- Project
  project "Project"
    kind "ConsoleApp"
    language "C++"
    location ( pd .. "/" ) 
    targetdir (pd .. "/bin/")

    --buildoptions_cpp("-std=c++17")
    --buildoptions_objcpp("-std=c++17")
    
    includedirs { 
      pd .. "/include", 
      pd .. "/dependencies",
      pd .. "/dependencies/glew/include/",
      pd .. "/dependencies/GLFW/deps/",
    }
      
    -- INCLUDE FILES
    files { -- GLEW
      group = "GLEW", pd .. "/dependencies/glew/include/glew.c", 
    }
    
    files{ group = "include", pd .."/include/**.h" } -- include filter and get the files
    files{ group = "src", pd .."/src/**.cc", pd .."/src/**.cpp" } -- src filter and get the files
    excludes {
      -- temporal exclude until windows support for sockets is implemented
      pd .. "/include/sockets.h",
      pd .. "/src/sockets.cpp"
    }

    -- only when compiling as library
    --defines { "GLEW_STATIC" }
  
    configuration { "windows" }
      files {  -- GLFW
        group = "GLFW", 
          pd .. "/dependencies/GLFW/src/context.c", 
          pd .. "/dependencies/GLFW/src/init.c", 
          pd .. "/dependencies/GLFW/src/input.c",
          pd .. "/dependencies/GLFW/src/monitor.c",
          pd .. "/dependencies/GLFW/src/wgl_context.c",
          pd .. "/dependencies/GLFW/src/win32_init.c",
          pd .. "/dependencies/GLFW/src/win32_monitor.c",
          pd .. "/dependencies/GLFW/src/win32_time.c",
          pd .. "/dependencies/GLFW/src/win32_tls.c",
          pd .. "/dependencies/GLFW/src/win32_window.c",
          pd .. "/dependencies/GLFW/src/window.c",
          pd .. "/dependencies/GLFW/src/winmm_joystick.c",
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
          pd .. "/dependencies/GLFW/src/context.c", 
          pd .. "/dependencies/GLFW/src/init.c", 
          pd .. "/dependencies/GLFW/src/input.c",
          pd .. "/dependencies/GLFW/src/monitor.c",
          pd .. "/dependencies/GLFW/src/nsgl_context.m",
          pd .. "/dependencies/GLFW/src/cocoa_init.m",
          pd .. "/dependencies/GLFW/src/cocoa_monitor.m",
          pd .. "/dependencies/GLFW/src/mach_time.c",
          pd .. "/dependencies/GLFW/src/posix_tls.c",
          pd .. "/dependencies/GLFW/src/cocoa_window.m",
          pd .. "/dependencies/GLFW/src/window.c",
          pd .. "/dependencies/GLFW/src/iokit_joystick.m",
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
        	pd .. "/dependencies/GLFW/src/context.c", 
          pd .. "/dependencies/GLFW/src/init.c", 
          pd .. "/dependencies/GLFW/src/input.c",
          pd .. "/dependencies/GLFW/src/monitor.c",
          pd .. "/dependencies/GLFW/src/glx_context.c",
          pd .. "/dependencies/GLFW/src/x11_init.c",
          pd .. "/dependencies/GLFW/src/x11_monitor.c",
          pd .. "/dependencies/GLFW/src/posix_time.c",
          pd .. "/dependencies/GLFW/src/posix_tls.c",
          pd .. "/dependencies/GLFW/src/x11_window.c",
          pd .. "/dependencies/GLFW/src/window.c",
          pd .. "/dependencies/GLFW/src/linux_joystick.c",
          pd .. "/dependencies/GLFW/src/xkb_unicode.c",
      }
      links {
        "X11", "Xrandr", "Xcursor", "Xinerama", "Xi", "Xxf86vm", "rt", "pthread", "GL", "glut", "GLU", "m"
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