project(
    'mmi-gui-praktikum',
    'cpp',
    version : '0.1',
    default_options : ['warning_level=3', 'cpp_std=c++20'],
)
cpp_args = []

doctest_include = include_directories('third_party/doctest')

executable(
    'praktikum2-2',
    'praktikum2/task2.cpp',
    include_directories : [doctest_include],
    cpp_args : cpp_args,
)
executable(
    'praktikum2-3',
    ['praktikum2/task3.cpp', 'praktikum2/Stack.cpp'],
    cpp_args : cpp_args,
    include_directories : [doctest_include],
)

# executable(
#   'praktikum3-1',
#   ['praktikum3/task1.cpp'],
#   cpp_args: cpp_args,
#   include_directories: [doctest_include],
# )
executable(
    'praktikum3-2',
    ['praktikum3/Volume.cpp'],
    cpp_args : cpp_args,
    include_directories : [doctest_include],
)
executable(
    'praktikum3-3',
    ['praktikum3/task3.cpp'],
    cpp_args : cpp_args,
    include_directories : [doctest_include],
)
executable(
    'praktikum4',
    ['praktikum4/tasks.cpp'],
    cpp_args : cpp_args,
    include_directories : [doctest_include],
)
