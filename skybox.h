#ifndef __SKYBOX_H__
#define __SKYBOX_H__

/** 
 *	Menggambar Langit
 *	@author Mufid Jamaluddin
 */
namespace SkyboxGL
{
	/**
	 *	Mengubah Size Skybox
	 **/
	void setSize(int size);
	
	/**
	 *	Membaca Texture Skybox
	 **/
	void loadTexture();

	/**
	 *	Menghandle Penggambaran Skybox
	 **/
	void draw();

}

#endif
