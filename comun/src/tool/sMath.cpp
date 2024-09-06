/*========================================================================*\
|* sMath.cpp
|*
|*  Created on: 31/08/2024
|*      Author: Enrique Rocafull Ortiz
|*
|* Compendio de funciones matematicas utilies desde 2010.
|*
\*========================================================================*/


#include "sMath.h"


//--------------------------------------------------------------------------
// Nos fabricamos una funcion normalize debido a que hay muchos valores
// que son ya muy peque�os y deben tomarse como cero
//--------------------------------------------------------------------------
cstatic glm::vec3 sMath::normalize(glm::vec3 vector)
{
    glm::vec3 normal = glm::normalize(vector);

    normal = setZero(normal);

    return normal;
}
//--------------------------------------------------------------------------
cstatic float sMath::getFactorReduccion(float fFactorDecr, float fDeltaTime)
{
    float fDelta = fDeltaTime;
    float fDecExp = fFactorDecr;

    mSetZero(fDelta);
    float fFactor = exp(-fDecExp * fDelta);
    return fFactor;
}


//--------------------------------------------------------------------------
cstatic float* sMath::getMatriz(glm::mat4 mat)
{
    return (float*) &mat;
}


//--------------------------------------------------------------------------
// Si estamos muy cerca de cero, pues zero:
//--------------------------------------------------------------------------
cstatic glm::vec2 sMath::setZero(glm::vec2 vec)
{
    glm::vec2 vZero = vec;

    mSetZero(vZero.x);
    mSetZero(vZero.y);

    return vZero;
}


cstatic glm::vec3 sMath::setZero(glm::vec3 vec)
{
    glm::vec3 vZero = vec;

    mSetZero(vZero.x);
    mSetZero(vZero.y);
    mSetZero(vZero.z);

    return vZero;
}


cstatic glm::vec4 sMath::setZero(glm::vec4 vec)
{
    glm::vec4 vZero = vec;

    mSetZero(vZero.x);
    mSetZero(vZero.y);
    mSetZero(vZero.z);
    mSetZero(vZero.w);

    return vZero;
}


//--------------------------------------------------------------------------
cstatic bool sMath::isZero(glm::vec2 vec)
{
    return mEsZero(vec.x) && mEsZero(vec.y);
}


//--------------------------------------------------------------------------
cstatic bool sMath::isZero(glm::vec3 vec)
{
    return mEsZero(vec.x) && mEsZero(vec.y) && mEsZero(vec.z);
}


//--------------------------------------------------------------------------
cstatic bool sMath::isZero(glm::vec4 vec)
{
    return mEsZero(vec.x) && mEsZero(vec.y) && mEsZero(vec.z) && mEsZero(vec.w);
}


//--------------------------------------------------------------------------
cstatic float sMath::modulo(glm::vec2 vec)
{
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}


//--------------------------------------------------------------------------
cstatic float sMath::modulo(glm::vec3 vec)
{
    return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}


//--------------------------------------------------------------------------
cstatic float sMath::modulo(glm::vec4 vec)
{
    return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}


//--------------------------------------------------------------------------
cstatic float sMath::getAngulo(glm::vec2 vector)
{
    // No se si sera esta, o la perpendicular, vamos probando:
    float fdir = rad2deg(atan2f(vector.y, vector.x));

    return fdir;
}


/*========================================================================*\
|* Fin de sMath.cpp
\*========================================================================*/
