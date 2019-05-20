#include "pch.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "Screen.h"
#include "Actor.h"
#include "Log.h"
#include "Snake.h"

#undef max

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

int main()
{
	int framerate;
#ifdef _DEBUG
	std::cout << "Running in debug mode." << std::endl;
	while ((std::cout << "Framerate lock: ") && !(std::cin >> framerate))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
#else
	framerate = 7;
#endif
	// Instatiate screen object
	Screen screen(20, 50);

	// Start keybaord hook on thread with message loop
	std::thread hookThread(HookKeyboard, std::ref(screen));

	int startPos[2] = { 3, 3 };
	Snake snake('X', 'O', startPos, screen, 5);
	screen.Add(&snake);
	snake.Draw();

	// Inital render of screen
	screen.Render();

	auto time = [](){ return  std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()); };
	std::chrono::milliseconds last = time();

	while (!screen.shouldClose)
	{
		// Limit framerate
		std::chrono::milliseconds now = time();
		if (now.count() - last.count() < 1000 / framerate)
			continue;
		last = now;
		
		CLEAR_LOG();

		// Call update to invoke OnUpdate on all drawables
		screen.Update();
		//snake.Update();

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
	}
	
	// Tell thread to stop and wait for it to stop
	PostThreadMessage(GetThreadId(hookThread.native_handle()), WM_QUIT, 0, 0);
	hookThread.join();

	// Tell player they suck
	system("cls");
	std::cout << "Game over!" << std::endl;
	std::cin.get();
	return 0;
}