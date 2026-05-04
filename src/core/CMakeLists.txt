# ----------------------------------------------------------------------------------------
# Core module source files
# This list contains all implementation files for the core module.
# The variable will be exported to the parent CMakeLists via PARENT_SCOPE.
# ----------------------------------------------------------------------------------------

set(CORE_SOURCES

    # Basic C++ language features
    ${CMAKE_CURRENT_SOURCE_DIR}/basics/InitializeVariable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/basics/Operations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/basics/TypeQualifier.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/basics/ControlFlow.cpp

    # Linkage (internal / external / shared symbols)
    ${CMAKE_CURRENT_SOURCE_DIR}/linkage/Internal.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/linkage/Linkage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/linkage/External.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/linkage/sharing/Sharing.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/linkage/sharing/external/constants.cpp

    # Fundamental data types
    ${CMAKE_CURRENT_SOURCE_DIR}/datatype/Fundamental.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datatype/Array.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datatype/Reference.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datatype/Pointer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datatype/Enum.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datatype/Struct.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datatype/Union.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datatype/TypeConVersions.cpp

    # Classes and object lifecycle
    ${CMAKE_CURRENT_SOURCE_DIR}/class/Friend.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/class/Constructor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/class/Destructor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/class/SallowDeepCopying.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/class/RoleOfThreeFiveZero.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/class/Relationship.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/class/VirtualBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/class/Binding.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/class/Encapsulation.cpp

    # String handling
    ${CMAKE_CURRENT_SOURCE_DIR}/string/StringFormatting.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/string/CString.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/string/StdString.cpp

    # Exception handling
    ${CMAKE_CURRENT_SOURCE_DIR}/exception/BasicHandle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/exception/ThrowNoexcept.cpp

    # Streams and file handling
    ${CMAKE_CURRENT_SOURCE_DIR}/filehandle/IOStream.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filehandle/StringStream.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filehandle/FileIO.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filehandle/Directory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filehandle/OutputFormatting.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filehandle/BinaryFileHandling.cpp

    # STL containers and expressions
    ${CMAKE_CURRENT_SOURCE_DIR}/container/sequence/Array.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/container/sequence/Vector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/container/unordered/UnorderedMap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/container/adapter/Queue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/container/adapter/Stack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/container/sequence/Deque.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/container/associative/Set.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/expression/Lambda.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/expression/FunctionPointer.cpp

    # Smart pointers
    ${CMAKE_CURRENT_SOURCE_DIR}/smart_pointer/Unique.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/smart_pointer/Shared.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/smart_pointer/Weak.cpp

    # Operator overloading
    ${CMAKE_CURRENT_SOURCE_DIR}/overloading/ArithmeticOperator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/overloading/IOOperator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/overloading/UnaryOperator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/overloading/ComparisonOperator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/overloading/InDecOperator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/overloading/SubscriptOperator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/overloading/ParenthesisOperator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/overloading/TypeCast.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/overloading/AssignmentOperator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/overloading/ClassMemberAccessOperator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/overloading/AllocationOperator.cpp

    # Date and time
    ${CMAKE_CURRENT_SOURCE_DIR}/datetime/Time.cpp

    # Concurrency
    ${CMAKE_CURRENT_SOURCE_DIR}/concurrency/ThreadManagement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/concurrency/SharingData.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/concurrency/RaceCondition.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/concurrency/ConditionVariable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/concurrency/FuturePromise.cpp

    # Utils
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/Algorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/TypeTrait.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/Optional.cpp
)

# Export CORE_SOURCES to the parent CMakeLists.txt
# so the main application target can use these sources
set(CORE_SOURCES ${CORE_SOURCES} PARENT_SCOPE)