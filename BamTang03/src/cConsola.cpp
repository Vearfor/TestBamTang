/*
 * cConsola.cpp
 *
 *  Created on: 07/12/2015
 *      Author: Enrique Rocafull Ortiz
 */

#include "cConsola.h"
#include "cConio.h"

//#include <conio.h>
//#include "../Acciones/cAccion.h"
//#include "../Devices/cConio.h"
//#include "../Util/cError.h"
//#include "../Util/cString.h"
//#include "../Files/cLog.h"
//#include "../Memoria/fMemoria.h"


//--------------------------------------------------------------------------
// Statics
//--------------------------------------------------------------------------
// Windows:
//          + Si no hay consola:
//              - cConsola::m_bActiva = false
//          + Si SI hay consola:
//              - cConsola::m_bActiva = true
//
// Console:
//          + Siempre HAY CONSOLA:
//              - cConsola::m_bActiva = true
//
//--------------------------------------------------------------------------
eModConsola cConsola::m_eModo = eMOD_CONSOLA;
bool        cConsola::m_bActiva = false;
bool        cConsola::m_bOpened = false;
bool        cConsola::m_bVisible = false;
char        cConsola::m_vcTitulo[] = "";
char        cConsola::m_vcTituloNormal[] = "";
HWND        cConsola::m_hWindow = NULL;
bool        cConsola::m_bAllocConsoleOriginal = false;
char        cConsola::m_vcNombreProceso[] = "";
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// Constructor & Destructor
//--------------------------------------------------------------------------
// No ibamos a utilizar ni constructor ni destructor, pero probamos a
// introducir uno vacio, y ya veremos que metemos en el 
// destructor ...
//--------------------------------------------------------------------------
cConsola::cConsola(void)
{
    // por ahora vacio ...
}

cConsola::~cConsola(void)
{
    // por ahora vacio ...
}
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// Resto metodos
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// Todos Statics
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// Devolvemod 1 si exito
// Devolvemos 0 si error al igual que el AllocConsole original
//--------------------------------------------------------------------------
int cConsola::AllocConsole(bool bOriginal)
{
    BOOL bRes = TRUE;

    if (m_eModo == eMOD_WINDOWS)
    {
        m_bAllocConsoleOriginal = bOriginal;

        bRes = ::AllocConsole();
        //AttachConsole(GetCurrentProcessId());
        //FILE *fp;
        //freopen_s(&fp, "CON", "w", stdout);
    }

    return (int) bRes;
}


//--------------------------------------------------------------------------
// Devolvemod 1 si exito
// Devolvemos 0 si error al igual que el FreeConsole original
//--------------------------------------------------------------------------
int cConsola::FreeConsole()
{
    BOOL bRes = TRUE;

    if (m_eModo == eMOD_WINDOWS)
    {
        bRes = ::FreeConsole();
    }

    return bRes;
}


int cConsola::kbhit(void)
{
    if (EsActiva() && m_bOpened)
        return cConio::Kbhit();

    // kbhit debe devolver algo si la consola no esta activa.
    return 1;
}

int cConsola::getch ( void )
{
    if (EsActiva() && m_bOpened)
        return cConio::Getch(GETCH_NO_ESPERA);

    return 0;
}

//-------------------------------------------------------------------------- 
// Espera tecla para continuar
//-------------------------------------------------------------------------- 
int cConsola::PulsaTecla(const char * pcFormat, ...)
{
    int iCar = 0;

    if (EsActiva())
    {
        if (mNoVacia(pcFormat))
        {
            va_list stList;

            va_start(stList, pcFormat);
            escribeLista(stList, pcFormat);
            va_end(stList);
        }

        // Otra manera
        iCar = cConio::Getch(GETCH_ESPERA);
        //iCar = cConio::Kbhit();
    }

    return iCar;
}


int cConsola::error(const char * pcFormat, ...)
{
    int iRes = 0;
    if (EsActiva() && pcFormat)
    {
        va_list stList;

        va_start(stList, pcFormat);
        //----------------------------------------------------------------------
        // Intentemos que la salida a pantalla sea la misma
        //----------------------------------------------------------------------
        word actualColor = cConio::GetColor();
        cConio::SetColor(cConio::GetErrorColor());
        //----------------------------------------------------------------------
        iRes = escribeLista(stList, pcFormat);
        //----------------------------------------------------------------------
        cConio::SetColor(actualColor);
        //----------------------------------------------------------------------
        va_end(stList);
    }
    return iRes;
}


