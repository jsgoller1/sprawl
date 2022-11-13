install-devtools:
	apt-get -qq install -y \
	byzanz-record \ 
	clang \
	clang-tools \
	lldb \
	libsdl2-dev \
	valgrind

record-screen:
	byzanz-record -d 5 --x=760 --y=200 --width=1920 --height=1080 bin/recorded_screen.gif
