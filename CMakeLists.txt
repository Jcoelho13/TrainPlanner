cmake_minimum_required(VERSION 3.24)
project(DATP1)

set(CMAKE_CXX_STANDARD 17)

add_executable(DATP1 main.cpp DataStructures/Graph.cpp DataStructures/Heap.cpp DataStructures/MutablePriorityQueue.h DataStructures/VertexEdge.cpp headers/Station.h cpps/Station.cpp DataStructures/UFDS.h)
