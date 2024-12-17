## Simon Sepiol-Duchemin Joshua Setia

CC = gcc
CFLAGS = -O3

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=obj/%.o)

TARGET = main

# Règle principale pour générer le programme
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Règle pour compiler les fichiers source en objets
obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour créer le dossier obj s'il n'existe pas
obj:
	mkdir -p obj

# Nettoyer les fichiers générés
clean:
	rm -rf obj/ $(TARGET)

.PHONY: clean
