if(EXISTS "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week5/assignment_04/build/lib_ds/list/tests_list[1]_tests.cmake")
  include("/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week5/assignment_04/build/lib_ds/list/tests_list[1]_tests.cmake")
else()
  add_test(tests_list_NOT_BUILT tests_list_NOT_BUILT)
endif()
