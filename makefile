INCPATH = ./Donnees
LIBPATH = $(INCPATH)
EXE = Carrefour
INT = Mere.h Clavier.h Voie.h Feux.h
REAL = $(INT:.h=.cpp)
OBJ = $(INT:.h=.o)
LIBS = -ltp -lncurses -ltcl
ECHO = @echo

$(EXE) : Mere.o Clavier.o Voie.o Feux.o
	$(ECHO) "EDL de <$(EXE)>"
	g++ -o $(EXE) $(OBJ) -L $(LIBPATH) $(LIBS)
%.o : %.cpp
	$(ECHO) "Compil de <$<>"
	g++ -c -DMAP $< -I$(INCPATH)
