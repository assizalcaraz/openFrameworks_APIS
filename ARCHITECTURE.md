# Arquitectura de la Aplicación Pokemon API

## 🏗️ Diagrama de Arquitectura

```
┌─────────────────────────────────────────────────────────────┐
│                    Pokemon API App                          │
│                   (openFrameworks)                          │
└─────────────────────────────────────────────────────────────┘
                                │
                                ▼
┌─────────────────────────────────────────────────────────────┐
│                      ofApp Class                            │
│  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────┐ │
│  │   UI Manager    │  │  API Manager    │  │ Data Store  │ │
│  │                 │  │                 │  │             │ │
│  │ • drawUI()      │  │ • loadPokemon() │  │ • pokemonData│ │
│  │ • drawButtons() │  │ • loadList()    │  │ • listData  │ │
│  │ • handleInput() │  │ • handleHTTP()  │  │ • state     │ │
│  └─────────────────┘  └─────────────────┘  └─────────────┘ │
└─────────────────────────────────────────────────────────────┘
                                │
                                ▼
┌─────────────────────────────────────────────────────────────┐
│                    openFrameworks                           │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────────────┐ │
│  │   ofxJSON   │  │   ofxHTTP   │  │  ofxNetworkUtils   │ │
│  │             │  │             │  │                     │ │
│  │ • JSON Parse│  │ • HTTP GET  │  │ • Network Utils     │ │
│  │ • Data Access│  │ • Requests  │  │ • Connection Mgmt  │ │
│  └─────────────┘  └─────────────┘  └─────────────────────┘ │
└─────────────────────────────────────────────────────────────┘
                                │
                                ▼
┌─────────────────────────────────────────────────────────────┐
│                      PokeAPI                                │
│  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────┐ │
│  │ /pokemon/{id}   │  │ /pokemon?limit= │  │ /pokemon/   │ │
│  │                 │  │ 50&offset={n}   │  │             │ │
│  │ • Individual    │  │                 │  │ • List      │ │
│  │ • Complete Data │  │ • Paginated     │  │ • Metadata  │ │
│  └─────────────────┘  └─────────────────┘  └─────────────┘ │
└─────────────────────────────────────────────────────────────┘
```

## 🔄 Flujo de Datos

### 1. Inicialización
```
main() → ofApp::setup() → loadPokemon(1) → API Call → UI Update
```

### 2. Interacción del Usuario
```
User Input → ofApp::mousePressed() → loadPokemon() → API Call → UI Update
```

### 3. Renderizado
```
ofApp::draw() → drawUI() → drawPokemonInfo() → Screen Output
```

## 🎮 Sistema de Interacción

### Input Layer
```
┌─────────────┐    ┌─────────────┐    ┌─────────────┐
│   Keyboard  │    │    Mouse    │    │   Touch     │
│             │    │             │    │             │
│ • Space     │    │ • Click     │    │ • Tap       │
│ • L, N, P   │    │ • Hover     │    │ • Swipe     │
│ • R         │    │ • Scroll    │    │ • Pinch     │
└─────────────┘    └─────────────┘    └─────────────┘
        │                   │                   │
        └───────────────────┼───────────────────┘
                            │
                            ▼
                    ┌─────────────┐
                    │ Input Handler│
                    │             │
                    │ • keyPressed│
                    │ • mousePressed│
                    │ • mouseScrolled│
                    └─────────────┘
```

### UI Layer
```
┌─────────────┐    ┌─────────────┐    ┌─────────────┐
│   Buttons   │    │   Display   │    │  Navigation │
│             │    │             │    │             │
│ • Load      │    │ • Pokemon   │    │ • Next/Prev │
│ • List      │    │ • Stats     │    │ • Random    │
│ • Random    │    │ • Types     │    │ • Scroll    │
└─────────────┘    └─────────────┘    └─────────────┘
```

## 📊 Estructura de Datos

### Pokemon Data Structure
```json
{
  "id": 1,
  "name": "bulbasaur",
  "height": 7,
  "weight": 69,
  "types": [
    {
      "type": {
        "name": "grass"
      }
    }
  ],
  "abilities": [
    {
      "ability": {
        "name": "overgrow"
      }
    }
  ],
  "stats": [
    {
      "stat": {
        "name": "hp"
      },
      "base_stat": 45
    }
  ]
}
```

### List Data Structure
```json
{
  "count": 1328,
  "results": [
    {
      "name": "bulbasaur",
      "url": "https://pokeapi.co/api/v2/pokemon/1/"
    }
  ]
}
```

## 🔧 Configuración del Sistema

### Build Configuration
```makefile
# Compiler flags
PROJECT_CFLAGS = -std=c++17 -Wall -Wextra

# Required addons
ADDONS = ofxJSON ofxHTTP ofxNetworkUtils

# Window settings
WINDOW_WIDTH = 1024
WINDOW_HEIGHT = 768
```

### Runtime Configuration
```cpp
// API settings
string API_BASE_URL = "https://pokeapi.co/api/v2/";
int API_TIMEOUT = 30;

// UI settings
int FONT_SIZE_TITLE = 24;
int FONT_SIZE_BODY = 16;
int POKEMON_PER_PAGE = 10;
```

## 🚀 Flujo de Ejecución

### 1. Startup Sequence
```
1. main() called
2. ofCreateWindow() - Create window
3. ofRunApp() - Start app
4. ofApp::setup() - Initialize
5. Load fonts and colors
6. Setup UI elements
7. loadPokemon(1) - Load first Pokemon
8. Enter main loop
```

### 2. Main Loop
```
1. ofApp::update() - Update state
2. ofApp::draw() - Render frame
3. Handle input events
4. Repeat at 60 FPS
```

### 3. API Interaction
```
1. User triggers action
2. loadPokemon() or loadPokemonList()
3. Create HTTP request
4. Send to PokeAPI
5. Parse JSON response
6. Update UI state
7. Trigger redraw
```

## 🎯 Patrones de Diseño

### Observer Pattern
- UI observes data changes
- Automatic redraw on data update

### State Machine
- Loading state
- Pokemon view state
- List view state
- Error state

### MVC-like Structure
- Model: Pokemon data
- View: UI rendering
- Controller: Input handling

## 🔮 Extensiones Futuras

### Planned Features
- Image loading and display
- Search functionality
- Filtering by type
- Animations and transitions
- Sound effects
- Configuration panel

### Technical Improvements
- Async loading with threads
- Data caching
- Error recovery
- Performance monitoring
- Unit testing

---

**Arquitectura diseñada para ser modular, extensible y mantenible**
