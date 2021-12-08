all: simulator.cpp
	g++ -Wall -Wextra simulator.cpp parameters.cpp person.cpp -o covidSimulator

clean:
	rm -f covidSimulator