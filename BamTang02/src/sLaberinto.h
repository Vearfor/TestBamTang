/*========================================================================*\
|* sLaberinto.h
\*========================================================================*/

#pragma once
//--------------------------------------------------------------------------
// Include
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Constantes
//--------------------------------------------------------------------------
const int kMin = 3;
const int kLim = 31;
//--------------------------------------------------------------------------


struct sLaberinto
{
    sLaberinto(size_t size);

    size_t m_size{ kMin + 2 };
};
/*========================================================================*\
|* Fin de sLaberinto.h
\*========================================================================*/
