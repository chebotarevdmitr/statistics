cmake_minimum_required(VERSION 3.10) # Проверка версии CMake.
                                      # Если версия установленной программы
                                      # старее указанной, произойдёт аварийный выход.
                        
project(Statistics) # Название проекта

set(CMAKE_CXX_STANDARD 17) # Устанавливаем стандарт C++17

add_library(statistics_lib  # Создание статической библиотеки с именем statistics_lib
    src/Statistics.cpp
)

add_executable(statistics_app # Создание исполняемого файла с именем statistics_app
    src/main.cpp
)

target_include_directories(statistics_lib PUBLIC include) # Добавляем директорию include в список директорий для поиска заголовочных файлов
target_link_libraries(statistics_app statistics_lib) # Линковка программы с библиотекой
