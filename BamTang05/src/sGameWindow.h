/*------------------------------------------------------------------------*\
|* sGameWindow.h
\*------------------------------------------------------------------------*/

#pragma once
//--------------------------------------------------------------------------
// Include
//--------------------------------------------------------------------------
#include "swat/sWindow.h"
//--------------------------------------------------------------------------


/*------------------------------------------------------------------------*/
class cTeclado;
/*------------------------------------------------------------------------*/
struct sGameWindow
    : public sWindow
{
    sGameWindow();
    ~sGameWindow();

    cTeclado* m_pTeclado;

protected:

    //----------------------------------------------------------------------
    virtual long commonWindowProc(HWND hwnd, uint uiMsg, WPARAM wparam, LPARAM lparam) override;
    virtual int initWindow() override;
    //----------------------------------------------------------------------
    //virtual long OnKeyUp(long lTecla) override;
    //----------------------------------------------------------------------
};
/*------------------------------------------------------------------------*/


/*------------------------------------------------------------------------*\
|* Fin de sGameWindow.h
\*------------------------------------------------------------------------*/
