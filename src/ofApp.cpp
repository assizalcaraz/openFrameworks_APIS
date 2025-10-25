#include "ofApp.h"
#include <algorithm>

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Pokemon API - openFrameworks");
    ofSetFrameRate(60);
    
    // Inicializar variables
    isLoading = false;
    hasPokemonData = false;
    hasListData = false;
    showList = false;  // Nueva variable para controlar visibilidad
    currentPokemonId = 1;
    scrollOffset = 0;
    loadingMessage = "Cargando...";
    errorMessage = "";
    
    // Cargar fuentes TTF desde la carpeta data
    bool fontLoaded = titleFont.load("Vera.ttf", 24);
    if (!fontLoaded) {
        ofLogWarning() << "No se pudo cargar Vera.ttf, usando fuentes por defecto";
    }
    
    bodyFont.load("Vera.ttf", 14);
    smallFont.load("Vera.ttf", 10);
    
    // Configurar colores mejorados
    backgroundColor = ofColor(30, 30, 30);
    textColor = ofColor(220, 220, 220);  // Un blanco más suave
    accentColor = ofColor(255, 204, 0);  // Amarillo dorado
    
    // Configurar GUI
    gui.setup("PokéAPI Explorer");
    gui.add(nextPokemonBtn.setup("Siguiente Pokémon"));
    gui.add(prevPokemonBtn.setup("Anterior Pokémon"));
    gui.add(randomPokemonBtn.setup("Pokémon Aleatorio"));
    gui.add(loadListBtn.setup("Mostrar/Ocultar Lista"));
    gui.add(pokemonIdSlider.setup("ID Pokémon", 1, 1, 151));
    gui.add(statusLabel.setup("Estado", "Listo"));
    
    // Configurar callbacks de botones
    nextPokemonBtn.addListener(this, &ofApp::onNextPokemon);
    prevPokemonBtn.addListener(this, &ofApp::onPrevPokemon);
    randomPokemonBtn.addListener(this, &ofApp::onRandomPokemon);
    loadListBtn.addListener(this, &ofApp::onLoadList);
    pokemonIdSlider.addListener(this, &ofApp::onPokemonIdChanged);
    
    // Cargar primer Pokémon automáticamente
    loadPokemon(1);
}