int cConsola::escribe(const char * pcFormat, ...)
{
    int iRes = 0;
    if (EsActiva() && pcFormat)
    {
        va_list stList;

        va_start(stList, pcFormat);
        //----------------------------------------------------------------------
        // Intentemos que la salida a pantalla sea la misma
        //----------------------------------------------------------------------
        iRes = escribeLista(stList, pcFormat);
        //----------------------------------------------------------------------
        va_end(stList);
    }
    return iRes;
}


//int cConsola::escribeXY(int x, int y, const char * pcFormat, ...)
//{
//	int iRes = 0;
//	if (EsActiva() && pcFormat)
//	{
//		int newx = x;
//		int newy = y;
//
//		if (x == eMAXCONSOLA)
//		{
//			va_list stList;
//			va_start(stList, pcFormat);
//			int lon;
//
//			lon = cString::longitud(stList, pcFormat);
//			newx = cConio::MaxX(lon);
//		}
//
//		if (x == eMINCONSOLA)
//		{
//			newx = 0;
//		}
//
//		if (y == eMAXCONSOLA)
//		{
//			newy = cConio::MaxY(1);
//		}
//
//		if (y == eMINCONSOLA)
//		{
//			newy = 1;
//		}
//
//		if (!cConio::GotoXY(newx, newy))
//		{
//			va_list stList;
//			va_start(stList, pcFormat);
//			//----------------------------------------------------------------------
//			// Intentemos que la salida a pantalla sea la misma
//			//----------------------------------------------------------------------
//			iRes = escribeLista(stList, pcFormat);
//			//----------------------------------------------------------------------
//			va_end(stList);
//
//			cConio::SetLastXY();
//		}
//	}
//	return iRes;
//}


//int cConsola::escribeListaXY(int x, int y, va_list pstList, const char * pcFormat)
//{
//    int iRes = 0;
//    if (EsActiva() && pcFormat)
//    {
//        int newx = x;
//        int newy = y;
//
//        if (x == eMAXCONSOLA)
//        {
//            int lon;
//            lon = cString::longitud(pstList, pcFormat);
//            newx = cConio::MaxX(lon);
//        }
//
//        if (x == eMINCONSOLA)
//        {
//            newx = 0;
//        }
//
//        if (y == eMAXCONSOLA)
//        {
//            newy = cConio::MaxY(1);
//        }
//
//        if (y == eMINCONSOLA)
//        {
//            newy = 1;
//        }
//
//        if (!cConio::GotoXY(newx, newy))
//        {
//            //----------------------------------------------------------------------
//            // Intentemos que la salida a pantalla sea la misma
//            //----------------------------------------------------------------------
//            iRes = escribeLista(pstList, pcFormat);
//            //----------------------------------------------------------------------
//            cConio::SetLastXY();
//        }
//    }
//    return iRes;
//}


int cConsola::escribeLista(va_list pstList, const char * pcFormat)
{
    int iRes = 0;   // No hay cadena de salida en consola

    if (mNoVacia(pcFormat))
    {
        if (EsActiva())
        {
            ulong nused;

            Open();
            Mostrar();

            int lonFinal = longitud(pstList, pcFormat);
            if (lonFinal>0)
            {
                char vcMensaje[LON_BUFF+1];
                char * pcBuffer;
                if (lonFinal > LON_BUFF)
                {
                    pcBuffer = (char *) malloc(lonFinal + 1);
                }
                else
                {
                    mInicio(vcMensaje);
                    pcBuffer = vcMensaje;
                    lonFinal = LON_BUFF;
                }
                if (pcBuffer)
                {
                    lonFinal = vsnprintf_s(pcBuffer, lonFinal, lonFinal-1, pcFormat, pstList);
                    cConio::WriteConsole(pcBuffer, lonFinal, &nused);
                    if (lonFinal > LON_BUFF)
                    {
                        free(pcBuffer);
                        pcBuffer = nullptr;
                    }
                }
                iRes = lonFinal;
            }
        }
        else
        {
            iRes = vprintf(pcFormat, pstList);
        }
    }

    return iRes;
}


eModConsola cConsola::getModo(void)
{
    return m_eModo;
}


void cConsola::setModo(eModConsola eModo)
{
    m_eModo = eModo;
}


bool cConsola::EsActiva(void)
{
    return m_bActiva;
}

void cConsola::SetActiva(bool bActiva)
{
    m_bActiva = bActiva;

    // Solo la activo pero no la abro
    // Pero si la desactivo, si que la cierro.
    if (!m_bActiva)
    {
        Close();
    }
}


