# Nutno nainstalovat GTK v3 (https://www.gtk.org/)
FILENAME := covidSimulator

all: simulator.cpp
	g++ -std=c++17 -O3 shared.cpp random_gen.cpp app_window.cpp simulator.cpp parameters.cpp statistics.cpp person.cpp -o $(FILENAME) `pkg-config --cflags --libs gtk+-3.0`

run:
	./$(FILENAME) $(ARGS)

clean:
	rm -f covidSimulator
