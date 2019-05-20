#pragma once
#include <Windows.h>
#include <vector>
#include "Drawable.h"
#include "Updateable.h"

class Screen
{
private:
	std::vector<Drawable*> drawables;
	std::vector<Updateable*> updateables;
	int height, width;
	static bool keys[128];
	static std::vector<const char*> messages;
public:
	bool shouldClose;

	Screen(int h, int w) : height(h), width(w) {};
	Screen(int h, int w, int rm) : height(h), width(w) {};

	static void Log(const char* message);
	static void ClearLog();
	int GetHeight() const;
	int GetWidth() const;
	void Render();
	void Add(Drawable* drawable);
	void Add(Updateable* updateable);
	bool Destroy(Drawable* drawable);
	void Update();
	bool ShouldRedraw();
	Drawable* DrawableAt(int x, int y);
	static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	bool GetInput(char key);
	std::vector<Drawable*> GetDrawables() const;
};