int cConsola::Open(void)
{
    if (EsActiva() && !m_bOpened)
    {
        if (m_eModo == eMOD_WINDOWS)
        {
            if (cConsola::AllocConsole())
            {
                //--------------------------------------------------------------
                mInicio(m_vcTitulo);
                GetConsoleTitle((LPWSTR)m_vcTitulo, sizeof(m_vcTitulo));
                m_hWindow = FindWindow(NULL, (LPWSTR)m_vcTitulo);
#ifdef _DEBUG
                setTituloConsola("%s : Debug", cConsola::getNombreProceso());
#else
                setTituloConsola("%s", getNombreProceso());
#endif
                mInicio(m_vcTituloNormal);
                GetConsoleTitle((LPWSTR)m_vcTituloNormal, sizeof(m_vcTituloNormal));
                m_bOpened = true;
                //--------------------------------------------------------------
                cConio::open();
            }
            else
            {
                fprintf(stderr, "cConsola::Open: AllocConsole\n");
            }
        }
        else
        {
            cConio::open();
            m_bOpened = true;
        }
    }
    return 0;
}


int cConsola::Close(void)
{
    if (EsActiva() && m_bOpened)
    {
        if (m_eModo == eMOD_WINDOWS)
        {
            // Termina();		// Termina el hilo del teclado, si es que estuviera activo
            // m_oLisLineas.LimpiaLista(true);
            Ocultar();
            if (cConsola::FreeConsole() == 0)
            {
                fprintf(stderr, "cConsola::Close: FreeConsole\n");
            }
            mInicio(m_vcTitulo);
            m_hWindow = NULL;
            m_bOpened = false;

            cConio::close();
        }
    }
    return 0;
}


int cConsola::Mostrar(void)
{
    int iRes = 0;   // Todo bien.
    if (EsActiva() && m_bOpened && !m_bVisible)
    {
        if (m_eModo == eMOD_WINDOWS)
        {
            // Mostrar cuando sea activa la consola
            ShowWindow(m_hWindow, SW_SHOW);
            m_bVisible = true;
        }
    }
    return iRes;
}


int cConsola::Ocultar(void)
{
    int iRes = 0;   // Todo bien.
    if (EsActiva() && m_bOpened && m_bVisible)
    {
        if (m_eModo == eMOD_WINDOWS)
        {
            // Ocultar cuando sea activa la consola
            ShowWindow(m_hWindow, SW_HIDE);
            m_bVisible = false;
        }
    }
    return iRes;
}


void cConsola::setNombreProceso(const char* pcNombreProceso)
{
    strcpy_s(m_vcNombreProceso, sizeof(m_vcNombreProceso), pcNombreProceso);
}


const char* cConsola::getNombreProceso(void)
{
    return m_vcNombreProceso;
}


//--------------------------------------------------------------------------
// Limpia la pantalla de la consola
//--------------------------------------------------------------------------
// iTraza = 0
//                          limpia pantalla
//--------------------------------------------------------------------------
// iTraza > 0
// Coje el nivel de traza del Log = 2 (por defecto)
//
// - Si iTraza es: 1 o 2
//
//                          limpia pantalla
//
// - Si iTraza es > 2 : 3, 4, 5, ... etc ...
//
//                          NO limpia pantalla
//
//--------------------------------------------------------------------------
int cConsola::cls(int iTraza)
{
    return cConio::Cls();
}


//--------------------------------------------------------------------------
// Establece el titulo de la Consola
//--------------------------------------------------------------------------
int cConsola::setTituloConsola(const char * pcFormat, ...)
{
    int iRes = 0;
    if (EsActiva() && pcFormat)
    {
        char vcTitulo[LON_BUFF];
        va_list stList;
        va_start(stList, pcFormat);
        vsnprintf_s(vcTitulo, sizeof(vcTitulo), sizeof(vcTitulo)-1, pcFormat, stList);
        va_end(stList);
        SetConsoleTitle((LPCWSTR)vcTitulo);
    }
    return iRes;
}


int cConsola::resetTituloConsola(const char * pcTitulo)
{
    if (pcTitulo)
    {
        SetConsoleTitle((LPCWSTR)pcTitulo);
    }
    else
    {
        SetConsoleTitle((LPCWSTR)m_vcTituloNormal);
    }

    return 0;
}


const char * cConsola::getTituloNormal(void)
{
    return m_vcTituloNormal;
}


int cConsola::longitud(va_list pstList, const char* pcFormat)
{
    int lonFinal = 0;
    if (mNoVacia(pcFormat))
    {
        lonFinal = vsnprintf(NULL, 0, pcFormat, pstList);
    }
    return lonFinal;
}



//--------------------------------------------------------------------------
// Fin de cConsola.cpp
//--------------------------------------------------------------------------

