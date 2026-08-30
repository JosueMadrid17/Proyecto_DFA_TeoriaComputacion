cmake_minimum_required(VERSION 3.19)
project(Proyecto_DFA_TeoriaComputacion LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Proyecto_DFA_TeoriaComputacion
    WIN32 MACOSX_BUNDLE
    main.cpp
    InterfazVisual/VentanaPrincipal.cpp
    InterfazVisual/VentanaPrincipal.h
    Estructuras/CadenaManual.h
    Estructuras/CadenaManual.cpp
    Estructuras/Nodo.h
    Estructuras/ListaEnlazada.h
    Automatas/Estado.h
    Automatas/Estado.cpp
    Automatas/Simbolo.h Automatas/Simbolo.cpp
    Automatas/Transicion.h Automatas/Transicion.cpp
    Automatas/Automata.h Automatas/Automata.cpp
    Validacion/ErrorValidacion.h Validacion/ErrorValidacion.cpp
    Validacion/ResultadoValidacion.h Validacion/ResultadoValidacion.cpp
    Validacion/ValidadorDFA.h Validacion/ValidadorDFA.cpp
    InterfazVisual/PaginaCrearAutomata.h InterfazVisual/PaginaCrearAutomata.cpp
    InterfazVisual/VistaAutomata.h InterfazVisual/VistaAutomata.cpp
    Automatas/RegistroAutomatas.h Automatas/RegistroAutomatas.cpp
    Operaciones/EstadoCompuesto.h Operaciones/EstadoCompuesto.cpp
    Operaciones/OperacionUnion.h Operaciones/OperacionUnion.cpp
    InterfazVisual/PaginaUnionAutomatas.h InterfazVisual/PaginaUnionAutomatas.cpp
    Procesamiento/PasoProcesamiento.h Procesamiento/PasoProcesamiento.cpp
    Procesamiento/ResultadoProcesamiento.h Procesamiento/ResultadoProcesamiento.cpp
    Procesamiento/ProcesadorCadenas.h Procesamiento/ProcesadorCadenas.cpp
    InterfazVisual/PaginaPruebaCadenas.h InterfazVisual/PaginaPruebaCadenas.cpp
)

target_link_libraries(Proyecto_DFA_TeoriaComputacion
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS Proyecto_DFA_TeoriaComputacion
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Proyecto_DFA_TeoriaComputacion
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
