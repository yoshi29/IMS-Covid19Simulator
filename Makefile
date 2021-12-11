# Nutno nainstalovat GTK v3 (https://www.gtk.org/)
all: simulator.cpp
	g++ -Wall -Wextra -O3 shared.cpp random_gen.cpp app_window.cpp simulator.cpp parameters.cpp statistics.cpp person.cpp -o covidSimulator `pkg-config --cflags --libs gtk+-3.0`

clean:
	rm -f covidSimulator