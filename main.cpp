#include "window.h"
#include "config.h"

int main(int argc, char** argv)
{
	// Baca File Config
	Config::read();
	Config::readState();
	
	// Inisialisasi GLUT
	glutInit(&argc, argv);
	
	// Inisialisasi Window OpenGL
	WindowGL::initialize();

	return 0;
}
