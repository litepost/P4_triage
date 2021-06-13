cmake_minimum_required(VERSION 3.17)
project(P4_triage)

set(CMAKE_CXX_STANDARD 14)

add_executable(P4_triage p4.cpp Patient.cpp Patient.h PatientPriorityQueue.cpp PatientPriorityQueue.h)