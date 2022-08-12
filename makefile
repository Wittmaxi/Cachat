make: 
	make calls
	clang++ ./cachat/main.cpp ./cachat_calls.o -o cachat # compile against own object-file for custom system calls 

make calls: 
	clang++ -c ./cachat_calls/*.cpp -o cachat_calls.o

test: 
	-rm ./ut
	make calls
	clang++ ./cachat/main.cpp ./cachat_calls.o -o ut -lCMD --std=c++17
	./ut -f ./test_file.cac