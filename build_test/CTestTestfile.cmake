# CMake generated Testfile for 
# Source directory: /home/user/vds_class_project/vdscp04
# Build directory: /home/user/vds_class_project/vdscp04/build_test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(VDSProject_Test "/home/user/vds_class_project/vdscp04/build_test/run_tests")
set_tests_properties(VDSProject_Test PROPERTIES  _BACKTRACE_TRIPLES "/home/user/vds_class_project/vdscp04/CMakeLists.txt;60;add_test;/home/user/vds_class_project/vdscp04/CMakeLists.txt;0;")
subdirs("/home/user/vds_class_project/vdscp04/gtest/googletest-build")
subdirs("src")