//--------------------------------------------------------------
// Función helper para dibujar texto con fallback
void ofApp::drawText(const string& text, float x, float y, ofTrueTypeFont& font, ofColor color) {
    ofSetColor(color);
    if (font.isLoaded()) {
        font.drawString(text, x, y);
    } else {
        ofDrawBitmapString(text, x, y);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    // La GUI se actualiza automáticamente
    // No necesitamos lógica de hover manual
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(backgroundColor);
    
    if (isLoading) {
        drawLoadingScreen();
    } else {
        drawUI();
        
        if (hasPokemonData) {
            drawPokemonInfo();
        }
        
        if (hasListData) {
            drawPokemonList();
        }
    }
}

//--------------------------------------------------------------
void ofApp::exit(){
    // Limpiar recursos si es necesario
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case ' ':
            // Espacio para cargar Pokémon aleatorio
            loadPokemon(ofRandom(1, 1010));
            break;
        case 'l':
        case 'L':
            // L para mostrar/ocultar lista
            if (hasListData) {
                showList = !showList;
            } else {
                loadPokemonList();
                showList = true;
            }
            break;
        case 'n':
        case 'N':
            // N para siguiente Pokémon
            if (hasPokemonData) {
                loadPokemon(currentPokemonId + 1);
            }
            break;
        case 'p':
        case 'P':
            // P para Pokémon anterior
            if (hasPokemonData && currentPokemonId > 1) {
                loadPokemon(currentPokemonId - 1);
            }
            break;
        case 'r':
        case 'R':
            // R para recargar
            if (hasPokemonData) {
                loadPokemon(currentPokemonId);
            }
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // ofxGui maneja los clics automáticamente
    // Los callbacks se ejecutan cuando se presionan los botones
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){
    if (hasListData && showList) {
        scrollOffset += scrollY * 30;  // Aumentar sensibilidad del scroll
        int itemsToShow = 15;
        int maxScroll = max(0, (int)pokemonListData["results"].size() - itemsToShow) * 25;
        scrollOffset = ofClamp(scrollOffset, 0, maxScroll);
    }
}

//--------------------------------------------------------------
void ofApp::loadPokemon(int pokemonId) {
    isLoading = true;
    loadingMessage = "Cargando Pokemon #" + ofToString(pokemonId) + "...";
    errorMessage = "";
    
    // Simular carga asíncrona (en una aplicación real usarías hilos)
    ofxJSON response;
    string url = "https://pokeapi.co/api/v2/pokemon/" + ofToString(pokemonId);
    
    if (response.open(url)) {
        pokemonData = response;
        hasPokemonData = true;
        currentPokemonId = pokemonId;
        errorMessage = "";
    } else {
        errorMessage = "Error al cargar Pokemon #" + ofToString(pokemonId);
        hasPokemonData = false;
    }
    
    isLoading = false;
}

//--------------------------------------------------------------
void ofApp::loadPokemonList() {
    isLoading = true;
    loadingMessage = "Cargando lista de Pokemon...";
    errorMessage = "";
    
    ofxJSON response;
    string url = "https://pokeapi.co/api/v2/pokemon?limit=151&offset=0";
    
    if (response.open(url)) {
        pokemonListData = response;
        hasListData = true;
        errorMessage = "";
    } else {
        errorMessage = "Error al cargar lista de Pokemon";
        hasListData = false;
    }
    
    isLoading = false;
}

//--------------------------------------------------------------
void ofApp::drawPokemonInfo() {
    if (!hasPokemonData) return;

    // Ajustar posición basada en si la lista está visible
    float infoX = (hasListData && showList) ? 50 : 380;
    float infoY = 80;

    // --- Nombre y ID ---
    string pokemonName = pokemonData["name"].asString();
    // Capitalizar la primera letra
    if (!pokemonName.empty()) {
        pokemonName[0] = toupper(pokemonName[0]);
    }
    drawText(pokemonName, infoX, infoY, titleFont, accentColor);
    
    drawText("ID: " + pokemonData["id"].asString(), infoX, infoY + 30, bodyFont, ofColor(180));
    
    infoY += 80;

    // --- Atributos Físicos ---
    drawText("Altura: " + ofToString(pokemonData["height"].asFloat() / 10.0f) + " m", infoX, infoY, bodyFont, textColor);
    drawText("Peso: " + ofToString(pokemonData["weight"].asFloat() / 10.0f) + " kg", infoX + 180, infoY, bodyFont, textColor);
    
    infoY += 50;

    // --- Tipos y Habilidades ---
    string types_str = "Tipo(s): ";
    for (int i = 0; i < pokemonData["types"].size(); i++) {
        types_str += pokemonData["types"][i]["type"]["name"].asString() + (i == pokemonData["types"].size() - 1 ? "" : ", ");
    }
    drawText(types_str, infoX, infoY, bodyFont, textColor);
    
    infoY += 30;
    string abilities_str = "Habilidades: ";
    for (int i = 0; i < pokemonData["abilities"].size(); i++) {
        abilities_str += pokemonData["abilities"][i]["ability"]["name"].asString() + (i == pokemonData["abilities"].size() - 1 ? "" : ", ");
    }
    drawText(abilities_str, infoX, infoY, bodyFont, textColor);
    
    infoY += 70;

    // --- Estadísticas ---
    drawText("Estadísticas Base:", infoX, infoY, bodyFont, textColor);
    infoY += 30;

    for (int i = 0; i < pokemonData["stats"].size(); i++) {
        string statName = pokemonData["stats"][i]["stat"]["name"].asString();
        int baseStat = pokemonData["stats"][i]["base_stat"].asInt();
        
        // Etiqueta de la estadística
        drawText(statName, infoX, infoY, smallFont, ofColor(200));
        
        // Fondo de la barra
        ofSetColor(50);
        ofDrawRectRounded(infoX + 120, infoY - 12, 255, 14, 7);

        // Barra de estadística (con un máximo de 255)
        float barWidth = ofMap(baseStat, 0, 255, 0, 255, true);
        ofSetColor(accentColor);
        ofDrawRectRounded(infoX + 120, infoY - 12, barWidth, 14, 7);
        
        // Valor numérico
        drawText(ofToString(baseStat), infoX + 125 + 255 + 10, infoY, smallFont, textColor);
        
        infoY += 25;
    }
}

//--------------------------------------------------------------
void ofApp::drawPokemonList() {
    if (!hasListData || !showList) return;
    
    // Posición fija en el lado derecho
    float listX = ofGetWidth() - 300;
    float listY = 80;
    
    // Fondo para la lista
    ofSetColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 200);
    ofDrawRectRounded(listX - 10, listY - 10, 290, 400, 8);
    
    // Borde
    ofSetColor(accentColor);
    ofNoFill();
    ofDrawRectRounded(listX - 10, listY - 10, 290, 400, 8);
    ofFill();
    
    drawText("Lista de Pokémon", listX, listY, bodyFont, accentColor);
    
    listY += 40;
    
    // Calcular rango de items a mostrar
    int itemsToShow = 15; // Reducir para evitar superposición
    int startIndex = floor(scrollOffset / 25.0f);
    startIndex = ofClamp(startIndex, 0, pokemonListData["results"].size() - itemsToShow);

    for (int i = 0; i < itemsToShow; ++i) {
        int currentIndex = startIndex + i;
        if (currentIndex >= pokemonListData["results"].size()) break;

        string pokemonName = pokemonListData["results"][currentIndex]["name"].asString();
        
        // Capitalizar nombre
        if (!pokemonName.empty()) {
            pokemonName[0] = toupper(pokemonName[0]);
        }
        
        // Resaltar si es el Pokémon actual
        ofColor textColorToUse = (currentIndex + 1 == currentPokemonId) ? accentColor : textColor;
        
        drawText(ofToString(currentIndex + 1) + ". " + pokemonName, listX, listY, smallFont, textColorToUse);
        listY += 20;
    }
    
    // Indicador de scroll
    if (pokemonListData["results"].size() > itemsToShow) {
        drawText("↑↓ Scroll", listX, listY + 10, smallFont, ofColor(150));
    }
}

