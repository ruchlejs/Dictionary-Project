# Ce makefile est destine a compiler et créer les programmes executables organisés en repertoires src, tests, include, obj, bin
#	tests : contient tous les programmes, de tests ou autre. Chaque fichier contient un main
#	src : contient tous les fichiers sources C des modules, comme list.c, graph.c, edges.c, etc...
#	include : contient tous les fichiers d'entete .h, en particulier tous ceux des modules comme list.h, graph.h, edges.h, ...
# 	obj : ne pas oublier de créer ce repertoire, qui contiendra tous les fichiers objet issus de la compilation
# 	bin : ne pas oublier de créer ce repertoire, qui contiendra tous les programmes executables issus de la compilation/edition des liens

# Flag de compilation avec le debug possible
CFLAGS=-c -g -Wall -Iinclude
# Flag pour l'edition des liens, juste la bibliotheque math a ajouter
LDFLAGS= -lm

# Le compilateur
CC=gcc

# Le repertoire des modules sources (pas de main)
SRC_DIR=src
# Les programmes de test et finaux (avec un main pour chaque fichier)
EXE_DIR=tests
# Le repertoire contenant les fichiers objets
OBJ_DIR=obj
# Le repertoire contenant les fichiers executables
BIN_DIR=bin
# Le repertoire contenant les fichiers d'entete
INCLUDE_DIR=include/


# SRC_FILES : Fichiers contenant tous les modules sources .c, ne contenant aucun main
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
#SRC_FILES := $(filter-out $(EXE_FILES), $(SRC_FILES))

# OBJ_FILES : Fichiers contenant tous les fichiers objets .o, mais uniquement des modules ne contenant aucun main
O1=$(patsubst %.c, %.o, $(SRC_FILES))
OBJ_FILES=$(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(O1))

# B1 : Fichiers contenant des main qui sont dans le repertoire tests
B1= $(wildcard $(EXE_DIR)/*.c)

# EXE_FILES : Les fichiers programmes executables
EXE_FILES=$(patsubst $(EXE_DIR)/%.c, $(BIN_DIR)/%, $(B1))

#all : $(BIN_DIR)/test_double_queue

#$(BIN_DIR)/test_double_queue : $(OBJ_DIR)/double.o $(OBJ_DIR)/test_double_queue.o
#	$(CC) -o $@ $(OBJ_DIR)/double.o $(OBJ_DIR)/test_double_queue.o

#$(OBJ_DIR)/test_double_queue.o : $(EXE_DIR)/test_double_queue.c
#	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(EXE_DIR)/test_double_queue.c -o $@

#$(OBJ_DIR)/double.o : $(SRC_DIR)/Pile_File/double.c
#	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(SRC_DIR)/Pile_File/double.c -o $@

#test_double_queue : $(OBJ_DIR)/double.o $(OBJ_DIR)/test_double_queue.o
#	$(CC) -o $(BIN_DIR)/test_double_queue $(OBJ_DIR)/double.o $(OBJ_DIR)/test_double_queue.o

#$(OBJ_DIR)/test_double_queue.o : $(EXE_DIR)/test_double_queue.c
#	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(EXE_DIR)/test_double_queue.c -o $(OBJ_DIR)/test_double_queue.o

#$(OBJ_DIR)/double.o : $(SRC_DIR)/Pile_File/double.c
#	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(SRC_DIR)/Pile_File/double.c -o $(OBJ_DIR)/double.o



all : $(EXE_FILES)

#règle de compilation de touts les programmes
$(BIN_DIR)/% :  $(OBJ_FILES) $(OBJ_DIR)/%.o
	gcc  $^ -o $@ $(LDFLAGS)

# Regle pour construire les fichiers objets .o a partir des .c pour les modules sans main
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	gcc $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $(OBJ_DIR)/$*.o

# Regle pour construire les fichiers objets .o a partir des .c pour les programmes avec main
$(OBJ_DIR)/%.o : $(EXE_DIR)/%.c
	gcc $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $@


clean :
	rm -rf $(OBJ_DIR)/*.o $(OBJ_FILES) $(EXE_FILES) $(INCLUDE_DIR)/*.gch $(BIN_DIR)/*.dSYM
