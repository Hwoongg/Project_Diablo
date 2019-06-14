#pragma once

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#pragma comment(lib, "ws2_32")

#include <winsock2.h>
#include <ws2tcpip.h>

#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <Mmsystem.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <list>
#include <map>

#include "CInput.h"
#include "CSprite.h"
#include "CTexture.h"

#include "AnimationInfo.h"

#include "IGameObject.h"
#include "CGameObject.h"
#include "Hero.h"
#include "Enemy.h"

#include "CObjectManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "UIButton.h"

#include "CD3DApp.h"
#include "CGame.h"

#include "Server.h"


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }