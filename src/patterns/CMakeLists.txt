set(DS_SOURCES

    # Structural Patterns
    ${CMAKE_CURRENT_SOURCE_DIR}/structural/Adapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/structural/Bridge.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/structural/Proxy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/structural/Composite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/structural/Flyweight.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/structural/Facade.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/structural/Decorator.cpp

    # Behavioral Patterns
    ${CMAKE_CURRENT_SOURCE_DIR}/behavioral/ChainOfCommand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/behavioral/Command.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/behavioral/Iterator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/behavioral/Mediator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/behavioral/Memento.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/behavioral/Visitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/behavioral/TemplateMethod.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/behavioral/Strategy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/behavioral/State.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/behavioral/Observer.cpp

    # Creational Patterns
    ${CMAKE_CURRENT_SOURCE_DIR}/creational/Singleton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/creational/FactoryMethod.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/creational/AbstractFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/creational/Builder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/creational/Prototype.cpp
)

set(DS_SOURCES ${DS_SOURCES} PARENT_SCOPE)