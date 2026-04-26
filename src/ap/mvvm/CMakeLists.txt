add_executable(mvvm_ap)

target_sources(mvvm_ap
    PRIVATE
        mvvm_ap.cpp
        model/SharedData.cpp
        viewmodel/SharedDataVM.cpp
        view/EditorWidget.cpp
        view/DisplayWidget.cpp
)

target_link_libraries(mvvm_ap PRIVATE gtk4-settings)