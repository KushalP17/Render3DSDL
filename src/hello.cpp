#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <math.h>
#include <Points3D.hpp>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <time.h>
// #include <iostream>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static int w = 0;
static int h = 0;
static long long int FrameCounter = 0;
static float anglesXYZ[3] = {0};

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    /* Create the window */
    if (!SDL_CreateWindowAndRenderer("Hello World", 1000, 1000, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    // SDL_MaximizeWindow(window);

    srand(time(NULL));
    
    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{

    const float scale = 2.0f;
    const float dz = .01;
    const float dAngle = 2*M_PI/1000;

    anglesXYZ[rand() % 3] += dAngle;

    Points cubeVertices[8] = {
        Points(.5, .5, .5), 
        Points(-.5, .5, .5), 
        Points(-.5, -.5, .5), 
        Points(.5, -.5, .5),
        Points(.5, .5, -.5), 
        Points(-.5, .5, -.5), 
        Points(-.5, -.5, -.5), 
        Points(.5, -.5, -.5)
    };

    int vertLines[12][2] = 
    {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0},
        {4, 5},
        {5, 6},
        {6, 7},
        {7, 4},
        {0, 4},
        {1, 5},
        {2, 6},
        {3, 7}
    };

    /* Center the message and scale it up */
    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_SetRenderScale(renderer, scale, scale);
    
    /* Draw the message */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    // for(Points vertex : cubeVertices)
    // {
        // SDL_FRect rectangle = vertex.RotateXYPlane(anglesXYZ[2]).RotateXZPlane(anglesXYZ[1]).RotateYZPlane(anglesXYZ[0]).TranslateZ(2).Project2D().CartesianTopLeftRecenter(w, h).PointToRect(scale);
    //     SDL_RenderFillRect(renderer, &rectangle);
    // }

    for(auto& pairPoints : vertLines)
    {
        Points p1 = cubeVertices[pairPoints[0]].RotateXYPlane(anglesXYZ[2]).RotateXZPlane(anglesXYZ[1]).RotateYZPlane(anglesXYZ[0]).TranslateZ(2).Project2D().CartesianTopLeftRecenter(w, h).PointScaleCoords(scale);
        Points p2 = cubeVertices[pairPoints[1]].RotateXYPlane(anglesXYZ[2]).RotateXZPlane(anglesXYZ[1]).RotateYZPlane(anglesXYZ[0]).TranslateZ(2).Project2D().CartesianTopLeftRecenter(w, h).PointScaleCoords(scale);
        SDL_RenderLine(renderer, p1.getX(), p1.getY(), p2.getX(), p2.getY());
    }


    SDL_RenderPresent(renderer);
    FrameCounter++;


    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
}