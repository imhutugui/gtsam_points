find_path(Iridescence_INCLUDE_DIRS glk/drawable.hpp
  HINTS D:/Programs/iridescence/include/iridescence
  DOC "Iridescence include directories")

find_library(Iridescence_LIBRARY NAMES iridescence
  HINTS D:/Programs/iridescence/lib
  DOC "Iridescence libraries")

  # find_library(gl_imgui_LIBRARY NAMES gl_imgui
  # HINTS D:/Programs/iridescence/lib
  # DOC "Iridescence libraries")

#set(Iridescence_INCLUDE_DIRS D:/Programs/iridescene/include)
set(Iridescence_LIBRARIES ${Iridescence_LIBRARY})
message("Iridescene: "  ${Iridescence_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Iridescence DEFAULT_MSG Iridescence_INCLUDE_DIRS Iridescence_LIBRARIES)
