## This file should be placed in the root directory of your project.
## Then modify the CMakeLists.txt file in the root directory of your
## project to incorporate the testing dashboard.
## # The following are required to uses Dart and the Cdash dashboard
##   ENABLE_TESTING()
##   INCLUDE(Dart)

set(CTEST_PROJECT_NAME "MERCURY_POSIX")
set(CTEST_NIGHTLY_START_TIME "00:00:00 CST")

set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "cdash.hdfgroup.uiuc.edu")
set(CTEST_DROP_LOCATION "/submit.php?project=MERCURY_POSIX")
set(CTEST_DROP_SITE_CDASH TRUE)

