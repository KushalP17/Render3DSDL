#include <SDL3/SDL_rect.h>

#ifndef POINTS_3D_H
#define POINTS_3D_H

class Points
{
    private:
        float x; // -1 to 1
        float y; // -1 to 1
        float z; // -inf to inf
        static constexpr float sizePoint = 5;

    public:
        Points(float x, float y, float z);

        Points Project2D();

        Points CartesianTopLeftRecenter(int widthScreen, int heightScreen);

        Points PointScaleCoords(float scale);

        SDL_FRect PointToRect(float scale);

        Points TranslateX(float dx);

        Points TranslateY(float dy);

        Points TranslateZ(float dz);

        Points Translate(float dx, float dy, float dz);

        Points RotateXZPlane(float angle);

        Points RotateYZPlane(float angle);

        Points RotateXYPlane(float angle);

        Points RotateZYXAxes(float AnglesXYZ[3]);

        float getX();
        float getY();
        float getZ();

};

#endif