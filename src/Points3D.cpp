#include <Points3D.hpp>
#include <math.h>
#include <SDL3/SDL_rect.h>

Points::Points(float x, float y, float z) : x(x), y(y), z(z) {};

Points Points::Project2D()
{
    return Points{x/z, y/z, z};
}

Points Points::CartesianTopLeftRecenter(int widthScreen, int heightScreen)
{
    return Points((x+1)/2*widthScreen, (1-(y+1)/2)*heightScreen, z);
}

Points Points::PointScaleCoords(float scale)
{
    return {x/scale, y/scale, z};
}

SDL_FRect Points::PointToRect(float scale)
{
    return {x/scale - sizePoint/2, y/scale - sizePoint/2, sizePoint, sizePoint};
}

Points Points::TranslateX(float dx) 
{
    return Points(x + dx, y, z);
}

Points Points::TranslateY(float dy) 
{
    return Points(x, y + dy, z);
}

Points Points::TranslateZ(float dz) 
{
    return Points(x, y, z + dz);
}

Points Points::Translate(float dx, float dy, float dz)
{
    return Points(x + dx, y + dy, z + dz);
}

Points Points::RotateXZPlane(float angle)
{
    const float cosRes = cos(angle);
    const float sinRes = sin(angle);

    return Points(x*cosRes - z*sinRes, y, x*sinRes + z*cosRes);
}

Points Points::RotateYZPlane(float angle)
{
    const float cosRes = cos(angle);
    const float sinRes = sin(angle);

    return Points(x, y*cosRes - z*sinRes, y*sinRes + z*cosRes);
}

Points Points::RotateXYPlane(float angle)
{
    const float cosRes = cos(angle);
    const float sinRes = sin(angle);

    return Points(x*cosRes - y*sinRes, x*sinRes + y*cosRes, z);
}

Points Points::RotateZYXAxes(float AnglesXYZ[3])
{
    const float alphaX = AnglesXYZ[0];
    const float betaY = AnglesXYZ[1];
    const float gammaZ = AnglesXYZ[2];

    const float cA = cos(alphaX);
    const float cB = cos(betaY);
    const float cG = cos(gammaZ);

    const float sA = sin(alphaX);
    const float sB = sin(betaY);
    const float sG = sin(gammaZ);

    return Points(
        x*(cA*cB)             + y*(-sA*cB)            + z*sG,
        x*(cA*sB*sG + sA*cG)  + y*(-sA*sB*sG + cG*cA) + z*(-sG*cB),
        x*(-cA*cB*cG + sA*sG) + y*(sA*cB*cG + cA*sG)  + z*(cB*cG)
    );
}

float Points::getX() { return x; };
float Points::getY() { return y; };
float Points::getZ() { return z; };