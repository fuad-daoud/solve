run:
	zig build && time ./zig-out/bin/main
run-fast:
	g++ -o main main.cpp && time ./main
run-fast-fast:
	g++ -O3 -march=native -ffast-math -fomit-frame-pointer main.cpp -o main && time ./main

