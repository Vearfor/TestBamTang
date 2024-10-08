//--------------------------------------------------------------------------
// nCommonKeys.h
//--------------------------------------------------------------------------


#pragma once
//--------------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------------
#include "../../tool/nComun.h"
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// Enumerados
//--------------------------------------------------------------------------
enum eTeclado
{
    //----------------------------------------------------------------------
    eBACK = VK_BACK,
    eTAB = VK_TAB,
    eRETURN = VK_RETURN,
    //----------------------------------------------------------------------
    eRTPAG = VK_PRIOR,
    eAVPAG = VK_NEXT,
    eESC = VK_ESCAPE,
    eSPACE = VK_SPACE,
    //----------------------------------------------------------------------
    eADD = VK_ADD,
    eSUB = VK_SUBTRACT,
    //----------------------------------------------------------------------
    eIZQD = VK_LEFT,   // 37,
    eARRB = VK_UP,   // 38,
    eDERCH = VK_RIGHT,   // 39,
    eABAJO = VK_DOWN,
    //----------------------------------------------------------------------
    eINSERT = VK_INSERT,
    eDELETE = VK_DELETE,
    eINICIO = VK_HOME,
    eFIN = VK_END,
    //----------------------------------------------------------------------
    // Me da el mismo valor que eCTRL = 17, y no 18.
    eALTGR = VK_MENU,
    eCTRL = VK_CONTROL,
    eLCTRL = VK_LCONTROL,
    eRCTRL = VK_RCONTROL,
    eLSHIFT = VK_LSHIFT,
    eRSHIFT = VK_RSHIFT,
    eLALT = VK_LMENU,
    eRALT = VK_RMENU,
    //----------------------------------------------------------------------
    eF1 = VK_F1,
    eF2 = VK_F2,
    eF3 = VK_F3,
    eF4 = VK_F4,
    eF5 = VK_F5,
    eF6 = VK_F6,
    eF7 = VK_F7,
    eF8 = VK_F8,
    eF9 = VK_F9,
    eF10 = VK_F10,
    eF11 = VK_F11,
    eF12 = VK_F12,
    //----------------------------------------------------------------------
};
//--------------------------------------------------------------------------
enum eExtendido
{
    //------------------------------------------------------------------
    eACTIVA_EXT = 224,  // Por ahora es lo que activa el Extendido
    //------------------------------------------------------------------
    eIZQD_EXT = 75,   // K , en el array de un teclado: 37
    eARRB_EXT = 72,   // H , array teclado: 38,
    eDERCH_EXT = 77,   // M , array teclado: 39,
    eABAJO_EXT = 80,   // P , en el array de un teclado: 40
    //------------------------------------------------------------------
};
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// Fin de cCommonKeys.h
//--------------------------------------------------------------------------
