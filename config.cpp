/**
 *	Membaca file konfigurasi
 *
 *	@author Mufid Jamaluddin
 *	Dibuat Tanggal 15 Januari 2019
 **/
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "config.h"
#include "constant.h"
#include "vendor/cJSON/cJSON.h"

using namespace std;
using namespace Model;

/**
 *	Deklarasi Global JSON Konfigurasi
 **/
cJSON * configData;

cJSON * stateData;

/**
 *	Implementasi
 **/
namespace Config
{
	/**
	 *	Mengubah cJSON ke Posisid 
	 **/
	Positiond cJSONtoPositiond(cJSON * item)
	{
		Positiond pos;
		cJSON * temp;
		
		temp = cJSON_GetObjectItem(item, "x");
		if(temp == NULL) pos.x = 1;
		else pos.x = temp->valuedouble;
		
		temp = cJSON_GetObjectItem(item, "y");
		if(temp == NULL) pos.y = 1;
		else pos.y = temp->valuedouble;
		
		temp = cJSON_GetObjectItem(item, "z");
		if(temp == NULL) pos.z = 1;
		else pos.z = temp->valuedouble;
		
		return pos;
	}
	
	/**
	 *	Mendapatkan Komponen
	 **/
	Component * getComponent(cJSON * item)
	{
		cJSON * temp;
		Component * component = new Component;
		
		// Type
		temp = cJSON_GetObjectItem(item, "type");
		if(temp == NULL) (*component).type = "";
		else (*component).type = temp->valuestring;

		// Size
		temp = cJSON_GetObjectItem(item, "size");
		(*component).size = cJSONtoPositiond(temp);

		// Rotate
		temp = cJSON_GetObjectItem(item, "rotate");
		if(temp == NULL) (*component).rotate = 0;
		else (*component).rotate = temp->valuedouble;
		
		// Translate
		temp = cJSON_GetObjectItem(item, "translate");
		(*component).translate = cJSONtoPositiond(temp);
		
		(*component).next = NULL; 
		
		return component;		
	}
	
	/**
	 *	Mendapatkan List Data Komponen
	 **/
	Component * getListComponents()
	{
		Component * listc;
		Component * temp;
		
		cJSON * list_components = cJSON_GetObjectItem(configData, "components");
		int component_size = cJSON_GetArraySize(list_components);
		cJSON * item;
		
		listc = getComponent(cJSON_GetArrayItem(list_components, 0));

		temp = listc;
		
		for(int i = 1; i < component_size; i++)
		{
			item = cJSON_GetArrayItem(list_components, i);
			
			(*temp).next = getComponent(item);
			
			temp = temp->next;
		}
		
		return listc;
	}
		
	/**
	 *	Membaca File state.config.json
	 **/
	bool readState()
	{
		char c;
		string content;
		
		if(stateData != NULL) cJSON_Delete(stateData);
		
		FILE *fileConfig = fopen(FILE_STATE_CONFIG,"r");
		
		if (fileConfig != NULL)
		{
			while ((c = fgetc(fileConfig)) != EOF) 
			{
				content += c;
			}
		
			content += '\0';
			
			//printf("%s\n%s\n", FILE_STATE_CONFIG, content.c_str());
			
			stateData = cJSON_Parse(content.c_str());
		    
			fclose(fileConfig);
			
			if(cJSON_IsInvalid(configData))
			{
				cout << ERROR_JSON_INVALID << " : " <<  FILE_STATE_CONFIG << endl;
				return false;
			}
			
			return true;
		}
		
		return false;
	}
	
	/**
 	 *	Membaca Data Konfigurasi dari File config.json 
 	 **/
	bool read()
	{
		char c;
		string content;
		
		if(configData != NULL) cJSON_Delete(configData);
		
		FILE *fileConfig = fopen(FILE_CONFIG,"r");
		
		if (fileConfig != NULL)
		{
			while ((c = fgetc(fileConfig)) != EOF) 
			{
				content += c;
			}
		
			content += '\0';
			
			//printf("%s\n%s\n", FILE_CONFIG, content.c_str());
			
			configData = cJSON_Parse(content.c_str());
		    
			fclose(fileConfig);
			
			if(cJSON_IsInvalid(configData))
			{
				cout << ERROR_JSON_INVALID << " : " << FILE_CONFIG << endl;
				cJSON_Delete(configData);
				return false;
			}
			
			return true;
		}
		
		return false;
	}
	
