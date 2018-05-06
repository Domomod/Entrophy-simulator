#include "display.h"
#include <iostream>
#include <GL/glew.h>

Display::Display(int width, int height, const std::string& title)
{
    //jeœli bêdê u¿ywa³ SDL do czegoœ wiêcej ni¿ tworzenia okien- to przeniosê to poza klasê Display(np do maina);
    SDL_Init(SDL_INIT_EVERYTHING);

    //ile przeznaczê na zapisanie koloru czerwonego, w tym wypadku oko³o 256 odcieni
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    //w sumie 32 bity przeznaczone na przechowanie danych o kolorze + kana³ alfa
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //zalokuj 32 bity na informacje o jednym pixelu
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //zalokuj pamiêæ na drugie okno -do doublebufferingu

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    m_glContext = SDL_GL_CreateContext(m_window);

    GLenum status = glewInit();

    if(status != GLEW_OK) // jeœli GLEW ma problem to mamy problem ;)
    {
        std::cerr << "Glew failed to initialize!" << std::endl;
    }

    m_isClosed = false;

    //glViewport(0, 0, 0.8 * width, height);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

Display::~Display()
{
    //usuwam w odwrotnej kolejnoœci ni¿ inicjalizowa³em!
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a)
{
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::Close()
{
    m_isClosed=true;
}

bool Display::IsClosed()
{
    return m_isClosed;
}

void Display::Use() 
{
	SDL_GL_MakeCurrent(m_window, m_glContext);
}

void Display::Use(SDL_GLContext context)
{
	SDL_GL_MakeCurrent(m_window, context);
}

void Display::Update()
{
	SDL_GL_SwapWindow(m_window);
}
