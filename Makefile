# Nazwa aplikacji
PROG = Warcaby

# Nazwy katalogów
BDIR = bin
ODIR = obj
SDIR = src
IDIR = include

# Kompilator
CC = g++

# Opcje kompilatora
CFLAGS = -std=c++11

# Opcje linkera
LFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

# Pliki z roszerzeniem .cpp
SRC = $(wildcard **/*.cpp)

# Obiekty z roszerzeniem .o
OBJS = $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(SRC))

all: $(OBJS)
	@mkdir -p $(BDIR)
	$(CC) $(CFLAGS) -I$(IDIR) -o $(BDIR)/$(PROG) $^ $(LFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	@mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -MMD -c -o $@ $<

clean:
	rm -rf $(ODIR) $(BDIR)
