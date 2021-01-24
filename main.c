/********************************************

This example was copied mainly from
https://sdl.beuc.net/sdl.wiki/Using_OpenGL_With_SDL
but has been adapted for SDL2.

License - The MIT License (https://mit-license.org)

Copyright © 2021 Vaughan Milliman

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

********************************************/

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>

GLboolean should_rotate = GL_TRUE;

void kill(int code) {
	SDL_Quit();
	exit(code);
}

void input(SDL_Keysym* keysym) {
	switch (keysym->sym) {
		case SDLK_ESCAPE:
			kill(0);
			break;
		case SDLK_SPACE:
			should_rotate = !should_rotate;
			break;
		default:
			break;
	}
}

void events()
{
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_KEYDOWN:
				input(&event.key.keysym);
				break;
			case SDL_QUIT:
				kill(0);
				break;
			default:
				break;
		}
	}
}

void draw(SDL_Window* window) {
	static float angle = 0.0f;

	static GLfloat v0[] = {-1.0f, -1.0f, 1.0f};
	static GLfloat v1[] = {1.0f, -1.0f, 1.0f};
	static GLfloat v2[] = {1.0f, 1.0f, 1.0f};
	static GLfloat v3[] = {-1.0f, 1.0f, 1.0f};
	static GLfloat v4[] = {-1.0f, -1.0f, -1.0f};
	static GLfloat v5[] = {1.0f, -1.0f, -1.0f};
	static GLfloat v6[] = {1.0f, 1.0f, -1.0f};
	static GLfloat v7[] = {-1.0f, 1.0f, -1.0f};

	static GLubyte red[] = {255, 0, 0, 255};
	static GLubyte green[] = {0, 255, 0, 255};
	static GLubyte blue[] = {0, 0, 255, 255};
	static GLubyte white[] = {255, 255, 255, 255};
	static GLubyte yellow[] = {0, 255, 255, 255};
	static GLubyte black[] = {0, 0, 0, 255};
	static GLubyte orange[] = {255, 255, 0, 255};
	static GLubyte purple[] = {255, 0, 255, 0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(angle, 0.0, 1.0, 0.0);

	if (should_rotate) {
		if (++angle > 360.0f) {
			angle = 0.0f;
		}
	}

	glBegin(GL_TRIANGLES);

	glColor4ubv(red);
	glVertex3fv(v0);
	glColor4ubv(green);
	glVertex3fv(v1);
	glColor4ubv(blue);
	glVertex3fv(v2);

	glColor4ubv(red);
	glVertex3fv(v0);
	glColor4ubv(blue);
	glVertex3fv(v2);
	glColor4ubv(white);
	glVertex3fv(v3);

	glColor4ubv(green);
	glVertex3fv(v1);
	glColor4ubv(black);
	glVertex3fv(v5);
	glColor4ubv(orange);
	glVertex3fv(v6);

	glColor4ubv(green);
	glVertex3fv(v1);
	glColor4ubv(orange);
	glVertex3fv(v6);
	glColor4ubv(blue);
	glVertex3fv(v2);

	glColor4ubv(black);
	glVertex3fv(v5);
	glColor4ubv(yellow);
	glVertex3fv(v4);
	glColor4ubv(purple);
	glVertex3fv(v7);

	glColor4ubv(black);
	glVertex3fv(v5);
	glColor4ubv(purple);
	glVertex3fv(v7);
	glColor4ubv(orange);
	glVertex3fv(v6);

	glColor4ubv(yellow);
	glVertex3fv(v4);
	glColor4ubv(red);
	glVertex3fv(v0);
	glColor4ubv(white);
	glVertex3fv(v3);

	glColor4ubv(yellow);
	glVertex3fv(v4);
	glColor4ubv(white);
	glVertex3fv(v3);
	glColor4ubv(purple);
	glVertex3fv(v7);

	glColor4ubv(white);
	glVertex3fv(v3);
	glColor4ubv(blue);
	glVertex3fv(v2);
	glColor4ubv(orange);
	glVertex3fv(v6);

	glColor4ubv(white);
	glVertex3fv(v3);
	glColor4ubv(orange);
	glVertex3fv(v6);
	glColor4ubv(purple);
	glVertex3fv(v7);

	glColor4ubv(green);
	glVertex3fv(v1);
	glColor4ubv(red);
	glVertex3fv(v0);
	glColor4ubv(yellow);
	glVertex3fv(v4);

	glColor4ubv(green);
	glVertex3fv(v1);
	glColor4ubv(yellow);
	glVertex3fv(v4);
	glColor4ubv(black);
	glVertex3fv(v5);

	glEnd();

	SDL_GL_SwapWindow(window);
}

void opengl(int width, int height) {
	float ratio = (float)width / (float)height;

	glShadeModel(GL_SMOOTH);

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	glClearColor(0, 0, 0, 0);
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, ratio, 1.0, 1024.0);
}

int main()
{
	int width;
	int height;
	int flags;

	SDL_Renderer* renderer;
	SDL_Window* window;

	int windowFlags;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Failure, SDL error - %s\n", SDL_GetError());
		kill(1);
	}

	width = 640;
	height = 480;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;

	window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);

	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	if (window == 0){
		fprintf(stderr, "Failure, SDL error - %s\n", SDL_GetError());
		kill(1);
	}
	opengl(width, height);

	while (1) {

		events();

		draw(window);

		SDL_Delay(50);
	}

	return 0;
}
