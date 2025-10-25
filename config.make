# Configuración del proyecto Pokemon API
# Este archivo se incluye automáticamente en el Makefile

# Ruta a openFrameworks (ajusta según tu instalación)
OF_ROOT = /Users/joseassizalcarazbaxter/Documents/UNA/POSGRADO/2025_1/PyA/of_v0.12.1_osx_release

# Nombre de la aplicación
APP_NAME = PokemonAPI

# Directorio de compilación
BUILD_DIR = bin

# Directorio de addons
ADDONS_DIR = addons

# Addons necesarios para el proyecto
REQUIRED_ADDONS = ofxJSON ofxHTTP ofxNetworkUtils ofxHTTPForm

# Configuración de compilación
DEBUG_FLAGS = -g -O0 -DDEBUG
RELEASE_FLAGS = -O3 -DNDEBUG

# Configuración de la API
API_BASE_URL = https://pokeapi.co/api/v2
API_TIMEOUT = 30

# Configuración de logging
LOG_LEVEL = INFO
LOG_FILE = logs/pokemon_api.log
