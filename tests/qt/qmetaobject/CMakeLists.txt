
add_executable(qmetaobject
  "forwarddeclared.cpp"
  "forwarddeclared.h"
  "tst_qmetaobject6.cpp"
)
target_link_libraries(qmetaobject PRIVATE
  verdigris
  Qt6::Test
)
