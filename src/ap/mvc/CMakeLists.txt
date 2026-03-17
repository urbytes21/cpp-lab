add_executable(mvc_ap)

target_sources(mvc_ap
    PRIVATE
    mvc_ap.cpp
    model/SharedData.cpp
    view/EditorWidget.cpp
    view/DisplayWidget.cpp
    controller/Controller.cpp
)

target_link_libraries(mvc_ap PRIVATE gtk4-settings)