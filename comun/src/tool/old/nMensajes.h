#pragma once
//--------------------------------------------------------------------------
// nMensajes.h
//--------------------------------------------------------------------------
// Mensajes que vamos a establecer entre los distintos hilos de nuestras
// aplicaciones ...
//--------------------------------------------------------------------------


#ifndef NMENSAJES_H_
#define NMENSAJES_H_
//--------------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------------
#include "nComun.h"
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// enumerados
//--------------------------------------------------------------------------
enum class eCommonMensajes : int
{
    //----------------------------------------------------------------------
    // Hasta nueva orden estos son los mensajes mas basicos
    //----------------------------------------------------------------------
    eTM_FIN_PROGRAMA = AM_INICIO_MENSAJES,      // Cuidado, Host empieza con lo mismo sus, supuestos mensajes.
    eTM_ERROR_HILO,                             // Se ha producido un error, exception, en un hilo.
    eTM_EJECUTA_ACCION,                         // Ejecuta accion
    //----------------------------------------------------------------------
    eTM_MENSAJES_USUARIO,
    //----------------------------------------------------------------------
    // A partir del valor de eTM_MENSAJES_USUARIO se definiran el resto
    //----------------------------------------------------------------------
};
//--------------------------------------------------------------------------
#endif /* NMENSAJES_H_ */


//--------------------------------------------------------------------------
// Fin de nMensajes.h
//--------------------------------------------------------------------------
