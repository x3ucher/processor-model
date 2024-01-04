# Указываем список исходных файлов для библиотеки myvector
set(SOURCE_FILES myvector.hpp)

# Создаем библиотеку с именем myvector
add_library(myvector ${SOURCE_FILES})

# Укажите язык связи (linker language) явно для цели "myvector"
set_target_properties(myvector PROPERTIES LINKER_LANGUAGE CXX)

# Указываем, что этот подпроект будет доступен другим подпроектам
target_include_directories(myvector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})