﻿cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME TransformProcessor)

project(${PROJECT_NAME})

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../)

add_library(_transform SHARED
    IniFileParserInterface.h
    FeatureEvaluator.h
    TransformProcessorFeatureMap.h
    IniFileParserInterface.cpp
    FeatureEvaluator.cpp
    TransformProcessorFeatureMap.cpp
    TransformProcessor.h
    TransformProcessor.cpp
    )

target_include_directories(_transform PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../NeuralTreeEvaluator.Library/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../NeuralTree.Library/inc
    )

target_link_libraries(_transform
    -Wl,--no-as-needed
    -Wl,--start-group
    -lpthread
    -lz
    -ldl
    -ltinfo
    DRNeuralTreeLibrary
    DRFreeFormLlvmBackendLibrary
    DRFreeFormSharedLibrary
    DRFreeFormExpressionLibrary
    DRFreeFormTransformLibrary
    DRFreeFormSExpressionLibrary
    DRFreeFormLibrary
    NeuralTreeEvaluatorLibrary
    ${Boost_LIBRARIES}
    ${LLVM_LIB}
    -Wl,--end-group
    )
