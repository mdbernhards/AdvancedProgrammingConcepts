add_test( custom.always_pass [==[/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week5/assignment_04/build/tests/list/tests_custom]==] [==[--gtest_filter=custom.always_pass]==] --gtest_also_run_disabled_tests)
set_tests_properties( custom.always_pass PROPERTIES WORKING_DIRECTORY [==[/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week5/assignment_04/build/tests/list]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( custom.empty_size [==[/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week5/assignment_04/build/tests/list/tests_custom]==] [==[--gtest_filter=custom.empty_size]==] --gtest_also_run_disabled_tests)
set_tests_properties( custom.empty_size PROPERTIES WORKING_DIRECTORY [==[/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week5/assignment_04/build/tests/list]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( tests_custom_TESTS custom.always_pass custom.empty_size)
