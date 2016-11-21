# Rutas
MOTOR_DIR := motor

# Ejecutable del juego.
EXE := airforcepilot
EXEWIN := airforcepilotwin.exe

# Ficheros fuente del juego (modificar para añadir) .
SRC := main.cpp

# Ficheros fuente del motor.
SRC_MOTOR := imagen.cpp sonido.cpp musica.cpp control_animacion.cpp fuente.cpp texto.cpp galeria.cpp \
		parser.cpp dmanager.cpp nivel.cpp Teclado.cpp participante.cpp protagonista.cpp escena.cpp \
		juego.cpp universo.cpp bala.cpp enemigo.cpp harrier.cpp aguila.cpp opcion.cpp menu.cpp \
		cronometro.cpp transicion.cpp
		
		
# motor_dir + fuentes
SRC_DIR_MOTOR := $(foreach src, $(SRC_MOTOR),$(MOTOR_DIR)/$(src) )

# Objetos
OBJS := $(SRC:%.cpp=%.o)
OBJS_MOTOR := $(SRC_DIR_MOTOR:%.cpp=%.o)

# Compilador y las opciones 
CXX = c++ 
CXXFLAGS = -pedantic -Wall -pipe -ggdb -D"TIXML_USE_TICPP" -I$(MOTOR_DIR)
LDFLAGS = -L$(MOTOR_DIR)/ticpp -lticpp -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -ggdb
LDWINFLAGS = -L$(MOTOR_DIR)/ticpp -lticppwin -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf

# Config para make
all: $(EXE)
win32: $(EXEWIN)

# Obtención del ejecutable 
$(EXE): $(OBJS) $(OBJS_MOTOR)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(EXEWIN): $(OBJS) $(OBJS_MOTOR)
	$(CXX) -o $@ $^ $(LDWINFLAGS)


# Limpieza
clean: 
	 $(RM) $(EXE) $(OBJS) $(OBJS_MOTOR) *~ -rf

clean-win32:
	del $(EXEWIN) *.o .\motor\*.o *~

