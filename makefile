INCPATH = /media/alvaro/OS/share/public/tp/tp-multitache
LIBPATH = $(INCPATH)
EXE = Carrefour
INT = Mere.h Clavier.h
REAL = $(INT:.h=.cpp)
OBJ = $(INT:.h=.o)
LIBS = -ltp -lncurses -ltcl
ECHO = @echo

$(EXE) : Mere.o Clavier.o
	$(ECHO) "EDL de <$(EXE)>"
	g++ -o $(EXE) $(OBJ) -L $(LIBPATH) $(LIBS)
		
%.o : %.cpp
	$(ECHO) "Compil de <$<>"
	g++ -c -DMAP $< -I$(INCPATH)
