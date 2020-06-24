add_executable(tests
    tests.cpp
    graph.cpp
    )

add_executable(bell
    run_bellmann_ford.cpp
    graph.cpp
    )

# generate compile_commands.json
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
