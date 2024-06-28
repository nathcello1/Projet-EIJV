CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRCDIR = src
BINDIR = bin

#Liste des fichiers source dans src
SRCS = $(filter-out $(SRCDIR)/main.cpp,$(wildcard $(SRCDIR)/*.cpp))

#Ajout de main.cpp à la liste des fichiers source
SRCS += $(SRCDIR)/main.cpp

#Liste des fichiers objets
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(SRCS))

#Nom de l'exécutable
EXECUTABLE = BlackJack

#Règle de construction de l'exécutable
$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

#Règle de construction des fichiers objets (sauf main.cpp)
$(BINDIR)/%.o: $(SRCDIR)/%.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#Règle de construction du fichier objet pour main.cpp
$(BINDIR)/main.o: $(SRCDIR)/main.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#Création du répertoire de sortie
$(BINDIR):
	mkdir -p $(BINDIR)

#Règle pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -rf $(BINDIR) $(EXECUTABLE)