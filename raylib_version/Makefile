all:
	@g++ src/*.cpp -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Iinlcude
run:
	@g++ src/*.cpp -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Iinclude
	@./main
	@rm main

clean:
	@rm main
