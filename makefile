# Variables
LIBS = -lglut -lGLU -lGL -lm

NOME_ARQUIVO = main

# Main targets
$(NOME_ARQUIVO): $(NOME_ARQUIVO).o
	gcc -o $(NOME_ARQUIVO) $(NOME_ARQUIVO).o $(LIBS)
	./$(NOME_ARQUIVO)
	rm $(NOME_ARQUIVO)

# Source targets
$(NOME_ARQUIVO).o: $(NOME_ARQUIVO).c
	gcc -c $(NOME_ARQUIVO).c $(CFLAGS)

