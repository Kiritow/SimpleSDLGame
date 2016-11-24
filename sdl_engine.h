#include <SDL2/SDL.h>
#include <cstdio>
#include <memory>
#include <string>
using namespace std;

#undef main
/*
Link Configure
 -lSDL2 -lSDL2main -lSDL2_test
*/

namespace _sdl_buildin_namespace
{
class _init_sdl_class
{
public:
    _init_sdl_class()
    {
        int ret=SDL_Init(SDL_INIT_EVERYTHING);
        if(ret!=0)
        {
            fprintf(stderr,"Failed To Init SDL2 System.\n");
            exit(0);
        }
        /// Init Done.
    }
    ~_init_sdl_class()
    {
        SDL_Quit();
    }
} _init_sdl_obj;
}/// End of namespace _sdl_buildin_namespace


namespace sdl
{
void delay(int Delay_ms)
{
    SDL_Delay(Delay_ms);
}

class texture
{
public:
    unique_ptr<SDL_Texture,void (*)(SDL_Texture*)> ptr;
    texture() : ptr(unique_ptr<SDL_Texture,void(*)(SDL_Texture*)>(nullptr,SDL_DestroyTexture))
    {

    }
};

class rendererX
{
public:
    SDL_Renderer* ren;
};

texture LoadTexture(const std::string &file, rendererX renx)
{
    SDL_Renderer* ren=renx.ren;
    //Initialize to nullptr to avoid dangling pointer issues
    SDL_Texture *rawtexture = nullptr;
    //Load the image
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
    //If the loading went ok, convert to texture and return the texture
    if (loadedImage != nullptr)
    {
        rawtexture = SDL_CreateTextureFromSurface(ren, loadedImage);
        SDL_FreeSurface(loadedImage);
        //Make sure converting went ok too
        if (rawtexture == nullptr)
        {
            //logSDLError(std::cout, "CreateTextureFromSurface");
        }
    }
    else
    {
        //logSDLError(std::cout, "LoadBMP");
    }
    texture x;
    x.ptr.reset(rawtexture);
    return x;
}

class window
{
public:
    window(string title,int Width,int Height)
    {
        wnd=SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,Width,Height,SDL_WINDOW_SHOWN);
        pen=SDL_CreateRenderer(wnd,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    }
    ~window()
    {
        SDL_DestroyRenderer(pen);
        SDL_DestroyWindow(wnd);
    }
    void Draw(SDL_Texture *tex, SDL_Rect dstRect, SDL_Rect *clip = NULL,
              float angle = 0.0, int xPivot = 0, int yPivot = 0,
              SDL_RendererFlip flip = SDL_FLIP_NONE)
    {
        //Convert pivot pos from relative to object's center to screen space
        xPivot += dstRect.w / 2;
        yPivot += dstRect.h / 2;
        //SDL expects an SDL_Point as the pivot location
        SDL_Point pivot = { xPivot, yPivot };
        //Draw the texture
        SDL_RenderCopyEx(pen, tex, clip, &dstRect, angle, &pivot, flip);
    }
    void Draw(texture& tex, SDL_Rect dstRect, SDL_Rect *clip = NULL,
              float angle = 0.0, int xPivot = 0, int yPivot = 0,
              SDL_RendererFlip flip = SDL_FLIP_NONE)
    {
        Draw(tex.ptr.get(), dstRect, clip ,angle , xPivot, yPivot,flip);
    }
    void Clear()
    {
        SDL_RenderClear(pen);
    }
    void Update()
    {
        SDL_RenderPresent(pen);
    }
    rendererX getRendererX()
    {
        rendererX ren;
        ren.ren=pen;
        return ren;
    }
    SDL_Rect Box()
    {
        {
            SDL_Rect mBox;
            SDL_GetWindowSize(wnd, &mBox.w, &mBox.h);
            return mBox;
        }
    }
private:
    SDL_Window* wnd;
    SDL_Renderer* pen;
};

}/// End of namespace sdl
