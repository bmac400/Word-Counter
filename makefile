SRC = charBST.c inputHandling.c hashTable.c
OBJ = charBST.o inputHandling.o hashTable.o
PROG = wordfreak

$(PROG) : $(OBJ)
	gcc $(OBJ) -o $(PROG)

$(OBJ): $(SRC)
