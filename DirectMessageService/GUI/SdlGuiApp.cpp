#include "SdlGuiApp.h"

// APP
GUI::GUI::GUI()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

GUI::GUI::~GUI()
{
    TTF_Quit();
    IMG_Quit();
    SDL_VideoQuit();
    SDL_Quit();
}


// WINDOW
GUI::Window::Window(const char* title)
{
    pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!pWindow)
    {
        throw std::runtime_error(SDL_GetError());
    }
}


GUI::Window::Window(const char* title, int w, int h, int x, int y, Uint32 flags)
{

    pWindow = SDL_CreateWindow(title, x, y, w, h, flags);

    if (!pWindow)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

GUI::Window::~Window()
{
    SDL_DestroyWindow(pWindow);
}

GUI::Window::operator SDL_Window* ()
{
    return pWindow;
}


// RENDERER
GUI::Renderer::Renderer(SDL_Window* win)
{
    pRenderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!pRenderer)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

GUI::Renderer::~Renderer()
{
    SDL_DestroyRenderer(pRenderer);
}

void GUI::Renderer::clear()
{
    SDL_SetRenderDrawColor(pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(pRenderer);
}

void GUI::Renderer::present()
{
    SDL_RenderPresent(pRenderer);
}

GUI::Renderer::operator SDL_Renderer* ()
{
    return pRenderer;
}
