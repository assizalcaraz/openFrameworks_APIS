#!/bin/bash

# Script para compilar y ejecutar la aplicación Pokemon API

set -e  # Salir si hay algún error

echo "🎮 Pokemon API - openFrameworks"
echo "================================"

# Verificar que openFrameworks esté configurado
if [ -z "$OF_ROOT" ]; then
    echo "❌ OF_ROOT no está configurado"
    echo "Por favor configura OF_ROOT en config.make o como variable de entorno"
    exit 1
fi

echo "✅ openFrameworks encontrado en: $OF_ROOT"

# Verificar que los addons estén instalados
echo "🔍 Verificando addons..."

ADDONS_DIR="addons"
REQUIRED_ADDONS=("ofxJSON" "ofxHTTP" "ofxNetworkUtils")

for addon in "${REQUIRED_ADDONS[@]}"; do
    if [ -d "$ADDONS_DIR/$addon" ]; then
        echo "✅ $addon encontrado"
    else
        echo "❌ $addon no encontrado"
        echo "Instalando $addon..."
        
        case $addon in
            "ofxJSON")
                git clone https://github.com/jeffcrouse/ofxJSON.git "$ADDONS_DIR/$addon"
                ;;
            "ofxHTTP")
                git clone https://github.com/jeffcrouse/ofxHTTP.git "$ADDONS_DIR/$addon"
                ;;
            "ofxNetworkUtils")
                git clone https://github.com/jeffcrouse/ofxNetworkUtils.git "$ADDONS_DIR/$addon"
                ;;
        esac
        
        echo "✅ $addon instalado"
    fi
done

# Compilar la aplicación
echo "🔨 Compilando aplicación..."
make clean
make

if [ $? -eq 0 ]; then
    echo "✅ Compilación exitosa"
    
    # Ejecutar la aplicación
    echo "🚀 Ejecutando aplicación..."
    make run
else
    echo "❌ Error en la compilación"
    exit 1
fi
