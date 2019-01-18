/**
 *	ADT untuk membaca file konfigurasi
 *
 *	@author Mufid Jamaluddin
 *	Dibuat Tanggal 15 Januari 2019
 **/
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "model.h"

using namespace Model;

namespace Config
{	
	/**
	 *	Mendapatkan List Data Komponen
	 **/
	Component * getListComponents();

	/**
 	 *	Membaca Data Konfigurasi dari File JSON 
 	 **/
	bool read();
	
	/**
	 *	Membaca Data Konfigurasi Awal State JSON
	 **/
	bool readState();
	
	/**
	 *	Membebaskan Memori Konfigurasi
	 **/
	void destroy();
	
	/**
	 *	Mendapatkan Konfigurasi Window
	 **/
	Window getWindow();
	
	/**
	 *	Mendapatkan Konfigurasi Awal State Kamera
	 **/
	Positiond getCamera();
	
	/**
	 *	Mendapatkan Konfigurasi Awal State 
	 **/
	Positiond getLookAt();
	
	/**
	 *	Menyimpan State 
	 **/
	bool saveState(Positiond camera); //, Positiond lookAt);
	
	/**
 	 *	Membaca Data Konfigurasi Ground
 	 **/
	Skybox getSkybox();
	
	/**
	 *	Mendapatkan Default Texture Component
	 **/
	TextureComponent getDefaultTextureComponent();
}

#endif
