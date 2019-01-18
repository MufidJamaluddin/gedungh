/**
 *	Program Utama untuk Life Cycle Window OpenGL
 *
 *	@author Mufid Jamaluddin
 */
#pragma once

#include <windows.h>
#include <GL/glut.h>

namespace WindowGL
{
	/**
	 *	Inisialisasi Window OpenGL
	 **/
	void initialize();
	
	/**
	 *	Menghandle Aksi Sebelum Destroy Window OpenGL jika tekan ESC
	 **/
	void onDestroy();

	/**
	 *	Menghandle Aksi Penggambaran Ulang
	 **/
	void onDisplay();

	/**
	 *	Menghandle Aksi Perubahan Ukuran Layar
	 **/
	void onReshape(GLsizei width, GLsizei height);

	/**
	 *	Menghandle Klik dari Special Func (atas, bawah, kiri, kanan)s
	 **/
	void onSpecialKeyClick(int key, int xx, int yy);

	/**
	 *	Menghandle Klik Keyboard
	 **/
	void onKeyboardClick(unsigned char key, int xx, int yy);
}
