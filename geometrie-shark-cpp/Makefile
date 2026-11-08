# Répertoires
SRC_DIR = src
TXT_DIR = txt
SDL_DIR = SDL
OBJ_DIR = obj
BIN_DIR = bin
DOC_DIR = doc
DOXYFILE = $(DOC_DIR)/doxyfile
DOXYGEN_HTML_DIR = $(DOC_DIR)/html

# Création automatique des répertoires si inexistants
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR) $(DOC_DIR))

.PHONY: all clean clean_docs doc

# Options de compilation
CXX = g++
CXXFLAGS = -ggdb -std=c++11 -Wall -I $(SRC_DIR) -I $(TXT_DIR) -I $(SDL_DIR)
SDL_FLAGS = `sdl2-config --cflags`
SDL_LIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# Fichiers objets communs
OBJ_COMMON = \
  $(OBJ_DIR)/Partie.o \
  $(OBJ_DIR)/Joueur.o \
  $(OBJ_DIR)/surface.o \
  $(OBJ_DIR)/Obstacle.o \
  $(OBJ_DIR)/Portail.o \
  $(OBJ_DIR)/SautAuto.o \
  $(OBJ_DIR)/SautClick.o

# Cibles principales
all: $(BIN_DIR)/game_sdl $(BIN_DIR)/game_txt

# Exécutable version SDL
$(BIN_DIR)/game_sdl: $(OBJ_DIR)/main_sdl.o $(OBJ_DIR)/sdlJeu.o $(OBJ_DIR)/sdlMenu.o $(OBJ_COMMON)
	$(CXX) -o $@ $^ $(SDL_LIBS)

# Exécutable version console (texte)
$(BIN_DIR)/game_txt: $(OBJ_DIR)/main_txt.o $(OBJ_DIR)/txtJeu.o $(OBJ_DIR)/winTxt.o $(OBJ_COMMON)
	$(CXX) -o $@ $^

# Compilation fichiers SDL
$(OBJ_DIR)/main_sdl.o: $(SDL_DIR)/main_sdl.cpp
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) -c $< -o $@ -MMD -MP

$(OBJ_DIR)/sdlJeu.o: $(SDL_DIR)/sdlJeu.cpp
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) -c $< -o $@ -MMD -MP

$(OBJ_DIR)/sdlMenu.o: $(SDL_DIR)/sdlMenu.cpp
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) -c $< -o $@ -MMD -MP

# Compilation fichiers TXT
$(OBJ_DIR)/main_txt.o: $(TXT_DIR)/main_txt.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD -MP

$(OBJ_DIR)/txtJeu.o: $(TXT_DIR)/txtJeu.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD -MP

$(OBJ_DIR)/winTxt.o: $(TXT_DIR)/winTxt.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD -MP

# Compilation fichiers source communs
$(OBJ_DIR)/Partie.o: $(SRC_DIR)/Partie.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD -MP

$(OBJ_DIR)/Joueur.o: $(SRC_DIR)/Joueur.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD -MP

$(OBJ_DIR)/surface.o: $(SRC_DIR)/surface.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD -MP

$(OBJ_DIR)/Obstacle.o: $(SRC_DIR)/Obstacle.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD -MP

$(OBJ_DIR)/Portail.o: $(SRC_DIR)/Portail.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD -MP

$(OBJ_DIR)/SautAuto.o: $(SRC_DIR)/SautAuto.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD -MP

$(OBJ_DIR)/SautClick.o: $(SRC_DIR)/SautClick.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD -MP

# Documentation Doxygen
doc:
	@echo "Génération de la documentation Doxygen..."
	@doxygen $(DOXYFILE)

clean_docs:
	@echo "Nettoyage du dossier documentation..."
	rm -rf $(DOXYGEN_HTML_DIR)

# Nettoyage général
clean: clean_docs
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d $(BIN_DIR)/game_sdl $(BIN_DIR)/game_txt

# Inclusion des dépendances générées
-include $(OBJ_DIR)/*.d
