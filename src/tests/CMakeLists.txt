
foreach(PROG test_edge_undirected test_graph_node )
  file(GLOB ${PROG}_SOURCES ${PROG}*.cpp)
  add_executable(unit_${PROG} ${${PROG}_SOURCES})
  target_link_libraries(unit_${PROG} ugly)
  add_test(unit_${PROG} unit_${PROG})
  set_tests_properties(unit_${PROG} PROPERTIES LABELS "ugly")
endforeach(PROG)
