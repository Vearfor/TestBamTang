/*------------------------------------------------------------------------*\
|* sGlobal.h
\*------------------------------------------------------------------------*/

#pragma once
//--------------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------------
#include <tool/nComun.h>
//--------------------------------------------------------------------------

#pragma region Titulo
//--------------------------------------------------------------------------
// El Titulo de la Ventana
//--------------------------------------------------------------------------
#ifdef _X64
#define PLATFORM " [64"
#else
#define PLATFORM " [32"
#endif

#ifdef _DEBUG
#define CONFIG " Debug]"
#else
#define CONFIG " Release]"
#endif

#define TITLE PLATFORM CONFIG
//--------------------------------------------------------------------------
#pragma endregion


/*------------------------------------------------------------------------*/
struct sGlobal
{
    static int m_iDim;
    static int m_iWidth;
    static int m_iHeight;
    static char vcNombrePrograma[LON_BUFF / 8];
    static float m_fIntervaloDemo;
};
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*\
|* Fin de sGlobal.h
\*------------------------------------------------------------------------*/
