project(
  'mmi-gui-praktikum',
  'cpp',
  version: '0.1',
  default_options: ['warning_level=3', 'cpp_std=c++14'],
)

doctest_include = include_directories('third_party/doctest')

executable(
  'praktikum2-2',
  'praktikum2/task2.cpp',
  include_directories: [doctest_include],
)
executable(
  'praktikum2-3',
  ['praktikum2/task3.cpp', 'praktikum2/Stack.cpp'],

  include_directories: [doctest_include],
)