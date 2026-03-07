set(DS_SOURCES

    # Structural Patterns
    structural/Adapter.cpp
    structural/Bridge.cpp
    structural/Proxy.cpp
    structural/Composite.cpp
    structural/Flyweight.cpp
    structural/Facade.cpp
    structural/Decorator.cpp

    # Behavioral Patterns
    behavioral/ChainOfCommand.cpp
    behavioral/Command.cpp
    behavioral/Iterator.cpp
    behavioral/Mediator.cpp
    behavioral/Memento.cpp
    behavioral/Visitor.cpp
    behavioral/TemplateMethod.cpp
    behavioral/Strategy.cpp
    behavioral/State.cpp
    behavioral/Observer.cpp

    # Creational Patterns
    creational/Singleton.cpp
    creational/FactoryMethod.cpp
    creational/AbstractFactory.cpp
    creational/Builder.cpp
    creational/Prototype.cpp
)

set(DS_SOURCES ${DS_SOURCES} PARENT_SCOPE)