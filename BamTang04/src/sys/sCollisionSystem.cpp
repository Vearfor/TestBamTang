/*------------------------------------------------------------------------*\
|* sCollisionSystem.cpp
\*------------------------------------------------------------------------*/

#include "sCollisionSystem.h"
#include "../sGame.h"
#include "../sBall.h"
#include "../sGlobal.h"
#include "sRenderSystem.h"
#include <tool/sMath.h>
#include <vector>


/*------------------------------------------------------------------------*\
|* Statics
\*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/


/*------------------------------------------------------------------------*/
sCollisionSystem::sCollisionSystem()
{
}

sCollisionSystem::~sCollisionSystem()
{
    cLog::print(" Destructor sCollisionSystem\n");
}
/*------------------------------------------------------------------------*/


int sCollisionSystem::update(sGame* pGame, float fDeltaTime)
{
    auto& vecBolas = pGame->getVecBolas();
    if (!pGame->hayPausa())
    {
        if (vecBolas.size() > 0)
        {
            for (auto* pBall : vecBolas)
            {
                pBall->checkLimites(fDeltaTime, getWidth(), getHeight());
                // Los flags los reseteamos para la colision entre Bolas:
                pBall->m_check = false;
                pBall->m_estaColisionando = false;
            }

            // Al menos 2 bolas
            if (vecBolas.size() > 1)
            {
                // Bola contra Bola:
                for (int i = 0; i < vecBolas.size(); i++)
                {
                    sBall* pBall1 = vecBolas[i];
                    if (!pBall1->m_check && !sMath::isZero(pBall1->m_vecVelocidad))
                    {
                        //--------------------------------------------------
                        for (int j = 0; j < vecBolas.size(); j++)
                        {
                            if (i == j)
                                continue;

                            sBall* pBall2 = vecBolas[j];
                            if (!pBall2->m_check)
                            {
                                if (checkCollision(fDeltaTime, pBall1, pBall2))
                                {
                                    collision(pBall1, pBall2);
                                    float fVel1 = sMath::modulo(pBall1->m_vecVelocidad);
                                    float fVel2 = sMath::modulo(pBall2->m_vecVelocidad);
                                    cLog::print(" Vel Bola %6.3f  ---  Vel Bola %6.3f\n",
                                        fVel1,
                                        fVel2);
                                    break;
                                }
                            }
                        }
                        //--------------------------------------------------
                        pBall1->m_check = true;
                    }
                }
            }
        }
    }
    return 0;
}


bool sCollisionSystem::checkCollision(float fDeltaTime, sBall* bola1, sBall* bola2)
{
    // if (!bola1->m_check && !bola2->m_check)
    {
        // Cuando el tiempo es 0, el inc es 0
        glm::vec2 inc1 = (bola1->m_vecVelocidad * fDeltaTime);
        glm::vec2 inc2 = (bola2->m_vecVelocidad * fDeltaTime);

        // Y si el inc es 0, es la comprobacion en la posicion actual
        glm::vec2 pos1 = bola1->m_posicion + inc1;
        glm::vec2 pos2 = bola2->m_posicion + inc2;

        glm::vec2 diff = pos1 - pos2;
        float dist = sMath::modulo(diff);
        float f2radio = bola1->m_radio + bola2->m_radio;
        if (dist < f2radio)
        {
            bola1->m_estaColisionando = true;
            bola1->m_estaColisionando = true;

            cLog::print(" Collision: Bola %3ld -- Bola %3ld     Delta: %6.4f\n",
                bola1->m_bolaId,
                bola2->m_bolaId,
                fDeltaTime);
            return true;
        }
    }

    return false;
}


void sCollisionSystem::collision(sBall* pBola1, sBall* pBola2)
{
    float oldVel1 = sMath::modulo(pBola1->m_vecVelocidad);
    float oldVel2 = sMath::modulo(pBola2->m_vecVelocidad);
    // Para repartir sumo y reparto:
    float suma = oldVel1 + oldVel2;

    if (suma > 0.0f)
    {
        float fVel, xVel, yVel;

        glm::vec2 vdiff = (pBola1->m_posicion) - (pBola2->m_posicion);

        float fdir = rad2deg(atan2f(vdiff.y, vdiff.x));

        pBola1->m_fdir = fdir;
        pBola2->m_fdir = ((fdir + 180.0f) > 360.0f) ? (fdir + 180.0f) - 360.0f : fdir + 180.0f;

        // Si laguna es negativa, la mostramos siempre como positiva:
        pBola1->corrigeDir();
        pBola2->corrigeDir();

        // Estas son las direcciones perpendiculares al choque, �no habria que tener en cuenta las direcciones anteriores?
        // Deber�a ser, y seguro que es mucho mas simple
        if (oldVel1 > oldVel2)
        {
            float quito = oldVel1 * 0.1f;
            oldVel1 = oldVel1 - quito;
            oldVel2 = oldVel2 + quito;
        }
        else
        {
            float quito = oldVel2 * 0.1f;
            oldVel2 = oldVel2 - quito;
            oldVel1 = oldVel1 + quito;
        }

        // La velocidad: la anterior repartida aplicando la reduccion de elasticidad:
        fVel = oldVel1 * sGlobal::m_fElasticidad;
        xVel = fVel * cos(deg2rad(pBola1->m_fdir));
        yVel = fVel * sin(deg2rad(pBola1->m_fdir));

        pBola1->m_vecVelocidad = glm::vec2{ xVel, yVel };

        // La velocidad: la anterior repartida aplicando la reduccion de elasticidad:
        fVel = oldVel2 * sGlobal::m_fElasticidad;
        xVel = fVel * cos(deg2rad(pBola2->m_fdir));
        yVel = fVel * sin(deg2rad(pBola2->m_fdir));

        pBola2->m_vecVelocidad = glm::vec2{ xVel, yVel };
    }
}


/*------------------------------------------------------------------------*\
|* Hacemos el uso de la instancia sGame:
\*------------------------------------------------------------------------*/
int sCollisionSystem::getWidth()
{
    return sGame::instancia()->getRender()->getWidth();
}


int sCollisionSystem::getHeight()
{
    return sGame::instancia()->getRender()->getHeight();
}
/*------------------------------------------------------------------------*/


/*------------------------------------------------------------------------*\
|* Fin de sCollisionSystem.cpp
\*------------------------------------------------------------------------*/
