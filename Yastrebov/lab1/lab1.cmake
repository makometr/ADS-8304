all: Source/Analyzer.o Source/BracketAnalyzer.o
	g++ -o lab1 Source/Analyzer.o Source/BracketAnalyzer.o
	pause

Analyzer.o: Source/Analyzer.cpp
	g++ -c Source/Analyzer.cpp
	
BracketAnalyzer.o: Source/BracketAnalyzer.cpp Source/BracketAnalyzer.h
	g++ -c Source/BracketAnalyzer.cpp

Clean: 
	