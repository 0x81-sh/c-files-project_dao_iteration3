cmake_minimum_required(VERSION 3.17)
project(product_dao_iteration3 C)

set(CMAKE_C_STANDARD 99)

add_executable(product_dao_iteration3 main.c product.c product.h product_dao.c product_dao.h backend.c backend.h)