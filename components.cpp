/**
 *	Komponen Penggambaran
 *
 *	@author Mufid Jamaluddin
 *	Dibuat Tanggal 15 Januari 2019
 *	Diubah Tanggal 17 Januari 2019
 **/
#include "components.h"
#include "config.h"
#include "constant.h"
#include <string.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <iostream>
#include "vendor/SOIL/src/SOIL.h"

/**
 *	Texture Components
 **/
int textureComponent[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

namespace ComponentsGL
{
	/**
	 *	Membaca Texture Component
	 **/
	void initTexture(const char * dfile, const int type)
	{
		//std::cout << dfile << " : ";
		
		if(strlen(dfile) > 0)
		{
			textureComponent[type] = SOIL_load_OGL_texture
			(
				dfile,
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_NTSC_SAFE_RGB
			);
			
			glBindTexture(GL_TEXTURE_2D, textureComponent[type]);
			
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_LINEAR);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		
		//std::cout << textureComponent[type] << std::endl;
	}
	
	/**
	 *	Membaca Default Texture Component
	 **/
	void loadDefaultTexture()
	{
		TextureComponent defaultDirTexture;
		
		defaultDirTexture = Config::getDefaultTextureComponent();
		
		initTexture(defaultDirTexture.floorpillar, COMPONENT_FLOORPILLAR);
		initTexture(defaultDirTexture.mirror, COMPONENT_MIRROR);
		initTexture(defaultDirTexture.mirrorpolban, COMPONENT_MIRRORPOLBAN);
		initTexture(defaultDirTexture.pillar, COMPONENT_PILLAR);
		initTexture(defaultDirTexture.roof, COMPONENT_ROOF);
		initTexture(defaultDirTexture.rooffoundation, COMPONENT_ROOFFOUNDATION);
		initTexture(defaultDirTexture.roofpyramid, COMPONENT_ROOFPYRAMID);
		initTexture(defaultDirTexture.wall, COMPONENT_WALL);
		
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	/**
	 *	Pilih Mana?
	 **/
	void draw(Component * component)
	{
		if(strcmp((*component).type, "pillar") == 0)
		{
			if((*component).texture == 0) (*component).texture = textureComponent[COMPONENT_PILLAR];
			drawPillar(component);
		}
		else if(strcmp((*component).type, "floorpillar") == 0)
		{
			if((*component).texture == 0) (*component).texture = textureComponent[COMPONENT_FLOORPILLAR];
			drawPillar(component);
		}
		else if(strcmp((*component).type, "rooffoundation") == 0)
		{
			if((*component).texture == 0) (*component).texture = textureComponent[COMPONENT_ROOFFOUNDATION];
			drawRoofFoundation(component);
		}
		else if(strcmp((*component).type, "roof") == 0)
		{
			if((*component).texture == 0) (*component).texture = textureComponent[COMPONENT_ROOF];
			drawRoof(component);
		}
		else if(strcmp((*component).type, "roofpyramid") == 0)
		{
			if((*component).texture == 0) (*component).texture = textureComponent[COMPONENT_ROOFPYRAMID];
			drawRoofPyramid(component);
		}
		else if(strcmp((*component).type, "mirrorpolban") == 0)
		{
			if((*component).texture == 0) (*component).texture = textureComponent[COMPONENT_MIRRORPOLBAN];
			drawMirrorPolban(component);
		}
		else if(strcmp((*component).type, "mirror") == 0)
		{
			if((*component).texture == 0) (*component).texture = textureComponent[COMPONENT_MIRROR];
			drawMirror(component);
		}
		else if(strcmp((*component).type, "wall") == 0)
		{
			if((*component).texture == 0) (*component).texture = textureComponent[COMPONENT_WALL];
			drawWall(component);
		}
	}
	
	/**
	 *	Menggambar Tiang
	 **/
	void drawPillar(Component * component)
	{
		double rx = (*component).size.x / 2;
		double rz = (*component).size.z / 2;
		
		glColor3f(8.1f, 8.0f, 8.0f);
		
		glPushMatrix();
		
			glTranslated((*component).translate.x, (*component).translate.y, (*component).translate.z);
			
			
			glBindTexture(GL_TEXTURE_2D, (*component).texture);
			glBegin(GL_QUADS);
				
				// BAWAH
				glTexCoord2i(0, 0); glVertex3d(-rx, 0, -rz);
	  			glTexCoord2i(1, 0); glVertex3d( rx, 0, -rz);
	  			glTexCoord2i(1, 1); glVertex3d( rx, 0,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx, 0, rz);
			
				// ATAS
				glTexCoord2i(0, 0); glVertex3d(-rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 0); glVertex3d( rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 1); glVertex3d (rx, (*component).size.y,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx, (*component).size.y,  rz);

				// KIRI
				glTexCoord2i(0, 0); glVertex3d(-rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 0); glVertex3d(-rx,                0, -rz);
	  			glTexCoord2i(1, 1); glVertex3d(-rx,                0,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx, (*component).size.y,  rz);

				// KANAN
				glTexCoord2i(0, 0); glVertex3d(rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 0); glVertex3d(rx,                0, -rz);
	  			glTexCoord2i(1, 1); glVertex3d(rx,                0,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(rx, (*component).size.y,  rz);

				// DEPAN
				glTexCoord2i(0, 0); glVertex3d(-rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 0); glVertex3d( rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 1); glVertex3d( rx,                0, -rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx,                0, -rz);

				// BELAKANG
				glTexCoord2i(0, 0); glVertex3d(-rx, (*component).size.y, rz);
	  			glTexCoord2i(1, 0); glVertex3d( rx, (*component).size.y, rz);
	  			glTexCoord2i(1, 1); glVertex3d( rx,                0, rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx,                0, rz);
			glEnd();

		glPopMatrix();
		
		// UDAHAN
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	 
	/**
	 *	Menggambar Lantai Gantung
	 **/
	void drawFloorPillar(Component * component)
	{
	 	double rx = (*component).size.x / 2;
		double rz = (*component).size.z / 2;
	
		glColor3f(0.7f, 0.7f, 0.65f);
	
		glPushMatrix();
		
			glTranslated((*component).translate.x, (*component).translate.y, (*component).translate.z);
			
			glBindTexture(GL_TEXTURE_2D, (*component).texture);
			glBegin(GL_POLYGON);
			
				// BAWAH
				glTexCoord2i(0, 0); glVertex3d(-rx, 0, -rz);
	  			glTexCoord2i(1, 0); glVertex3d( rx, 0, -rz);
	  			glTexCoord2i(1, 1); glVertex3d( rx, 0,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx, 0, rz);

				// KIRI
				glTexCoord2i(0, 0); glVertex3d(-rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 0); glVertex3d(-rx,                   0, -rz);
	  			glTexCoord2i(1, 1); glVertex3d(-rx,                   0,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx, (*component).size.y,  rz);

				// KANAN
				glTexCoord2i(0, 0); glVertex3d(rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 0); glVertex3d(rx,                   0, -rz);
	  			glTexCoord2i(1, 1); glVertex3d(rx,                   0,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(rx, (*component).size.y,  rz);

				// DEPAN
				glTexCoord2i(0, 0); glVertex3d(-rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 0); glVertex3d( rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 1); glVertex3d( rx,                   0, -rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx,                   0, -rz);
	  			
	  			// BELAKANG
				glVertex3d(-rx, (*component).size.y, rz);
	  			glVertex3d( rx, (*component).size.y, rz);
	  			glVertex3d( rx,                0, rz);
	  			glVertex3d(-rx,                0, rz);
	  			
			glEnd();
			
		glPopMatrix();
		
		// UDAHAN
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	 
	/**
	 *	Menggambar Genteng Tipe Dasar 
	 **/
	void drawRoofFoundation(Component * component)
	{
	 	double rx_atas, rx_bawah, rz_atas, rz_bawah;
	 	
	 	rx_bawah = (*component).size.x / 2;
	 	rx_atas = rx_bawah - 1.6;
	 	
	 	rz_bawah = (*component).size.z / 2;
	 	rz_atas = rz_bawah - 1.6;
	 	
		//glColor3f(1.0f, 0.8f, 0.8f);
	 	
	 	/*
	 	// ALAS BAWAH
		glPushMatrix();
			glTranslated((*component).translate.x, (*component).translate.y, (*component).translate.z);
			
			glPushMatrix();
				glTranslated(rx_bawah, 0, rz_bawah);
				glScaled((*component).size.x, 1, (*component).size.z);
					
				glColor3f(1.0f, 0.8f, 0.8f);
				glutSolidCube(0.5);
					
				glColor3f(1.0f, 1.0f, 1.0f);
				glutWireCube(0.5);
			glPopMatrix();
		glPopMatrix();
	 	*/
	 	glColor3f(1.0f, 0.8f, 0.8f);
	 	
		glPushMatrix();
		
			glTranslated((*component).translate.x, (*component).translate.y, (*component).translate.z);


			glBindTexture(GL_TEXTURE_2D, (*component).texture);
			glBegin(GL_POLYGON);
			
				// BAWAH
				glTexCoord2i(0, 0); glVertex3d(-rx_bawah, 0, -rz_bawah);
	  			glTexCoord2i(1, 0); glVertex3d( rx_bawah, 0, -rz_bawah);
	  			glTexCoord2i(1, 1); glVertex3d( rx_bawah, 0,  rz_bawah);
	  			glTexCoord2i(0, 1); glVertex3d(-rx_bawah, 0,  rz_bawah);
			
				// ATAS
				glTexCoord2i(0, 0); glVertex3d(-rx_atas, (*component).size.y, -rz_atas);
	  			glTexCoord2i(1, 0); glVertex3d( rx_atas, (*component).size.y, -rz_atas);
	  			glTexCoord2i(1, 1); glVertex3d (rx_atas, (*component).size.y,  rz_atas);
	  			glTexCoord2i(0, 1); glVertex3d(-rx_atas, (*component).size.y,  rz_atas);
			
				// KIRI
				glTexCoord2i(0, 0); glVertex3d(-rx_atas ,  (*component).size.y, -rz_atas );
	  			glTexCoord2i(1, 0); glVertex3d(-rx_bawah,                  0.5, -rz_bawah);
	  			glTexCoord2i(1, 1); glVertex3d(-rx_bawah,                  0.5,  rz_bawah);
	  			glTexCoord2i(0, 1); glVertex3d(-rx_atas ,  (*component).size.y,  rz_atas );

				// KANAN
				glTexCoord2i(0, 0); glVertex3d(rx_atas , (*component).size.y, -rz_atas );
	  			glTexCoord2i(1, 0); glVertex3d(rx_bawah,                 0.5, -rz_bawah);
	  			glTexCoord2i(1, 1); glVertex3d(rx_bawah,                 0.5,  rz_bawah);
	  			glTexCoord2i(0, 1); glVertex3d(rx_atas , (*component).size.y,  rz_atas );

				// DEPAN
				glTexCoord2i(0, 0); glVertex3d(-rx_atas, (*component).size.y, -rz_atas);
	  			glTexCoord2i(1, 0); glVertex3d( rx_atas, (*component).size.y, -rz_atas);
	  			glTexCoord2i(1, 1); glVertex3d( rx_bawah,                0.5, -rz_bawah);
	  			glTexCoord2i(0, 1); glVertex3d(-rx_bawah,                0.5, -rz_bawah);

				// BELAKANG
				glTexCoord2i(0, 0); glVertex3d(-rx_atas , (*component).size.y, rz_atas );
	  			glTexCoord2i(1, 0); glVertex3d( rx_atas , (*component).size.y, rz_atas );
	  			glTexCoord2i(1, 1); glVertex3d( rx_bawah,                 0.5, rz_bawah);
	  			glTexCoord2i(0, 1); glVertex3d(-rx_bawah,                 0.5, rz_bawah);
			glEnd();
			
		glPopMatrix();
		
		// UDAHAN
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	 
	/**
	 *	Menggambar Genteng Atas
	 **/
	void drawRoof(Component * component)
	{
	 	double rx = (*component).size.x / 2;
		double rz = (*component).size.z / 2;
	
		glColor3f(1.0f, 0.8f, 0.8f);
	
		glPushMatrix();
		
			glTranslated((*component).translate.x, (*component).translate.y, (*component).translate.z);
			
			glBindTexture(GL_TEXTURE_2D, (*component).texture);
			glBegin(GL_POLYGON);
				
				// BAWAH
				glTexCoord2i(0, 0); glVertex3d(-rx, 0, -rz);
	  			glTexCoord2i(1, 0); glVertex3d( rx, 0, -rz);
	  			glTexCoord2i(1, 1); glVertex3d( rx, 0,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx, 0,  rz);

			glEnd();
			
			glBindTexture(GL_TEXTURE_2D, (*component).texture);
			glBegin(GL_POLYGON);

				// PINGGIR KIRI
				glTexCoord2i(0, 0); glVertex3d(-rx,                   0, -rz);
	  			glTexCoord2i(1, 0); glVertex3d(  0, (*component).size.y, -rz);
	  			glTexCoord2i(1, 1); glVertex3d(  0, (*component).size.y,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx,                   0,  rz);

			glEnd();
			
			glBindTexture(GL_TEXTURE_2D, (*component).texture);
			glBegin(GL_POLYGON);

				// PINGGIR KANAN
				glTexCoord2i(0, 0); glVertex3d( 0, (*component).size.y, -rz);
	  			glTexCoord2i(1, 0); glVertex3d(rx,                   0, -rz);
	  			glTexCoord2i(1, 1); glVertex3d(rx,                   0,  rz);
	  			glTexCoord2i(0, 1); glVertex3d( 0, (*component).size.y,  rz);
				
			glEnd();
			
			glBegin(GL_TRIANGLES);
				
				// DEPAN
				glVertex3d(-rx,                   0, rz);
	  			glVertex3d(  0, (*component).size.y, rz);
	  			glVertex3d( rx,                   0, rz);

				// BELAKANG
				glVertex3d(-rx,                   0, -rz);
	  			glVertex3d(  0, (*component).size.y, -rz);
	  			glVertex3d( rx,                   0, -rz);
	  			
			glEnd();
			
		glPopMatrix();
		
		// UDAHAN
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	 
	/**
	 *	Menggambar Genteng Piramid
	 **/
	void drawRoofPyramid(Component * component)
	{
	 	double rx = (*component).size.x / 2;
		double rz = (*component).size.z / 2;
		
		glColor4f(0.8f, 0.8f, 1.0f, 0.8f);
		
		glPushMatrix();
		
			glTranslated((*component).translate.x, (*component).translate.y, (*component).translate.z);
			
			glBindTexture(GL_TEXTURE_2D, (*component).texture);
			glBegin(GL_TRIANGLES);
				// KANAN
				glTexCoord2i(0, 0); glVertex3d(-rx,                   0, -rz);
	  			glTexCoord2i(1, 0); glVertex3d(  0, (*component).size.y,   0);
	  			glTexCoord2i(1, 1); glVertex3d(-rx,                   0,  rz);

				// KIRI
				glTexCoord2i(0, 0); glVertex3d(rx,                   0, -rz);
	  			glTexCoord2i(1, 0); glVertex3d( 0, (*component).size.y,   0);
	  			glTexCoord2i(1, 1); glVertex3d(rx,                   0,  rz);

				// BELAKANG
				glTexCoord2i(0, 0); glVertex3d(  0, (*component).size.y,   0);
	  			glTexCoord2i(1, 0); glVertex3d(-rx,                   0, -rz);
	  			glTexCoord2i(1, 1); glVertex3d( rx,                   0, -rz);

				// DEPAN
				glTexCoord2i(0, 0); glVertex3d(  0, (*component).size.y,  0);
	  			glTexCoord2i(1, 0); glVertex3d(-rx,                   0, rz);
	  			glTexCoord2i(1, 1); glVertex3d( rx,                   0, rz);
			glEnd();
			
		glPopMatrix();
		
		// UDAHAN
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	 
	/**
	 *	Menggambar Kaca Berlogo Polban
	 **/
	void drawMirrorPolban(Component * component)
	{
	 	double rx = (*component).size.x / 2;
		double rz = (*component).size.z / 2;
		
		glColor4f(0.9f, 0.9f, 1.0f, 0.8f);
		//glColor3f(0.7f, 0.7f, 0.8f);
		
		glPushMatrix();
		
			glTranslated((*component).translate.x, (*component).translate.y, (*component).translate.z);
			
			glBindTexture(GL_TEXTURE_2D, (*component).texture);
			glBegin(GL_QUADS);
			
				// BAWAH
				glVertex3d(-rx, 0, -rz);
	  			glVertex3d( rx, 0, -rz);
	  			glVertex3d( rx, 0,  rz);
	  			glVertex3d(-rx, 0, rz);
			
				// ATAS
				glVertex3d(-rx, (*component).size.y, -rz);
	  			glVertex3d( rx, (*component).size.y, -rz);
	  			glVertex3d (rx, (*component).size.y,  rz);
	  			glVertex3d(-rx, (*component).size.y,  rz);

				// KANAN
				glTexCoord2i(0, 0); glVertex3d(-rx,                   0, -rz);
	  			glTexCoord2i(1, 0); glVertex3d(-rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 1); glVertex3d(-rx, (*component).size.y,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx,                   0,  rz);

				// KIRI
				glTexCoord2i(0, 0); glVertex3d(rx,                   0, -rz);
	  			glTexCoord2i(1, 0); glVertex3d(rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 1); glVertex3d(rx, (*component).size.y,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(rx,                   0,  rz);

				// DEPAN
				glTexCoord2i(0, 0); glVertex3d(-rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 0); glVertex3d( rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 1); glVertex3d( rx,                   0, -rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx,                   0, -rz);

				// BELAKANG
				glTexCoord2i(0, 0); glVertex3d(-rx, (*component).size.y, rz);
	  			glTexCoord2i(1, 0); glVertex3d( rx, (*component).size.y, rz);
	  			glTexCoord2i(1, 1); glVertex3d( rx,                   0, rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx,                   0, rz);
			
			glEnd();
			
		glPopMatrix();
		
		// UDAHAN
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	 
	/**
	 *	Menggambar Kaca Biasa
	 **/
	void drawMirror(Component * component)
	{
	 	double rx = (*component).size.x / 2;
		double rz = (*component).size.z / 2;
		
		glColor4f(0.8f, 0.8f, 0.9f, 0.3f);
		
		glPushMatrix();
		
			glTranslated((*component).translate.x, (*component).translate.y, (*component).translate.z);
				
			glBindTexture(GL_TEXTURE_2D, (*component).texture);
			glBegin(GL_QUADS);			
				// BAWAH
				glTexCoord2i(0, 0); glVertex3d(-rx, 0, -rz);
	  			glTexCoord2i(1, 0); glVertex3d( rx, 0, -rz);
	  			glTexCoord2i(1, 1); glVertex3d( rx, 0,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx, 0, rz);
			
				// ATAS
				glTexCoord2i(0, 0); glVertex3d(-rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 0); glVertex3d( rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 1); glVertex3d (rx, (*component).size.y,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx, (*component).size.y,  rz);

				// KIRI
				glTexCoord2i(0, 0); glVertex3d(-rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 0); glVertex3d(-rx,                   0, -rz);
	  			glTexCoord2i(1, 1); glVertex3d(-rx,                   0,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx, (*component).size.y,  rz);

				// KANAN
				glTexCoord2i(0, 0); glVertex3d(rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 0); glVertex3d(rx,                   0, -rz);
	  			glTexCoord2i(1, 1); glVertex3d(rx,                   0,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(rx, (*component).size.y,  rz);

				// DEPAN
				glTexCoord2i(0, 0); glVertex3d(-rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 0); glVertex3d( rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 1); glVertex3d( rx,                   0, -rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx,                   0, -rz);
			
				// BELAKANG
				glVertex3d(-rx, (*component).size.y, rz);
	  			glVertex3d( rx, (*component).size.y, rz);
	  			glVertex3d( rx,                0, rz);
	  			glVertex3d(-rx,                0, rz);
			
			glEnd();
			
		glPopMatrix();	 	
		
		// UDAHAN
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	 
	/**
	 *	Menggambar Tembok
	 **/
	void drawWall(Component * component)
	{
	 	double rx = (*component).size.x / 2;
		double rz = (*component).size.z / 2;
		
		glColor3f(0.8f, 0.8f, 0.8f);
		
		glPushMatrix();
		
			glTranslated((*component).translate.x, (*component).translate.y, (*component).translate.z);
			
			glBindTexture(GL_TEXTURE_2D, (*component).texture);
			glBegin(GL_QUADS);
				// BAWAH
				glTexCoord2i(0, 0); glVertex3d(-rx, 0, -rz);
	  			glTexCoord2i(1, 0); glVertex3d( rx, 0, -rz);
	  			glTexCoord2i(1, 1); glVertex3d( rx, 0,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx, 0, rz);
			
				// ATAS
				glTexCoord2i(0, 0); glVertex3d(-rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 0); glVertex3d( rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 1); glVertex3d (rx, (*component).size.y,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx, (*component).size.y,  rz);

				// KIRI
				glTexCoord2i(0, 0); glVertex3d(-rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 0); glVertex3d(-rx,                0, -rz);
	  			glTexCoord2i(1, 1); glVertex3d(-rx,                0,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx, (*component).size.y,  rz);

				// KANAN
				glTexCoord2i(0, 0); glVertex3d(rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 0); glVertex3d(rx,                0, -rz);
	  			glTexCoord2i(1, 1); glVertex3d(rx,                0,  rz);
	  			glTexCoord2i(0, 1); glVertex3d(rx, (*component).size.y,  rz);

				// DEPAN
				glTexCoord2i(0, 0); glVertex3d(-rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 0); glVertex3d( rx, (*component).size.y, -rz);
	  			glTexCoord2i(1, 1); glVertex3d( rx,                0, -rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx,                0, -rz);

				// BELAKANG
				glTexCoord2i(0, 0); glVertex3d(-rx, (*component).size.y, rz);
	  			glTexCoord2i(1, 0); glVertex3d( rx, (*component).size.y, rz);
	  			glTexCoord2i(1, 1); glVertex3d( rx,                0, rz);
	  			glTexCoord2i(0, 1); glVertex3d(-rx,                0, rz);
			glEnd();
			
		glPopMatrix();
		
		// UDAHAN
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
