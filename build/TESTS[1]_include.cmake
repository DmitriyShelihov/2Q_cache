if(EXISTS "/home/dmitriy/Рабочий стол/Владос/2Q_cache/build/TESTS[1]_tests.cmake")
  include("/home/dmitriy/Рабочий стол/Владос/2Q_cache/build/TESTS[1]_tests.cmake")
else()
  add_test(TESTS_NOT_BUILT TESTS_NOT_BUILT)
endif()
