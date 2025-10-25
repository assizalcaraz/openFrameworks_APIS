#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void mousePressed(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		
		// Funciones personalizadas para la API
		void loadPokemon(int pokemonId);
		void loadPokemonList();
		void drawPokemonInfo();
		void drawPokemonList();
		void drawUI();
		void drawLoadingScreen();
		
		// Callbacks de GUI
		void onNextPokemon();
		void onPrevPokemon();
		void onRandomPokemon();
		void onLoadList();
		void onPokemonIdChanged(int &pokemonId);
		
		// Función helper para dibujar texto
		void drawText(const string& text, float x, float y, ofTrueTypeFont& font, ofColor color);
		
	private:
		// Variables de la API
		ofxJSON pokemonData;
		ofxJSON pokemonListData;
		bool isLoading;
		bool hasPokemonData;
		bool hasListData;
		bool showList;  // Controla si la lista está visible
		string loadingMessage;
		string errorMessage;
		
		// Variables de UI
		int currentPokemonId;
		int scrollOffset;
		
		// Variables de dibujo
		ofTrueTypeFont titleFont;
		ofTrueTypeFont bodyFont;
		ofTrueTypeFont smallFont;
		
		// Colores
		ofColor backgroundColor;
		ofColor textColor;
		ofColor accentColor;
		
		// GUI
		ofxPanel gui;
		ofxButton nextPokemonBtn;
		ofxButton prevPokemonBtn;
		ofxButton randomPokemonBtn;
		ofxButton loadListBtn;
		ofxIntSlider pokemonIdSlider;
		ofxLabel statusLabel;
};
