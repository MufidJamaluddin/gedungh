#include "skybox.h"
#include "config.h"
#include "constant.h"
#include <windows.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "vendor/SOIL/src/SOIL.h"

/**
 *	Texture Skybox
 **/
int textureSkybox[] = {0, 0, 0, 0, 0, 0};

float sizeSkybox = 100.0f;

/**
 *	Penggambaran Skybox
 **/
namespace SkyboxGL
{
	/**
	 *	Mengubah Size Skybox
	 **/
	void setSize(int size)
	{
		sizeSkybox = (float) size;
	}
	
	/**
	 *	Membaca Skybox
	 **/
	void initSkybox(const char * dfile, const int type)
	{
		if(strlen(dfile) > 0)
		{
			textureSkybox[type] = SOIL_load_OGL_texture
			(
				dfile,
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_MIPMAPS
			);
			
			glBindTexture(GL_TEXTURE_2D, textureSkybox[type]);
			
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
	
	/**
	 *	Membaca Texture Skybox
	 **/
	void loadTexture()
	{
		Model::Skybox skybox;
		
		skybox = Config::getSkybox();
		
		initSkybox(skybox.top, SKYBOX_TOP);
		initSkybox(skybox.down, SKYBOX_DOWN);
		initSkybox(skybox.front, SKYBOX_FRONT);
		initSkybox(skybox.back, SKYBOX_BACK);
		initSkybox(skybox.left, SKYBOX_LEFT);
		initSkybox(skybox.right, SKYBOX_RIGHT);
		
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	/**
	 *	Penggambaran Skybox
	 **/
	void draw()
	{
		glDepthMask(GL_FALSE);	
		
		glColor3f(0.9f, 0.9f, 1.0f);
		
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, textureSkybox[SKYBOX_RIGHT]);
			glBegin(GL_QUADS);
			
				// Kanan
	  			glTexCoord2i(0, 0); glVertex3f(sizeSkybox, sizeSkybox,       0.0f);
	  			glTexCoord2i(1, 0); glVertex3f(sizeSkybox, sizeSkybox, sizeSkybox);
	  			glTexCoord2i(1, 1); glVertex3f(sizeSkybox,       0.0f, sizeSkybox);
	  			glTexCoord2i(0, 1); glVertex3f(sizeSkybox,       0.0f,       0.0f);
			
			glEnd();
			
			glBindTexture(GL_TEXTURE_2D, textureSkybox[SKYBOX_LEFT]);
			glBegin(GL_QUADS);
			
				// Kiri
	  			glTexCoord2i(0, 0); glVertex3f(0.0f, sizeSkybox, sizeSkybox);
	  			glTexCoord2i(1, 0); glVertex3f(0.0f, sizeSkybox,       0.0f);
	  			glTexCoord2i(1, 1); glVertex3f(0.0f,       0.0f,       0.0f);
	  			glTexCoord2i(0, 1); glVertex3f(0.0f,       0.0f, sizeSkybox);
	
			glEnd();
			
			glBindTexture(GL_TEXTURE_2D, textureSkybox[SKYBOX_TOP]);
			glBegin(GL_QUADS);
	
				// Atas
				glTexCoord2i(0, 0); glVertex3f(      0.0f, sizeSkybox, sizeSkybox);
				glTexCoord2i(1, 0); glVertex3f(sizeSkybox, sizeSkybox, sizeSkybox);
				glTexCoord2i(1, 1); glVertex3f(sizeSkybox, sizeSkybox,       0.0f);
				glTexCoord2i(0, 1); glVertex3f(      0.0f, sizeSkybox,       0.0f);
	 
			glEnd();
			
			glBindTexture(GL_TEXTURE_2D, textureSkybox[SKYBOX_DOWN]);
			glBegin(GL_QUADS);
	
				// Bawah
				glTexCoord2i(0, 0); glVertex3f(      0.0f, 0.0f,       0.0f);
				glTexCoord2i(1, 0); glVertex3f(sizeSkybox, 0.0f,       0.0f);
				glTexCoord2i(1, 1); glVertex3f(sizeSkybox, 0.0f, sizeSkybox);
				glTexCoord2i(0, 1); glVertex3f(      0.0f, 0.0f, sizeSkybox);
	
			glEnd();
			
			glBindTexture(GL_TEXTURE_2D, textureSkybox[SKYBOX_FRONT]);
			glBegin(GL_QUADS);
	
				// Depan 	
				glTexCoord2i(0, 0); glVertex3f(      0.0f, sizeSkybox, 0.0f);
				glTexCoord2i(1, 0); glVertex3f(sizeSkybox, sizeSkybox, 0.0f);
				glTexCoord2i(1, 1); glVertex3f(sizeSkybox,       0.0f, 0.0f);
				glTexCoord2i(0, 1); glVertex3f(      0.0f,       0.0f, 0.0f);
	
			glEnd();
			
			glBindTexture(GL_TEXTURE_2D, textureSkybox[SKYBOX_BACK]);
			glBegin(GL_QUADS);
	
				// Belakang	
			  	glTexCoord2i(0, 0); glVertex3f(sizeSkybox, sizeSkybox, sizeSkybox);
			  	glTexCoord2i(1, 0); glVertex3f(      0.0f, sizeSkybox, sizeSkybox);
			  	glTexCoord2i(1, 1); glVertex3f(      0.0f,       0.0f, sizeSkybox);
			  	glTexCoord2i(0, 1); glVertex3f(sizeSkybox,       0.0f, sizeSkybox);
	  	
		  	glEnd();
		  	
		  	glBindTexture(GL_TEXTURE_2D, 0);
		  	
		glPopMatrix();
	
		glDepthMask(GL_TRUE);
	}
	
}
