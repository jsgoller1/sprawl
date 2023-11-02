install-devtools:
	apt-get -qq install -y \
	byzanz-record \ 
	clang \
	clang-tools \
	lldb \
	libsdl2-dev \
	valgrind

sdl-setup:
	cd tmp; \
	wget https://github.com/libsdl-org/SDL/releases/download/release-2.26.2/SDL2-2.26.2.zip; \
	unzip SDL2-2.26.2.zip; \
	cd SDL2-2.26.2/; \
	cmake -S . -B build && cmake --build build && sudo cmake --install build; \
	cp /tmp/SDL2-2.26.2/include/* ./3rdparty/; \
	cp /tmp/SDL2-2.26.2/libSDL2-2.0.so ./3rdparty


sdl-img-setup:
	cd tmp; \
	wget https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.2/SDL2_image-2.6.2.zip; \
	unzip SDL2_image-2.6.2.zip; \
	cd SDL2_image-2.6.2; \
	cmake -S . -B build && cmake --build build && sudo cmake --install build; \
	cp /tmp/SDL2_image-2.6.2/SDL_image.h ./3rdparty; \
	cp /tmp/SDL2_image-2.6.2/build/libSDL2_image.so ./3rdparty
	

