CXX=g++
CXXFLAGS=-W -Wall -D UNIX_COLORS
LDFLAGS=
EXEC=othello

all: $(EXEC)

othello: Game.o History.o Ia.o Referee.o Options.o
	$(CXX) -o othello Game.o History.o Ia.o Referee.o Options.o main.cpp $(CXXFLAGS) $(LDFLAGS)

Game.o: Game.cpp
	$(CXX) -o Game.o -c Game.cpp $(CXXFLAGS) $(LDFLAGS)

History.o: History.cpp
	$(CXX) -o History.o -c History.cpp $(CXXFLAGS) $(LDFLAGS)

Ia.o: Ia.cpp
	$(CXX) -o Ia.o -c Ia.cpp $(CXXFLAGS) $(LDFLAGS)

Referee.o: Referee.cpp
	$(CXX) -o Referee.o -c Referee.cpp $(CXXFLAGS) $(LDFLAGS)

Options.o: Options.cpp
	$(CXX) -o Options.o -c Options.cpp $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
