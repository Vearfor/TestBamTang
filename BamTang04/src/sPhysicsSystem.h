/*------------------------------------------------------------------------*\
|* sPhysicsSystem.h
|*------------------------------------------------------------------------*
|*
|* a(t) = A
|* v(t) = Vo + At
|* x(t) = Xo + VoT +(1/2)At2
|*
\*------------------------------------------------------------------------*/

#pragma once
//--------------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

/*------------------------------------------------------------------------*/
struct sGame;
/*------------------------------------------------------------------------*/
struct sPhysicsSystem
{
    sPhysicsSystem();
    ~sPhysicsSystem();

    int update(sGame*, float fDeltaTime);
};
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*\
|* Fin de sPhysicsSystem.h
\*------------------------------------------------------------------------*/
