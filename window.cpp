#include <math.h>
#include "config.h"
#include "model.h"
#include "window.h"
#include "skybox.h"
#include "components.h"

/**
 *	Sudut Arah Kamera
 **/
double angleHorizontal = 0.0;
double angleVertical = 0.0;

// merepresentasikan arah kamera
double lx = 0.0f, lz = -1.0f, ly = 0.1f;

/**
 *	Posisi Kamera
 **/
Positiond cameraPosition;

/**
 *	ID Window OpenGL
 **/
int winId;

/**
 *	List Komponen
 **/
Component * listComponents;

namespace WindowGL
{
	/**
	 *	Menggambar Komponen
	 **/
	void drawComponents()
	{
		//glDepthMask(GL_FALSE);
		
		Component * temp;
		
		// ke root
		temp = listComponents;
		
		glPushMatrix();
		
		glTranslatef(25, 0, 25);
		
		while(temp != NULL)
		{
			ComponentsGL::draw(temp);
			
			temp = temp->next;
		}
		
		glPopMatrix();
		
		//glDepthMask(GL_TRUE);
	}
	
	/**
	 *	Dealokasi Komponen
	 **/
	void freeComponent()
	{
		Component * temp;
		Component * temp2;
		
		// ke root
		temp = listComponents;
		
		while(temp != NULL)
		{
			temp2 = temp;
			
			temp = temp->next;
			
			free(temp2);
		}
	}
	
	/**
	 *	Menghandle Aksi Penggambaran Ulang
	 **/
	void onDisplay()
	{
		// Clear Warna dan Depth Buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		// Set Kamera
		gluLookAt(
			cameraPosition.x, cameraPosition.y, cameraPosition.z, 
			cameraPosition.x + lx, cameraPosition.y + ly, cameraPosition.z + lz, 
			0.0f, cameraPosition.y, 0.0f
		);
		
		// Gambar dari Konfigurasi
		drawComponents();
		
		// Gambar Skybox
		SkyboxGL::draw();
		
		glutSwapBuffers();
	}

	/**
	 *	Menghandle Aksi Perubahan Ukuran Layar
	 **/
	void onReshape(GLsizei width, GLsizei height)
	{
		if (height == 0) height = 1;

		float ratio = (float)width / height;

		glMatrixMode(GL_PROJECTION);

		glLoadIdentity();

		glViewport(0, 0, width, height);

		gluPerspective(45.0f, ratio, 0.1f, 100.0f);

		glMatrixMode(GL_MODELVIEW);
	}

	/**
	 *	Menghandle Klik dari Special Func (atas, bawah, kiri, kanan)s
	 **/
	void onSpecialKeyClick(int key, int xx, int yy)
	{
		float speed = 0.3f;

		switch (key)
		{
			case GLUT_KEY_LEFT:
				angleHorizontal -= 0.01f;
				lx = sin(angleHorizontal);
				lz = -cos(angleHorizontal);
				break;
	
			case GLUT_KEY_RIGHT:
				angleHorizontal += 0.01f;
				lx = sin(angleHorizontal);
				lz = -cos(angleHorizontal);
				break;
	
			case GLUT_KEY_UP:
				cameraPosition.x += lx * speed;
				cameraPosition.z += lz * speed;
				break;
	
			case GLUT_KEY_DOWN:
				cameraPosition.x -= lx * speed;
				cameraPosition.z -= lz * speed;
				break;
		}

		glutPostRedisplay();
	}

	/**
	 *	Menghandle Klik Keyboard
	 **/
	void onKeyboardClick(unsigned char key, int xx, int yy)
	{
		float speed = 0.1f;

		switch (key)
		{
			case 27:
				onDestroy();
				exit(0);
				break;
	
			// Keatas Naik
			case 'w':
				cameraPosition.y += speed;
				break;
	
			// Kebawah Turun
			case 's':
				cameraPosition.y -= speed;
				break;
			
			// Lihat Atas
			case 'e':
				ly += speed;
				break;
				
			// Lihat Bawah
			case 'd':
				ly -= speed;
				break;
		}
		
		glutPostRedisplay();
	}

	/**
	 *	Inisialisasi Window OpenGL
	 **/
	void initialize()
	{
		Model::Window window;
		
		window = Config::getWindow();
		cameraPosition = Config::getCamera();
		listComponents = Config::getListComponents();
		
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(window.positionX, window.positionY);
		glutInitWindowSize(window.sizeX, window.sizeY);
		winId = glutCreateWindow(window.title);

		glutDisplayFunc(onDisplay);
		glutReshapeFunc(onReshape);
		glutSpecialFunc(onSpecialKeyClick);
		glutKeyboardFunc(onKeyboardClick);
		
  		glClearColor(0.9f, 0.9f, 1.0f, 0.0f);
  		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  		glEnable(GL_DEPTH_TEST);
  		glLoadIdentity();
  	
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  		
  		SkyboxGL::setSize(window.sizeland);
		SkyboxGL::loadTexture();
		
		ComponentsGL::loadDefaultTexture();
	
		glutMainLoop();
	}

	/**
	 *	Menghandle Aksi Sebelum Destroy Window OpenGL jika tekan ESC
	 **/
	void onDestroy()
	{
		freeComponent();
		
		// Menyimpan Posisi Kamera
		Config::saveState(cameraPosition);
		
		// Destroy List JSON
		Config::destroy();
		
		// Destroy GLUT Windows
		glutDestroyWindow(winId);
	}
}
