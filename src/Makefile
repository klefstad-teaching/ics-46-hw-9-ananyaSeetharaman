CXXFLAGS=-ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

dijkstras_main: dijkstras_main.cpp dijkstras.cpp
	g++ $(CXXFLAGS) dijkstras_main.cpp dijkstras.cpp -o dijkstras_main

ladder_main: ladder_main.cpp ladder.cpp
	g++ $(CXXFLAGS) ladder_main.cpp ladder.cpp -o ladder_main

clean:
	/bin/rm dijkstras_main ladder_main