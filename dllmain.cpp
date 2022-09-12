// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "PlayerEnt.h"
#include "Graphics.h"
#include "WindowUtility.h"
#include "EntityEntry.h"
#include "GAME_DATA.h"
#include "MvpMatrix.h"
#include "Esp.h"

void close(const char* error);
BOOL detourWglSwapBuffers(HDC hDc);


HMODULE g_hModule;
FILE* f;

typedef BOOL (_stdcall* wglSwapBuffers)(HDC hDc);
wglSwapBuffers pWglSwapBuffersOriginal = nullptr;
wglSwapBuffers pWglSwapBuffersTarget ;

HWND hAndle = NULL; //device content to window handle
Graphics * graphics = nullptr;
GAME_DATA * gameData;

Esp esp = { &graphics , &gameData };

DWORD  WINAPI hackFunc()
{
	AllocConsole();
	
	freopen_s(&f,"CONOUT$", "w", stdout);

	if (f)
	{
		std::cout << "injected" << std::endl;
		const wchar_t* moduelName = L"ac_client.exe";
		uintptr_t baseAdd = (uintptr_t)GetModuleHandle(moduelName);

		PlayerEnt * localPlayer = *(PlayerEnt **)(baseAdd+ 0x00109B74);

		if(!localPlayer) close("local Player not found");

		std::cout << "local player found at:" << std::hex << (*(uintptr_t*)localPlayer) << std::dec << std::endl;

		EntityEntry* entityList = new EntityEntry( 100 , (uintptr_t*)(baseAdd + 0x10F4F8),localPlayer );

		uintptr_t mvpMatrixBase = baseAdd + 0x101AE8;
		MvpMatrix* mcpMatrix = (MvpMatrix*)mvpMatrixBase;
		gameData = new GAME_DATA( localPlayer , entityList , mcpMatrix);
		
		


		MH_STATUS status;
		if ( ( status = MH_Initialize()) != MH_OK)
		{
			close(MH_StatusToString(status));
			return 0;

		}

		if (MH_CreateHookApiEx(
			L"Opengl32.dll" , "wglSwapBuffers" , 
			&detourWglSwapBuffers , 
			reinterpret_cast<void**>(&pWglSwapBuffersOriginal), reinterpret_cast<void**>(&pWglSwapBuffersTarget)) != MH_OK)
		{
			close("create hook failed");
			return 0;
		}

		MH_EnableHook(pWglSwapBuffersTarget);

		while (true)
		{
			if (GetAsyncKeyState(VK_DELETE) & 1)
			{
				break;
			}
		}

		MH_DisableHook(pWglSwapBuffersTarget);


	}
	close(nullptr);
	return 0;

}


BOOL detourWglSwapBuffers(HDC hDc)
{
	if (!hAndle)
	{
		hAndle = WindowFromDC(hDc);
		WindowUtil::WINDOW_ATT windowAtt = WindowUtil::getWindowAtt(hAndle);
		graphics = new Graphics(hAndle, windowAtt.width, windowAtt.height);
	}

	if (gameData)
	{
		std::vector<PlayerEnt*> list = gameData->entityEntry->getPlayers();
		if (!list.empty())
		{
			esp.drawPlayers(list);

		}
	}



	return pWglSwapBuffersOriginal(hDc);
}


void close( const char * error)
{
	MH_Uninitialize();

	if(graphics) delete graphics;

	if(error) std::cout << error << std::endl;
	else std::cout << "EXITING" << std::endl;
	Sleep(1000);
	f ? fclose(f) : NULL;
	delete gameData;
	FreeConsole();
	FreeLibraryAndExitThread(g_hModule, 0);
}




BOOL APIENTRY DllMain(
	HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_hModule = hModule;
		HANDLE hAndle;
		hAndle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)hackFunc, hModule, 0, nullptr);
		if (hAndle) CloseHandle(hAndle);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

