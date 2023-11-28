#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

namespace GUI
{

    class GUI
    {
    public:
        GUI();
        ~GUI();
    };

    class Window
    {
    public:
        Window(const char* title);
        Window(const char* title, int w, int h, int x = SDL_WINDOWPOS_UNDEFINED,
            int y = SDL_WINDOWPOS_UNDEFINED, Uint32 flags = SDL_WINDOW_SHOWN);
        ~Window();

        operator SDL_Window* ();

    private:
        SDL_Window* pWindow;
    };

    class Renderer
    {
    public:
        Renderer(SDL_Window* win);
        ~Renderer();

        void clear();
        void present();

        operator SDL_Renderer* ();

    private:
        SDL_Renderer* pRenderer;
    };













};

