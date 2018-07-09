.PHONY: all clean run opt

all:
	g++ -std=c++11 thread_contention.cpp -o with_contention -lpthread
	g++ -std=c++11 no_contention.cpp -o no_contention -lpthread

opt:
	g++ -std=c++11 thread_contention.cpp -o with_contention -lpthread -O5
	g++ -std=c++11 no_contention.cpp -o no_contention -lpthread -O5

clean:
	rm -f no_contention with_contention

run:
	echo "Running process with contention"
	./with_contention
	echo "-----------------------------------------"
	echo "Running without contention"
	./no_contention

