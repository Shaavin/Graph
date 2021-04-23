a.out:
	g++ -std=c++11 myGraph_i127p615.hpp
	g++ -std=c++11 main.cpp
	# ./a.out instances/instance1.txt > output.txt
	# /usr/bin/time -v -o analysis.log ./a.out instances/instance1.txt > output.txt

clean:
	rm *.gch output.txt analysis.log a.out
