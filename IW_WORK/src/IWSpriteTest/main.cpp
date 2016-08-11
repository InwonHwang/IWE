// include the basic windows header files and the Direct3D header file
#include"stdafx.h"
#include "Device.h"
#include "IWETexture.h"
#include "IWESprite.h"
#include "IWESpriteRenderer.h"

// define the screen resolution and keyboard macros
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

IWETexture texture;
IWESprite sprite;
IWESpriteRenderer spriteRenderer;

void render_frame(void);    // renders a single frame

							// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL, L"WindowClass", L"Our Direct3D Program",
		WS_EX_TOPMOST | WS_POPUP, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	CDevice::GetInstance()->Init(hWnd);

	D3DXCreateTextureFromFileEx(g_Device,    // the device pointer
		L"Panel2.png",    // the new file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&texture._d3dTexture9);    // load to sprite

	sprite.setTexture(texture);
	spriteRenderer.setSprite(sprite);

	MSG msg;

	while (TRUE)
	{
		DWORD starting_point = GetTickCount();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		render_frame();

		// check the 'escape' key
		if (KEY_DOWN(VK_ESCAPE))
			PostMessage(hWnd, WM_DESTROY, 0, 0);

		while ((GetTickCount() - starting_point) < 25);
	}


	return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}




// this is the function used to render a single frame
void render_frame(void)
{
	// clear the window to a bright red
	g_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 0, 0), 1.0f, 0);

	g_Device->BeginScene();    // begins the 3D scene

	g_Sprite->Begin(D3DXSPRITE_ALPHABLEND);    // // begin sprite drawing with transparency

	spriteRenderer.update();	

	g_Sprite->End();    // end sprite drawing

	g_Device->EndScene();    // ends the 3D scene

	g_Device->Present(NULL, NULL, NULL, NULL);

	return;
}


