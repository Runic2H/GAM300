#pragma warning(disable : 28251)

#include    "GameApp.h"



#if _DEBUG
#pragma comment( linker, "/subsystem:console" )
int main(int argc, const char** argv)
{

    (void)argc, (void)argv;
    return WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(), 0);
}
#else
#pragma comment( linker, "/subsystem:windows" )
#endif

TDS::GamApp* g_GameApp{ nullptr };

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (g_GameApp != NULL)
    {
        g_GameApp->handleMessages(hWnd, uMsg, wParam, lParam);
    }
    return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    void(hPrevInstance), (void)lpCmdLine;
    const wchar_t classname[] = L"TDSWindowClass"; //class name

    g_GameApp = new TDS::GamApp(hInstance, nCmdShow, classname, WndProc);
    g_GameApp->Initialize();
    g_GameApp->Run();
    g_GameApp->Update();
    g_GameApp->~GamApp();

    return 0;
}