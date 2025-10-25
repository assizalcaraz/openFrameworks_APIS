#!/bin/bash

# Script de inicio rápido para Pokemon API - openFrameworks
# Este script facilita el desarrollo y ejecución del proyecto

set -e  # Salir si hay algún error

# Colores para output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${GREEN}Pokemon API - openFrameworks${NC}"
echo "=============================="
echo ""

# Función para mostrar ayuda
show_help() {
    echo -e "${YELLOW}Uso: ./start.sh [comando]${NC}"
    echo ""
    echo "Comandos disponibles:"
    echo "  setup     - Configurar entorno completo"
    echo "  build     - Compilar la aplicación"
    echo "  run       - Ejecutar la aplicación"
    echo "  debug     - Compilar en modo debug"
    echo "  release   - Compilar en modo release"
    echo "  clean     - Limpiar archivos de compilación"
    echo "  status    - Mostrar estado del proyecto"
    echo "  help      - Mostrar esta ayuda"
    echo ""
    echo "Ejemplos:"
    echo "  ./start.sh setup    # Configurar todo"
    echo "  ./start.sh build    # Solo compilar"
    echo "  ./start.sh run      # Compilar y ejecutar"
    echo "  ./start.sh status   # Ver estado"
}

# Función para verificar dependencias
check_dependencies() {
    echo -e "${YELLOW}🔍 Verificando dependencias...${NC}"
    
    # Verificar Git
    if ! command -v git &> /dev/null; then
        echo -e "${RED}❌ Git no está instalado${NC}"
        exit 1
    fi
    
    # Verificar Make
    if ! command -v make &> /dev/null; then
        echo -e "${RED}❌ Make no está instalado${NC}"
        exit 1
    fi
    
    echo -e "${GREEN}✅ Dependencias básicas encontradas${NC}"
}

# Función para configurar el entorno
setup_environment() {
    echo -e "${YELLOW}🔧 Configurando entorno...${NC}"
    
    # Crear directorios necesarios
    mkdir -p logs
    mkdir -p bin
    mkdir -p addons
    
    # Hacer el script ejecutable
    chmod +x start.sh
    
    echo -e "${GREEN}✅ Entorno configurado${NC}"
}

# Función principal
main() {
    case "${1:-help}" in
        "setup")
            check_dependencies
            setup_environment
            make -f Makefile.dev setup
            ;;
        "build")
            make -f Makefile.dev build
            ;;
        "run")
            make -f Makefile.dev run
            ;;
        "debug")
            make -f Makefile.dev debug
            ;;
        "release")
            make -f Makefile.dev release
            ;;
        "clean")
            make -f Makefile.dev clean
            ;;
        "status")
            make -f Makefile.dev status
            ;;
        "help"|*)
            show_help
            ;;
    esac
}

# Ejecutar función principal
main "$@"
