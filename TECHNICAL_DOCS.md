# Documentación Técnica - Pokemon API openFrameworks

## 🏗️ Arquitectura de la Aplicación

### Estructura del Proyecto
```
of_apis_project2/
├── src/
│   ├── main.cpp          # Punto de entrada
│   ├── ofApp.h           # Declaración de la clase principal
│   └── ofApp.cpp         # Implementación de la clase principal
├── addons.make           # Configuración de addons
├── config.make           # Configuración del proyecto
├── project_config.make   # Configuración específica
├── build_and_run.sh      # Script de compilación
└── README.md             # Documentación del usuario
```

### Clase Principal: ofApp

La clase `ofApp` hereda de `ofBaseApp` y maneja toda la lógica de la aplicación.

#### Variables Principales
- **API Data**: `pokemonData`, `pokemonListData` (ofxJSON)
- **UI State**: `isLoading`, `hasPokemonData`, `hasListData`
- **Navigation**: `currentPokemonId`, `selectedPokemonIndex`, `scrollOffset`
- **Visual**: `titleFont`, `bodyFont`, `smallFont`, colores
- **Buttons**: Rectángulos para botones interactivos

#### Métodos Principales
- `loadPokemon(int id)`: Carga un Pokémon específico
- `loadPokemonList()`: Carga lista de Pokémon
- `drawPokemonInfo()`: Renderiza información del Pokémon
- `drawPokemonList()`: Renderiza lista de Pokémon
- `drawUI()`: Renderiza interfaz de usuario

## 🔌 Integración con APIs

### PokeAPI Integration
- **Base URL**: `https://pokeapi.co/api/v2/`
- **Endpoints**:
  - `/pokemon/{id}`: Información de Pokémon específico
  - `/pokemon?limit=50&offset={offset}`: Lista de Pokémon
- **Método**: HTTP GET usando ofxJSON
- **Formato**: JSON response

### Manejo de Datos
```cpp
// Cargar Pokémon
ofxJSON response;
string url = "https://pokeapi.co/api/v2/pokemon/" + ofToString(pokemonId);
if (response.open(url)) {
    pokemonData = response;
    hasPokemonData = true;
}
```

## 🎨 Sistema de Renderizado

### Pipeline de Dibujo
1. **Background**: Color de fondo
2. **UI Elements**: Botones y controles
3. **Data Display**: Información del Pokémon
4. **List Display**: Lista de Pokémon
5. **Error Messages**: Mensajes de error

### Fuentes y Tipografía
- **Title Font**: 24px para títulos
- **Body Font**: 16px para texto principal
- **Small Font**: 12px para controles

### Sistema de Colores
```cpp
backgroundColor = ofColor(30, 30, 30);      // Gris oscuro
textColor = ofColor(255, 255, 255);         // Blanco
accentColor = ofColor(255, 193, 7);         // Amarillo
buttonColor = ofColor(76, 175, 80);         // Verde
buttonHoverColor = ofColor(69, 160, 73);    // Verde oscuro
```

## 🎮 Sistema de Interacción

### Controles de Teclado
- **ESPACIO**: Pokémon aleatorio
- **L**: Cargar lista
- **N**: Siguiente Pokémon
- **P**: Pokémon anterior
- **R**: Recargar actual

### Controles de Mouse
- **Click**: Activar botones
- **Hover**: Efectos visuales
- **Scroll**: Navegar lista

### Sistema de Botones
```cpp
// Detección de hover
ofPoint mouse(ofGetMouseX(), ofGetMouseY());
bool isHover = button.inside(mouse);

// Renderizado con estado
ofSetColor(isHover ? buttonHoverColor : buttonColor);
ofDrawRectangle(button);
```

## 📊 Manejo de Estado

### Estados de la Aplicación
- **Loading**: Cargando datos de API
- **Pokemon View**: Mostrando información de Pokémon
- **List View**: Mostrando lista de Pokémon
- **Error**: Mostrando mensaje de error

### Variables de Estado
```cpp
bool isLoading;           // Estado de carga
bool hasPokemonData;      // Datos de Pokémon disponibles
bool hasListData;         // Datos de lista disponibles
string errorMessage;      // Mensaje de error
```

## 🔧 Configuración y Compilación

### Addons Requeridos
- **ofxJSON**: Manejo de datos JSON
- **ofxHTTP**: Peticiones HTTP
- **ofxNetworkUtils**: Utilidades de red

### Configuración de Compilación
```makefile
PROJECT_CFLAGS = -std=c++17 -Wall -Wextra
PROJECT_LDFLAGS = 
```

### Script de Build
El script `build_and_run.sh` automatiza:
1. Verificación de dependencias
2. Instalación de addons
3. Compilación del proyecto
4. Ejecución de la aplicación

## 🐛 Debugging y Logging

### Sistema de Logging
```cpp
// Mensajes de estado
loadingMessage = "Cargando Pokemon #" + ofToString(pokemonId) + "...";

// Mensajes de error
errorMessage = "Error al cargar Pokemon #" + ofToString(pokemonId);
```

### Debug Visual
- Indicadores de estado en pantalla
- Mensajes de error visibles
- Controles de debug en pantalla

## 🚀 Optimizaciones

### Rendimiento
- **FPS**: 60 FPS target
- **Lazy Loading**: Carga datos solo cuando es necesario
- **Efficient Rendering**: Solo redibuja cuando es necesario

### Memoria
- **JSON Parsing**: Uso eficiente de ofxJSON
- **Font Loading**: Carga de fuentes una sola vez
- **Resource Management**: Limpieza apropiada de recursos

## 🔮 Extensiones Futuras

### Características Planificadas
- **Async Loading**: Carga asíncrona de datos
- **Image Support**: Imágenes de Pokémon
- **Search Functionality**: Búsqueda por nombre
- **Filtering**: Filtros por tipo
- **Animations**: Animaciones de transición
- **Sound Effects**: Efectos de sonido

### Mejoras Técnicas
- **Threading**: Carga en hilos separados
- **Caching**: Cache de datos de API
- **Error Recovery**: Recuperación automática de errores
- **Performance Monitoring**: Monitoreo de rendimiento

## 📚 Referencias Técnicas

### openFrameworks
- [Documentación oficial](https://openframeworks.cc/documentation/)
- [ofxJSON](https://github.com/jeffcrouse/ofxJSON)
- [ofxHTTP](https://github.com/jeffcrouse/ofxHTTP)

### APIs
- [PokeAPI Documentation](https://pokeapi.co/docs/v2)
- [JSON API Standards](https://jsonapi.org/)

### C++ y openFrameworks
- [C++17 Reference](https://en.cppreference.com/w/cpp/17)
- [openFrameworks Examples](https://github.com/openframeworks/openFrameworks/tree/master/examples)

---

**Desarrollado con ❤️ usando openFrameworks**
