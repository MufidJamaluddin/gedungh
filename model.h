/**
 *	ADT untuk Model Penggambaran
 *
 *	@author Mufid Jamaluddin
 *	Dibuat Tanggal 15 Januari 2019
 **/

#ifndef __MODEL_H__
#define __MODEL_H__

namespace Model
{
	/**
	 *	Struct Posisi di 3-Dimensi	
	 **/
	typedef struct Position {
		int x;
	 	int y;
	 	int z;
	} Position;
	
	typedef struct Positiond {
		double x;
	 	double y;
	 	double z;
	} Positiond;
	 
	/**
	 *	Struct Komponen u/ Penggambaran Gedung
	 **/
	typedef struct Component{
		const char * type;
		Positiond size;
		double rotate;
		Positiond translate;
		int texture;
		Component * next;
	} Component;
	
	typedef struct TextureComponent{
		const char * pillar;
		const char * floorpillar;
		const char * rooffoundation;
		const char * roof;
		const char * roofpyramid;
		const char * mirrorpolban;
		const char * mirror;
		const char * wall;
	} TextureComponent;
	
	/**
	 *	Struct untuk Konfigurasi Window
	 **/
	typedef struct Window{
		const char * title;
		int positionX;
		int positionY;
		int sizeX;
		int sizeY;
		int sizeland;
	} Window;
	
	/**
	 *	Struct untuk direktori 6 sisi Skybox
	 **/
	typedef struct Skybox {
		const char * right;
		const char * left;
		const char * top;
		const char * down;
		const char * back;
		const char * front;
	} Skybox;
}

#endif
