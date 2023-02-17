foreach(item ${LIST})
  execute_process(COMMAND ${CMAKE_COMMAND} -E echo ${item})
endforeach()
