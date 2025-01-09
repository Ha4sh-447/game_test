run:
	clang++ test.cpp -o test -lraylib -lm -ldl -lpthread -lGL -lX11
	./test

run2:
	clang++ tester.cpp -o testies -lraylib -lm -ldl -lpthread -lGL -lX11
	./testies


