/*------------------------------------------------------------------------*\
|* sCollisionSystem.h
\*------------------------------------------------------------------------*/

#pragma once
//--------------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

/*------------------------------------------------------------------------*/
struct sGame;
struct sBall;
/*------------------------------------------------------------------------*/
struct sCollisionSystem
{
    sCollisionSystem();
    ~sCollisionSystem();

    int update(sGame*, float fDeltaTime);
    bool checkCollision(float fDeltaTime, sBall* bola1, sBall* bola2);
    void collision(sBall* pBola1, sBall* pBola2);
    void modificoBola(sBall* pBall, float oldVel, float fdir);

private:

    int getWidth();
    int getHeight();
};
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*\
|* Fin de sCollisionSystem.h
\*------------------------------------------------------------------------*/
