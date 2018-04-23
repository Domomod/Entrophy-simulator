#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <string>

class Display
{
public:
    Display(int width, int height, const std::string& title);

    void Clear(float r, float g, float b, float a);
    void Update();
    void Close();
    bool IsClosed();

    //getters
    //TODO(user#1#): paste getters to cpp file
    inline int GetWindowWidth() const
    {
        SDL_DisplayMode dm;

        if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
        {
            SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
            return 1;
        }

        return dm.w;
    }
    inline int GetWindowHeight() const
    {
        SDL_DisplayMode dm;

        if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
        {
            SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
            return 1;
        }

        return dm.h;
    }

    virtual ~Display();
protected:

private:
    Display(const Display& other) {}
    void operator=(const Display& other) {}

    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    bool m_isClosed;
};
#endif // DISPLAY_H
