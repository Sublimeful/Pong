LIBS:=-lsfml-graphics -lsfml-window -lsfml-system
INC:=-Iinclude
SRC:=src/Board.cpp src/Ball.cpp
run:
	g++ ${INC} ${SRC} game.cpp ${LIBS}
	pwsh -c start pwsh -FilePath "./a.exe"

