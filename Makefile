all:
	g++ *.cpp -lpthread -o test

clean:
	rm test
	