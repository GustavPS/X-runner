all:
	\g++ -std=c++14 main.cc engine/*.cc level_parser/*.cc  objects/abstractish/*.cc objects/non_abstract/*.cc states/abstract/*.cc states/non_abstract/*.cc -lsfml-window -lsfml-graphics -lsfml-system -lpugixml -o "x_runner"
