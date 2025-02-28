set_project("tiny_stl")

-- set xmake minimum version
set_xmakever("2.5.1")

add_includedirs("include")

target("tiny_stl")
    set_kind("binary")
    add_files("include/main.cpp")