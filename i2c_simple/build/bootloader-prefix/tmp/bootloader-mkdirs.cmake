# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/esp-idf/components/bootloader/subproject"
  "D:/esp-idf/examples/peripherals/i2c/i2c_simple/build/bootloader"
  "D:/esp-idf/examples/peripherals/i2c/i2c_simple/build/bootloader-prefix"
  "D:/esp-idf/examples/peripherals/i2c/i2c_simple/build/bootloader-prefix/tmp"
  "D:/esp-idf/examples/peripherals/i2c/i2c_simple/build/bootloader-prefix/src/bootloader-stamp"
  "D:/esp-idf/examples/peripherals/i2c/i2c_simple/build/bootloader-prefix/src"
  "D:/esp-idf/examples/peripherals/i2c/i2c_simple/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/esp-idf/examples/peripherals/i2c/i2c_simple/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
