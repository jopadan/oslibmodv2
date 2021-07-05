#ifndef _WINDOW_12H

typedef struct {
	Display* display;
	Window* window;
} OSL_X11;

typedef struct {
} OSL_GLFW;

typedef struct {
	S2D_Window window;
} OSL

typedef struct {
	OSL_DISPLAY display;
	OSL_PLATFORM_GLFW      glfw;
	OSL_PLATFORM_X11       x11;
	OSL_PLATFORM_WIN       win;
	OSL_PLATFORM_S2D       s2d;
	OSL_PLATFORM_SIGIL     sigil;
	OSL_PLATFORM_GLUT      glut;
	OSL_PLATFORM_GLCONTEXT gl;
} OSL_WINDOW;

OSL_WINDOW* oslCreateWindow(
#endif
