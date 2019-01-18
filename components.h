/**
 *	ADT untuk Komponen 
 *
 *	@author Mufid Jamaluddin
 *	Dibuat Tanggal 15 Januari 2019
 **/
#pragma once
 
#include "model.h"

using namespace Model;
 
namespace ComponentsGL
{
	/**
	 *	Mendapatkan Default Texture
	 **/
	void loadDefaultTexture();
	
	/**
	 *	Menggambar Komponen Sesuai Tipe
	 **/
	void draw(Component * component);
	
	/**
	 *	Menggambar Tiang
	 **/
	void drawPillar(Component * component);
	 
	/**
	 *	Menggambar Lantai Gantung
	 **/
	void drawFloorPillar(Component * component);
	 
	/**
	 *	Menggambar Genteng Tipe Dasar 
	 **/
	void drawRoofFoundation(Component * component);
	 
	/**
	 *	Menggambar Genteng Atas
	 **/
	void drawRoof(Component * component);
	 
	/**
	 *	Menggambar Genteng Piramid
	 **/
	void drawRoofPyramid(Component * component);
	
	/**
	 *	Menggambar Kaca Berlogo Polban
	 **/
	void drawMirrorPolban(Component * component);
	 
	/**
	 *	Menggambar Kaca Biasa
	 **/
	void drawMirror(Component * component);
	 
	/**
	 *	Menggambar Tembok
	 **/
	void drawWall(Component * component);
}
