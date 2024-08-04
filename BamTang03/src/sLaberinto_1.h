/*========================================================================*\
|* sLaberinto_1.h
\*========================================================================*/

#pragma once
//--------------------------------------------------------------------------
// Include
//--------------------------------------------------------------------------
#include "sLaberinto.h"
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Constantes
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// Valores definidos para marcar:
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Enumerados
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// Struct
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

//
// Una estructura en c++ es simplemente una clase con sus elementos publicos
// As� que meteremos en la parte privada aquello que no queremos que se
// tenga acceso.
//
struct sLaberinto_1
    : public sLaberinto
{
    sLaberinto_1();
    ~sLaberinto_1();

    virtual int creaLaberinto() override;
    virtual int calculaCaminoMasLargo() override;

private:

    void removeWall(sCoord cur, int ancho_celda, int alto_celda);
    void ramdomize(int* array, int n);
    bool isValidPosition(sCoord cur, int alto, int ancho);
    void copyRow(int row_src, int row_dest, int ancho);
    void copyCol(int col_src, int col_dest, int alto);
    void copyValidRowsAndCols(int alto, int ancho);
};


/*========================================================================*\
|* Fin de sLaberinto_1.h
\*========================================================================*/
