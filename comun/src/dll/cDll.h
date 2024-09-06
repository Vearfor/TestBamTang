/*========================================================================*\
|* cDll.h
\*========================================================================*/


#pragma once
//--------------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------------
// #include "../Memoria/fMemoria.h"
//--------------------------------------------------------------------------
#include "nExport.h"
#include <Windows.h>
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// Class
//--------------------------------------------------------------------------
class _mExport cDll
{
	HINSTANCE	m_hInstancia;
	int			m_iIdDll;

	static	int			m_iNumInstancias;
	static	int			m_iInstanciaDll;

public:

	cDll(void);
	virtual ~cDll(void);

	virtual	int		Inicio_Dll	( HMODULE hModule );
	virtual	int		Salida_Dll	( void );

    static  void    PreInicio   ( void );
    static  void    PostFin     ( const char * );
};
//--------------------------------------------------------------------------


/*========================================================================*\
|* Fin de cDll.h
\*========================================================================*/