//--------------------------------------------------------------
void ofApp::drawUI() {
    // Ajustar posición del GUI si la lista está visible
    if (hasListData && showList) {
        gui.setPosition(10, 10);  // Mover GUI a la esquina superior izquierda
    } else {
        gui.setPosition(10, 10);  // Posición normal
    }
    
    // Dibujar la GUI
    gui.draw();
    
    // Actualizar estado del slider
    pokemonIdSlider = currentPokemonId;
    
    // Actualizar estado
    if (isLoading) {
        statusLabel = loadingMessage;
    } else if (!errorMessage.empty()) {
        statusLabel = "Error: " + errorMessage;
    } else if (hasPokemonData) {
        statusLabel = "Pokémon cargado: " + pokemonData["name"].asString();
    } else {
        statusLabel = "Listo";
    }
    
    // Mostrar instrucciones
    if (hasListData) {
        drawText("Presiona 'L' para mostrar/ocultar lista", 10, ofGetHeight() - 30, smallFont, ofColor(150));
    }
}

//--------------------------------------------------------------
void ofApp::drawLoadingScreen() {
    // Fondo semitransparente para dar contexto
    ofSetColor(0, 0, 0, 150);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    // Mensaje de carga centrado
    float textWidth = bodyFont.isLoaded() ? bodyFont.stringWidth(loadingMessage) : loadingMessage.length() * 8;
    drawText(loadingMessage, 
             ofGetWidth()/2 - textWidth/2, 
             ofGetHeight()/2, 
             bodyFont, 
             textColor);
    
    // Spinner mejorado
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2 + 50);
    ofRotateDeg(ofGetElapsedTimef() * 100); // Rotación continua
    
    ofSetColor(accentColor);
    ofSetRectMode(OF_RECTMODE_CENTER);
    for (int i = 0; i < 8; ++i) {
        ofDrawCircle(30, 0, 5 - i * 0.5); // Círculos que se desvanecen
        ofRotateDeg(360.0 / 8.0);
    }
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofPopMatrix();
}

//--------------------------------------------------------------
// Callbacks de GUI
void ofApp::onNextPokemon() {
    if (currentPokemonId < 151) {
        loadPokemon(currentPokemonId + 1);
    }
}

void ofApp::onPrevPokemon() {
    if (currentPokemonId > 1) {
        loadPokemon(currentPokemonId - 1);
    }
}

void ofApp::onRandomPokemon() {
    int randomId = ofRandom(1, 152); // 1-151
    loadPokemon(randomId);
}

void ofApp::onLoadList() {
    if (hasListData) {
        showList = !showList;
    } else {
        loadPokemonList();
        showList = true;
    }
}

void ofApp::onPokemonIdChanged(int &pokemonId) {
    if (pokemonId != currentPokemonId) {
        loadPokemon(pokemonId);
    }
}
