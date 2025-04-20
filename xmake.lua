set_project("tiny_stl")

-- set xmake minimum version
set_xmakever("2.5.1")
set_languages("cxx17")


target("tiny_stl")
    set_kind("binary")
    add_includedirs("src")
    add_files("src/main.cpp")