	/**
	 *	Membebaskan Memori Konfigurasi
	 **/
	void destroy()
	{
		if(configData != NULL) cJSON_Delete(configData);
		if(stateData != NULL) cJSON_Delete(stateData);
	}
	
	/**
	 *	Mendapatkan Konfigurasi Window
	 **/
	Window getWindow()
	{
		Window window;
		cJSON * windowJson;
		cJSON * title;
		cJSON * position;
		cJSON * size;
		cJSON * positionX;
		cJSON * positionY;
		cJSON * sizeX;
		cJSON * sizeY;
		cJSON * sizeland;
		
		windowJson = cJSON_GetObjectItem(configData, "window");
		
		title = cJSON_GetObjectItem(windowJson, "title");
		position = cJSON_GetObjectItem(windowJson, "position");
		size = cJSON_GetObjectItem(windowJson, "size");
		
		// TITLE
		if(title == NULL) window.title = DEFAULT_TITLE;
		else window.title = title->valuestring;
		
		// POSISI
		if((positionX = cJSON_GetObjectItem(position, "x")) == NULL) window.positionX = DEFALUT_POSITION;
		else window.positionX = positionX->valueint;
		
		if((positionY = cJSON_GetObjectItem(position, "y")) == NULL) window.positionY = DEFALUT_POSITION;
		else window.positionY = positionY->valueint;		
		
		// SIZE
		if((sizeX = cJSON_GetObjectItem(size, "x")) == NULL) window.sizeX = DEFAULT_SIZE;
		else window.sizeX = sizeX->valueint;
		
		if((sizeY = cJSON_GetObjectItem(size, "y")) == NULL) window.sizeY = DEFAULT_SIZE;
		else window.sizeY = sizeY->valueint;
		
		// Size SKYBOX
		if((sizeland = cJSON_GetObjectItem(size, "sizeland")) == NULL) window.sizeland = DEFAULT_SIZELAND;
		else window.sizeland = sizeland->valueint;
		
		return window;
	}
	
	/**
	 *	Mendapatkan Konfigurasi Awal State Kamera
	 **/
	Positiond getCamera()
	{
		Positiond camera;
		cJSON * cameraJson;
		cJSON * temp;
		
		// Default
		camera.x = DEFAULT_CAMERA_XZ;
		camera.y = DEFAULT_CAMERA_Y;
		camera.z = DEFAULT_CAMERA_XZ;
		
		cameraJson = cJSON_GetObjectItem(stateData, "camera");
		
		if(cameraJson != NULL)
		{
			temp = cJSON_GetObjectItem(cameraJson, "x");
			if(temp != NULL) camera.x = temp->valueint;
			
			temp = cJSON_GetObjectItem(cameraJson, "y");
			if(temp != NULL) camera.y = temp->valueint;
			
			temp = cJSON_GetObjectItem(cameraJson, "z");
			if(temp != NULL) camera.z = temp->valuedouble;
		}
		
		return camera;
	}
	
	/**
	 *	Mendapatkan Konfigurasi Awal State 
	 **
	Positiond getLookAt()
	{
		Positiond lookAt;
		cJSON * lookAtJson;
		cJSON * temp;
		
		// Default
		lookAt.x = DEFAULT_CAMERA_XZ;
		lookAt.y = DEFAULT_CAMERA_Y;
		lookAt.z = DEFAULT_CAMERA_XZ;
		
		lookAtJson = cJSON_GetObjectItem(configData, "lookat");
		
		if(lookAtJson != NULL)
		{
			temp = cJSON_GetObjectItem(lookAtJson, "x");
			if(temp != NULL) lookAt.x = temp->valuedouble;
			
			temp = cJSON_GetObjectItem(lookAtJson, "y");
			if(temp != NULL) lookAt.y = temp->valuedouble;
			
			temp = cJSON_GetObjectItem(lookAtJson, "z");
			if(temp != NULL) lookAt.z = temp->valuedouble;
		}
		
		return lookAt;		
	}
	*/
	
