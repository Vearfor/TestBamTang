/*------------------------------------------------------------------------*\
|* sGameWindow.h
\*------------------------------------------------------------------------*/

#pragma once
/*------------------------------------------------------------------------*\
|* Includes
\*------------------------------------------------------------------------*/
#include <swat/windows/sWindow.h>
/*------------------------------------------------------------------------*/


/*------------------------------------------------------------------------*\
|* struct sGameWindow
\*------------------------------------------------------------------------*/
class cTeclado;
class cRaton;
/*------------------------------------------------------------------------*/
struct sGameWindow
    : public sWindow
{
    sGameWindow(int width, int height);
    virtual ~sGameWindow();

    cTeclado* m_pTeclado{ nullptr };
    cRaton* m_pRaton{ nullptr };

protected:

    //----------------------------------------------------------------------
    virtual long commonWindowProc(HWND hwnd, uint uiMsg, WPARAM wparam, LPARAM lparam) override;
    virtual int initWindow() override;
    //----------------------------------------------------------------------
    virtual long OnSize(int newWidth, int newHeight) override;
    //----------------------------------------------------------------------
};
/*------------------------------------------------------------------------*/


/*------------------------------------------------------------------------*\
|* Fin de sGameWindow.h
\*------------------------------------------------------------------------*/
