#include "pch.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "Screen.h"
#include "Actor.h"
#include "Log.h"
#include "Snake.h"
#include <Python.h>
#include <discord_rpc.h>
#include <time.h>

#undef max

static const char* ApplicationID = "581978887697727488";
static int64_t rpcStart;

struct GameSettings
{
	int Height = 20;
	int Width = 20;
	int Framerate = 7;
};

GameSettings ParseArgs(int argc, char* argv[])
{
	GameSettings settings;
	for (int i = 0; i + 1 < argc; i++)
	{
		std::string arg(argv[i]);
		int next;
		try
		{
			next = std::stoi(argv[i + 1]);
		}
		catch (...) { /* Conversion error */ }
		if (arg.compare("-h") == 0)
			settings.Height = next;
		else if (arg.compare("-w") == 0)
			settings.Width = next;
		else if (arg.compare("-f") == 0)
			settings.Framerate = next;
	}
	return settings;
}

void HookKeyboard(Screen& s)
{
	// Create keyboard hook
	HHOOK keyHook = SetWindowsHookEx(WH_KEYBOARD_LL, s.KeyboardProc, 0, 0);
	// Begin message loop
	MSG msg;
	while (!GetMessage(&msg, NULL, NULL, NULL))
	{
		if (msg.message == WM_QUIT)
			break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(keyHook);
}

void UpdateRPC(int score)
{
	char buffer[256];
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	sprintf_s(buffer, "Apples consumed: %d", score);
	discordPresence.details = buffer;
	discordPresence.startTimestamp = rpcStart;
	discordPresence.largeImageKey = "icon";
#ifdef _DEBUG
	discordPresence.smallImageKey = "debug-icon";
#else
	discordPresence.smallImageKey = "release-icon";
#endif
	Discord_UpdatePresence(&discordPresence);
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

int main(int argc, char** argv)
{
	PyObject *pFunc, *pModule, *pName, *pValue;

	const wchar_t* libs = L"libs";
	wchar_t exe[MAX_PATH];
	GetModuleFileName(NULL, exe, MAX_PATH);

	int exeLen = 0;
	wchar_t libPath[MAX_PATH];

	for (int i = 0; exe[i] != '\0'; i++)
		exeLen++;

	for (int j = 0; j < exeLen - 4; j++)
	{
		if (j >= exeLen - 9)
			libPath[j] = libs[j - (exeLen - 9)];
		else 
			libPath[j] = exe[j];
	}

	Py_SetPath((const wchar_t*)libPath);
	Py_Initialize();
	PyObject* sysPath = PySys_GetObject("path");
	PyList_Append(sysPath, PyUnicode_FromString("."));
	PyList_Append(sysPath, PyUnicode_FromString("Scripts"));

	pName = PyUnicode_FromString("score_tracker");
	pModule = PyImport_Import(pName);

	GameSettings settings = ParseArgs(argc, argv);
	int framerate = settings.Framerate;
#ifdef _DEBUG
	std::cout << "Running in debug mode." << std::endl;
	std::cout << "Default framerate: " << framerate << std::endl;
	while ((std::cout << "Framerate lock: ") && !(std::cin >> framerate))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
#endif
	// Instatiate screen object
	Screen screen(settings.Height, settings.Width);

	// Start keybaord hook on thread with message loop
	std::thread hookThread(HookKeyboard, std::ref(screen));

	int startPos[2] = { 3, 3 };
	Snake snake('X', 'O', startPos, screen, 5);
	screen.Add(&snake);
	snake.Draw();

	// Inital render of screen
	ShowConsoleCursor(false);
	screen.Render();

	auto std_time = []{ return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()); };
	std::chrono::milliseconds last = std_time();

	Discord_Initialize(ApplicationID, NULL, 1, NULL);
	rpcStart = time(NULL);

	while (!screen.shouldClose)
	{
		// Limit framerate
		std::chrono::milliseconds now = std_time();
		if (now.count() - last.count() < 1000 / framerate)
			continue;
		last = now;
		
		CLEAR_LOG();

		// Call update to invoke OnUpdate on all drawables
		screen.Update();

		LOG(
			"               +------------------------------------------------------------+\n"
			"               |                        DEBUG MODE                          |\n"
			"               +------------------------------------------------------------+\n"
		);
#ifdef _DEBUG
		std::vector<Drawable*> drawables = screen.GetDrawables();
		std::string test;
		for (int i = 0; i < drawables.size(); i++)
		{
			test += drawables[i]->Character;
			test += " (";
			test += std::to_string(drawables[i]->GetX()) + ",";
			test += std::to_string(drawables[i]->GetY());
			test += ")\n";
		}
		LOG(test.c_str());
#endif
		// Check if any drawables need to be redrawn
		if (screen.ShouldRedraw())
			screen.Render();

		UpdateRPC(screen.GetScore());
	}

	Discord_ClearPresence();
	Discord_Shutdown();

	// Tell thread to stop and wait for it to stop
	PostThreadMessage(GetThreadId(hookThread.native_handle()), WM_QUIT, 0, 0);
	hookThread.join();

	int score = screen.GetScore();
	pFunc = PyObject_GetAttrString(pModule, "save_score");
	PyObject_CallObject(pFunc, Py_BuildValue("(i)", score));
	pFunc = PyObject_GetAttrString(pModule, "get_high_score");
	pValue = PyObject_CallObject(pFunc, NULL);
	int highScore = _PyLong_AsInt(pValue);

	Py_Finalize();

	// Tell player they suck
	system("cls");
	std::cout << "Game over!" << std::endl;
	std::cout << "Your score was: " << score << "\nYour high score is: " << highScore << std::endl;
	std::cin.get();
	return 0;
}
