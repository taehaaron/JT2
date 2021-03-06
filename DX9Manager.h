#pragma once

#include "defines.h"

namespace JungleTime{

class DX9Manager
{
public:
	DX9Manager(void);
	~DX9Manager(void);

	static unsigned int WINAPI MainHookDX9(void *param);

	//Our dirty hooks...
	static void HookEndScene(LPDIRECT3DDEVICE9 pDevice);
	static void HookPreReset();
	static void HookPostReset(LPDIRECT3DDEVICE9 pDevice, HRESULT res);

	//For the status message
	void SetStatusText(wstring txt);
	void SetStatusIsRender(bool isRender);

	//Temporary indicators for the EndScene
	bool isInitiated; //for a first initiation, from dll attach thread
	bool isFirstFrame; //for a first hooked EndScene, to show a message "loading..."
	bool isFirstInitiatedFrame; //for a first frame, after all initiation of the Core
	bool isReadyToRender; //for a usual render
	
	static DX9Manager* singleton;
private:

	//On the first frame we intercept
	virtual bool OnDXFirstFrame(LPDIRECT3DDEVICE9 pDevice);
	//On hooking done
	virtual bool OnDXInitiated(void);
	//On each frame
	virtual void OnDXEndScene(LPDIRECT3DDEVICE9 pDevice);
	//On reset
	virtual void OnDXResetDevice(LPDIRECT3DDEVICE9 pDevice);
	//On resources unloading
	virtual void OnDXLostDevice();

	HANDLE hDXHookThread;

	//For the "loading..." label and status text
	LPD3DXFONT statusFont;
	RECT statusRect;
	wstring statusText;
	bool isRenderStatus;

	LPDIRECT3DDEVICE9 d3d9Device;
	bool isDeviceReady;
};

}