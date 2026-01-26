all: install 

install: compile
	cmake --install build --prefix install 

compile: build
	cmake --build build

build: 
	cmake -B build \
	-DCMAKE_BUILD_TYPE=Debug 

format:
	find ./src -regex '.*\.[c|h]pp' -exec  clang-format -style=llvm -i {} +

clean:
	rm -rf install build

.PHONY: all clean build compile install
