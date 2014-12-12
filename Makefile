CC=clang
CFLAGS=-pedantic -std=c11 -Wall -g -O3
GL_LIBS=-L/usr/local/lib -lglfw3 -lrt -lXrandr -lXi -lGL -lm -ldl -lXrender -ldrm -lXdamage -lX11-xcb -lxcb-glx -lxcb-dri2 -lxcb-dri3 -lxcb-present -lxcb-sync -lxshmfence -lXxf86vm -lXfixes -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp  
OS_GL_LIBS=-L/usr/local/Cellar/glfw3/3.0.4/lib -lglfw3
OS_X_OTHER_LIBS=-framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo  
OS_X_FLAGS= -I/usr/local/Cellar/glfw3/3.0.4/include 


snakeGL:
	$(CC) $(CFLAGS) -o  $(GL_LIBS)

clean:
	rm -rf bin/*

