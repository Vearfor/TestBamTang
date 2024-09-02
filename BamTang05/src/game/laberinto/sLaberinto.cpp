/*========================================================================*\
|* sLaberinto.cpp
\*========================================================================*/


#include "sLaberinto.h"
#include "../../tool/cLog.h"
#include "../../tool/nComun.h"
#include "../../swat/sRenderObject.h"


sLaberinto::sLaberinto(const char* pcSoy)
    : m_quienSoy(pcSoy)
    , m_size(kMin + 2)
    , m_matriz(nullptr)
    , m_motor{}
{
    // Iniciamos el motor aleatorio:
    m_motor.inicia();
}

sLaberinto::~sLaberinto()
{
    delete m_pObjCamara;

    delete m_pFin;
    delete m_pInicio;
    delete m_pMuro;
    delete m_pSuelo;

    delete m_pPunto;

    destruyeMatriz(m_matriz, m_size);
}


int sLaberinto::creaMatriz(int size)
{
    m_size = size;
    char car = kMuro;
    // primero la matriz que apunta al array de filas
    m_matriz = new char* [size];
    miNulo(m_matriz);

    // Y ahora con un for completamos las columnas:
    for (int fila = 0; fila < size; fila++)
    {
        // Creamos las columnas de cada fila:
        m_matriz[fila] = new char[size];
        miNulo(m_matriz[fila]);
        // tengo que multiplicar por sizeof int, ya que son caracteres, no ints
        std::memset(m_matriz[fila], car, size * sizeof(char));
    }

    return 0;
}

void sLaberinto::destruyeMatriz(char ** matriz, int size)
{
    if (matriz)
    {
        for (int fila = 0; fila < size; fila++)
        {
            if (matriz[fila])
            {
                delete[] matriz[fila];
                matriz[fila] = nullptr;
            }
        }
        delete[] matriz;
        matriz = nullptr;
    }
}


int sLaberinto::createMaze2D(int size)
{
    if (creaMatriz(size))
    {
        cLog::error(" sLaberinto::createMaze2D Error: creaMatriz: en la creaci�n de la matriz del laberinto");
        return -1;
    }

    // Creo los objetos antes que el laberinto, para asignar la posicion de m_pFin:
    m_pSuelo = new sRenderObject();
    m_pMuro = new sRenderObject();
    m_pInicio = new sRenderObject();
    m_pFin = new sRenderObject();

    m_pObjCamara = new sRenderObject();

    if (creaLaberinto())
    {
        cLog::error(" sLaberinto::createMaze2D Error: creaLaberinto: en la construccion del laberinto");
        return -1;
    }

    // Y el render object no debe pertenecer a la vista:
    m_pPunto = new sRenderObject();

    // No es el sitio: lo reorganizaremos de otra manera, pero metemos las condiciones del Laberinto aqui para que el 'punto'
    // sepa las condiciones del laberinto.
    m_pPunto->m_fila = 1;
    m_pPunto->m_columna = 1;

    return 0;
}


char** sLaberinto::getCopiaMatriz(char** src_matriz, int size)
{
    char** src_copia = new char* [size];
    for (int i = 0; i < size; i++)
    {
        src_copia[i] = new char[size];
        for (int j = 0; j < size; j++)
        {
            src_copia[i][j] = src_matriz[i][j];
        }
    }
    return src_copia;
}


int sLaberinto::arriba()
{
    if (m_pPunto)
    {
        int fila = m_pPunto->m_fila;
        int columna = m_pPunto->m_columna;
        // char valor = m_matriz[fila][columna - 1];
        char valor = m_matriz[fila - 1][columna];
        if (valor == kVacio || valor == kFin || valor == kInicio)
        {
            //m_pPunto->m_columna--;
            m_pPunto->m_fila--;
        }
        //cLog::print(" arriba:     [ %2d, %2d]\n", m_pPunto->m_fila, m_pPunto->m_columna);
        checkHemosLlegado();
    }
    return 0;
}


int sLaberinto::derecha()
{
    if (m_pPunto)
    {
        int fila = m_pPunto->m_fila;
        int columna = m_pPunto->m_columna;
        // char valor = m_matriz[fila + 1][columna];
        char valor = m_matriz[fila][columna + 1];
        if (valor == kVacio || valor == kFin || valor == kInicio)
        {
            // m_pPunto->m_fila++;
            m_pPunto->m_columna++;
        }
        //cLog::print(" derecha:    [ %2d, %2d]\n", m_pPunto->m_fila, m_pPunto->m_columna);
        checkHemosLlegado();
    }
    return 0;
}


int sLaberinto::abajo()
{
    if (m_pPunto)
    {
        int fila = m_pPunto->m_fila;
        int columna = m_pPunto->m_columna;
        // char valor = m_matriz[fila][columna + 1];
        char valor = m_matriz[fila + 1][columna];
        if (valor == kVacio || valor == kFin || valor == kInicio)
        {
            // m_pPunto->m_columna++;
            m_pPunto->m_fila++;
        }
        //cLog::print(" abajo:      [ %2d, %2d]\n", m_pPunto->m_fila, m_pPunto->m_columna);
        checkHemosLlegado();
    }
    return 0;
}


int sLaberinto::izquierda()
{
    if (m_pPunto)
    {
        int fila = m_pPunto->m_fila;
        int columna = m_pPunto->m_columna;
        // char valor = m_matriz[fila - 1][columna];
        char valor = m_matriz[fila][columna - 1];
        if (valor == kVacio || valor == kFin || valor == kInicio)
        {
            // m_pPunto->m_fila--;
            m_pPunto->m_columna--;
        }
        //cLog::print(" izquierda:  [ %2d, %2d]\n", m_pPunto->m_fila, m_pPunto->m_columna);
        checkHemosLlegado();
    }
    return 0;
}


void sLaberinto::checkHemosLlegado()
{
    if (!m_bEstaEnElFin)
    {
        m_bEstaEnElFin = (m_pFin->m_fila == m_pPunto->m_fila && m_pFin->m_columna == m_pPunto->m_columna);
    }
}



/*========================================================================*\
|* Fin de sLaberinto.h
\*========================================================================*/

