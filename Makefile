run:
	clang++ test.cpp -o test -lraylib -lm -ldl -lpthread -lGL -lX11
	./test
