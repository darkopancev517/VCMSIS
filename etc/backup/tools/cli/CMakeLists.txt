add_library(vc-cli
  cli.c
)

target_include_directories(vc-cli
  PUBLIC
    ${VC_PUBLIC_INCLUDES}
)

target_link_libraries(vc-cli PRIVATE vc-config)

target_compile_options(vc-cli PRIVATE
  ${VC_CFLAGS}
)