	/**
	 *	Menyimpan State 
	 **/
	bool saveState(Positiond camera)//, Positiond lookAt)
	{
		FILE * fileStateConfig; 
		cJSON * cameraJson;
		//cJSON * lookAtJson;
		char * content;
		
		if(stateData != NULL) cJSON_Delete(stateData);

		// ROOT
		stateData = cJSON_CreateObject();
		
		// NODE
		cJSON_AddItemToObject(stateData, "camera", cameraJson = cJSON_CreateObject());
		//cJSON_AddItemToObject(stateData, "lookat", lookAtJson = cJSON_CreateObject());
		
		cJSON_AddNumberToObject(cameraJson, "x", camera.x);
		cJSON_AddNumberToObject(cameraJson, "y", camera.y);
		cJSON_AddNumberToObject(cameraJson, "z", camera.z);
		
		/*
		cJSON_AddNumberToObject(lookAtJson, "x", lookAt.x);
		cJSON_AddNumberToObject(lookAtJson, "y", lookAt.y);
		cJSON_AddNumberToObject(lookAtJson, "z", lookAt.z);
		*/
		
		// Content
		content = cJSON_Print(stateData);
		
		// Buat File Temporary
		fileStateConfig = fopen(FILE_TEMP, "w");
		
		if(fileStateConfig == NULL)
		{
			free(content);
			
			return false;
		}
		
		fputs(content, fileStateConfig);
		
		fclose(fileStateConfig);
		
		// Delete File State Config
		remove(FILE_STATE_CONFIG);
		
		// Rename File Temp ke Config
		rename(FILE_TEMP, FILE_STATE_CONFIG);
		
		// Delete File Temp
		remove(FILE_TEMP);
		
		free(content);
		
		return true;
	}
	
	
	/**
	 *	Konfigurasi Skybox
 	 **/
	Skybox getSkybox()
	{
		Skybox skybox;
		cJSON * skyboxConfig;
		cJSON * temp;
		
		skyboxConfig = cJSON_GetObjectItem(configData, "skybox");

		if((temp = cJSON_GetObjectItem(skyboxConfig, "top")) == NULL) skybox.top = "";
		else skybox.top = temp->valuestring;
		
		if((temp = cJSON_GetObjectItem(skyboxConfig, "down")) == NULL) skybox.down = "";
		else skybox.down = temp->valuestring;
		
		if((temp = cJSON_GetObjectItem(skyboxConfig, "left")) == NULL) skybox.left = "";
		else skybox.left = temp->valuestring;
		
		if((temp = cJSON_GetObjectItem(skyboxConfig, "right")) == NULL) skybox.right = "";
		else skybox.right = temp->valuestring;
		
		if((temp = cJSON_GetObjectItem(skyboxConfig, "front")) == NULL) skybox.front = "";
		else skybox.front = temp->valuestring;
		
		if((temp = cJSON_GetObjectItem(skyboxConfig, "back")) == NULL) skybox.back = "";
		else skybox.back = temp->valuestring;
		
		return skybox;
	}
	
	/**
	 *	Mendapatkan Default Texture Component
	 **/
	TextureComponent getDefaultTextureComponent()
	{
		TextureComponent textureComponent;
		cJSON * defaultTexture;
		cJSON * temp;
		
		defaultTexture = cJSON_GetObjectItem(cJSON_GetObjectItem(configData, "default"), "components");
		
		if((temp = cJSON_GetObjectItem(defaultTexture, "pillar")) == NULL) textureComponent.pillar = "";
		else textureComponent.pillar = temp->valuestring;
		
		if((temp = cJSON_GetObjectItem(defaultTexture, "floorpillar")) == NULL) textureComponent.floorpillar = "";
		else textureComponent.floorpillar = temp->valuestring;
		
		if((temp = cJSON_GetObjectItem(defaultTexture, "rooffoundation")) == NULL) textureComponent.rooffoundation = "";
		else textureComponent.rooffoundation = temp->valuestring;
		
		if((temp = cJSON_GetObjectItem(defaultTexture, "roof")) == NULL) textureComponent.roof = "";
		else textureComponent.roof = temp->valuestring;
		
		if((temp = cJSON_GetObjectItem(defaultTexture, "roofpyramid")) == NULL) textureComponent.roofpyramid = "";
		else textureComponent.roofpyramid = temp->valuestring;
		
		if((temp = cJSON_GetObjectItem(defaultTexture, "mirrorpolban")) == NULL) textureComponent.mirrorpolban = "";
		else textureComponent.mirrorpolban = temp->valuestring;
		
		if((temp = cJSON_GetObjectItem(defaultTexture, "mirror")) == NULL) textureComponent.mirror = "";
		else textureComponent.mirror = temp->valuestring;
		
		if((temp = cJSON_GetObjectItem(defaultTexture, "wall")) == NULL) textureComponent.wall = "";
		else textureComponent.wall = temp->valuestring;
		/*
		char * s = cJSON_Print(defaultTexture);
		
		cout << s << endl;
		
		free(s);
		*/		
		return textureComponent;
	}
	
}
