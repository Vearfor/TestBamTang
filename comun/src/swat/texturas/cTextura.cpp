/*========================================================================*\
|* cTextura.cpp
\*========================================================================*/


#include "cTextura.h"
#include "../shaders/cShader.h"
#include "../../tool/cTool.h"
#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>
#include <iostream>


//--------------------------------------------------------------------------
// Constructor & Destructor
//--------------------------------------------------------------------------
cTextura::cTextura(std::string nombre, GLuint idTex, textureType type)
    : m_nombreTextura(nombre)
    , m_iTex(idTex)
    , m_mytype(type)
    , m_material(nullptr)
{
}


cTextura::~cTextura()
{
    // No podemos hacer deleteTexturas en el destructor, si vamos a utilizar
    // copias en las listas de texturas:
    // 
    // Al final si:
    deleteTextura();
}
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// Resto de Funciones
//--------------------------------------------------------------------------
void cTextura::deleteTextura()
{
    if (m_iTex > 0)
    {
        glDeleteTextures(1, &m_iTex);
    }
}


void cTextura::setTextura(std::string nombre, GLuint idTex, textureType type)
{
    m_nombreTextura = nombre;
    m_iTex = idTex;
    m_mytype = type;
}


cstatic sResultText cTextura::genTexturaSimple(int width, int height, int componentes, unsigned char* image, bool generateMipMaps)
{
    sResultText sTex;
    GLuint iTex;

    glGenTextures(1, &iTex);
    glBindTexture(GL_TEXTURE_2D, iTex);
    // Wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    if (generateMipMaps)
        glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    sTex._iTex = iTex;
    sTex._bytesPorPixelTextura = componentes;
    sTex._widthTextura = width;
    sTex._heightTextura = height;
    sTex._sizeTextura = sTex._widthTextura * sTex._heightTextura * sTex._bytesPorPixelTextura;

    return sTex;
}


cstatic sResultText cTextura::genTexturaMap(int width, int height, int componentes, unsigned char* image, bool generateMipMaps)
{
    sResultText sTex;
    GLuint iTex;

    glGenTextures(1, &iTex);
    glBindTexture(GL_TEXTURE_2D, iTex);
    // Wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    if (generateMipMaps)
        glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    sTex._iTex = iTex;
    sTex._bytesPorPixelTextura = 3;
    sTex._widthTextura = width;
    sTex._heightTextura = height;
    sTex._sizeTextura = sTex._widthTextura * sTex._heightTextura * sTex._bytesPorPixelTextura;

    return sTex;
}


cstatic sResultText cTextura::genTexturaModel(int width, int height, int componentes, unsigned char* image, bool generateMipMaps)
{
    sResultText sTex;
    GLuint iTex;

    glGenTextures(1, &iTex);
    glBindTexture(GL_TEXTURE_2D, iTex);
    // Wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D,      // Target
        0,                  // Level
        GL_RGB,             // internal format
        width, height,
        0,                  // border: width of a border 
        GL_RGB,             // output format :
        GL_UNSIGNED_BYTE,   // type          : como estan dentro del buffer, unsigned byte y RGB.
        image               // image data: the raw image
    );
    if (generateMipMaps)
        glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    sTex._iTex = iTex;
    sTex._bytesPorPixelTextura = 3;
    sTex._widthTextura = width;
    sTex._heightTextura = height;
    sTex._sizeTextura = sTex._widthTextura * sTex._heightTextura * sTex._bytesPorPixelTextura;

    return sTex;
}


int cTextura::genCubeMap(std::vector<const GLchar*> faces)
{
    struct stImagen
    {
        int width;
        int height;
        int componentes;
        unsigned char* image;
    };
    int iRes = 0;
    //int forceCanals = SOIL_LOAD_RGB;
    int forceCanals = STBI_rgb;
    std::vector<struct stImagen> imagenes;

    GLuint i;
    for (i = 0; i < faces.size() && !iRes; i++)
    {
        struct stImagen imagen;
        imagen.image = stbi_load(faces[i], &imagen.width, &imagen.height, &imagen.componentes, forceCanals);
        if (!imagen.image)
        {
            iRes = -1;
            std::cerr << "\nError::genCubeMap: stbi_load: [" << faces[i] << "]" << std::endl;
        }
        else
        {
            imagenes.push_back(imagen);
        }
    }

    if (!iRes)
    {
        if (i != 6)
        {
            iRes = -1;
            std::cerr << "\nError::genCubeMap: El vecor de texturas debe ser de 6 para un Cube Map." << std::endl;
        }
        else
        {
            glGenTextures(1, &m_iTex);
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_iTex);

            // Wrap
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            // Filter
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            for (i = 0; i < imagenes.size(); i++)
            {
                glTexImage2D(
                    GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                    0, GL_RGB, 
                    imagenes[i].width, imagenes[i].height,
                    0, GL_RGB,
                    GL_UNSIGNED_BYTE, 
                    imagenes[i].image);
                stbi_image_free(imagenes[i].image);
            }
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

            m_mytype = textureType::TexCube;
        }

        imagenes.clear();
    }

    return iRes;
}


cstatic sResultText cTextura::cargaTextura(textureType type, const char* pcFichero, const char* directory, bool generateMipMaps)
{
    char texFile[LON_BUFF];

    mInicio(texFile);
    if (directory)
    {
        sprintf_s(texFile, sizeof(texFile), "%s/%s", directory, pcFichero);
    }
    else
    {
        strcpy_s(texFile, sizeof(texFile), pcFichero);
    }

    sResultText sTex;

    sTex._iTex = -1;
    int forceCanals;
    switch (type)
    {
        case textureType::TexSimple:
            forceCanals = (int)STBI_rgb_alpha;      // RGBA
            break;
        case textureType::TexMap:
        case textureType::TexModel:
            forceCanals = (int)STBI_rgb;            // RGB
            break;
        case textureType::TexCube:
            std::cerr << "\nError::cargaTextura:: El TexCube se hace con cTextura::genCubeMap" << std::endl;
            return sTex;
        default:
            std::cerr << "\nError::cargaTextura:: unknown type" << std::endl;
            return sTex;
    }

    int width, height, componentes;
    unsigned char* image = stbi_load(texFile, &width, &height, &componentes, forceCanals);

    //invertImage(image, width, height, componentes);

    if (image)
    {
        switch (type)
        {
            case textureType::TexSimple:
                sTex = genTexturaSimple(width, height, componentes, image);
                break;
            case textureType::TexMap:
                sTex = genTexturaMap(width, height, componentes, image);
                break;
            case textureType::TexModel:
                sTex = genTexturaModel(width, height, componentes, image);
                break;
            default:
                std::cerr << "\nError::cargaTextura:: unknown type" << std::endl;
                break;
        }
    }
    else
    {
        std::cerr << "Error::cargaTextura: stbi_load: [" << pcFichero << "]" << std::endl;
    }

    return sTex;
}


cstatic int cTextura::invertImage(unsigned char* imageData, int width, int height, int components)
{
    //int widthInBytes = width * components;      // 4
    int widthInBytes = width * 4;      // 4
    unsigned char* top = nullptr;
    unsigned char* bottom = nullptr;
    unsigned char tmp = 0;
    int halfHeight = height / 2;
    for (int iRow = 0; iRow < halfHeight; iRow++)
    {
        top = imageData + (iRow * widthInBytes);
        bottom = imageData + ((height - iRow - 1) * widthInBytes);
        for (int iCol = 0; iCol < widthInBytes; iCol++)
        {
            tmp = *top;
            *top = *bottom;
            *bottom = tmp;
            top++;
            bottom++;
        }
    }

    return 0;
}


//--------------------------------------------------------------------------
// Codigo que no utiliza el uniform sampler ???
//--------------------------------------------------------------------------
// texture.bind(0);                          // Caja madera
// Este codigo:
// - hace que la textura de la caja de madera sea la activa en el shader
// glActiveTexture(GL_TEXTURE0 + texUnit);   // texunit de 0 a 32 (31 ?)
// glBindTexture(GL_TEXTURE_2D, mTexture);   // mTexture el identificador opengl generado con  glGenTextures
//--------------------------------------------------------------------------
/*------------------------------------------------------------------------*\
|* Concepto de Texture Unit (unidad de textura)
|* - piece of hw que tiene access a una texture image
|*   para activar multiples niveles/efectos se podrian activar distintas
|*   Texture Unit, GL_TEXTURE1, GL_TEXTURE2, ...
|*   ... por ahora nos quedamos generalmente con la GL_TEXTURE0 ...
\*------------------------------------------------------------------------*/
int cTextura::useTextura(int texUnit, GLint samplerLoc, int valorSampler)
{
    if (m_iTex > 0)
    {
        if (texUnit > -1 && texUnit < 32)
        {
            glActiveTexture(GL_TEXTURE0 + texUnit);
            if (m_mytype == textureType::TexCube)
            {
                glBindTexture(GL_TEXTURE_CUBE_MAP, m_iTex);
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, m_iTex);
            }

            // y no deberia ser el valor del sampler, sino el valor del samplerLoc > -1
            // el que diga si esto se activa o no.
            if (valorSampler > 0)
            {
                //--------------------------------------------------------------
                // Segun parece no hace falta: hasta nuevo aviso.
                //GLint iLoc = pShader->getLocation(nameUniform);
                //cShader::SetUniform(iLoc, valorSampler);
                // 
                // No parece que la textura necesite el uniform sobre su 'texSampler1'
                // En origen no tengo ni el m_nameLoc que nos daria su location.
                //--------------------------------------------------------------
            }
        }
    }
    return 0;
}


int  cTextura::useTextura(int texUnit, cShader* pShader, const char* nameUniform, int valorSampler)
{
    if (m_iTex > 0)
    {
        if (texUnit > -1 && texUnit < 32)
        {
            glActiveTexture(GL_TEXTURE0 + texUnit);
            if (m_mytype == textureType::TexCube)
            {
                glBindTexture(GL_TEXTURE_CUBE_MAP, m_iTex);
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, m_iTex);
            }

            //--------------------------------------------------------------
            // Segun parece no hace falta: hasta nuevo aviso.
            //GLint iLoc = pShader->getLocation(nameUniform);
            //cShader::SetUniform(iLoc, valorSampler);
            // 
            // No parece que la textura necesite el uniform sobre su 'texSampler1'
            // En origen no tengo ni el m_nameLoc que nos daria su location.
            //--------------------------------------------------------------
        }
    }
    return 0;
}


void cTextura::getLocations(cShader* shader)
{
    if (!m_nameLoc.empty())
    {
        m_texLoc = shader->getLocation(m_nameLoc.c_str());
    }
}


void cTextura::unbind(GLuint texUnit)
{
    glActiveTexture(GL_TEXTURE0 + texUnit);
    if (m_mytype == textureType::TexCube)
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

//--------------------------------------------------------------------------
void cTextura::setMaterial(cMaterial* material)
{
    m_material = material;
}


cMaterial* cTextura::getMaterial()
{
    return m_material;
}
//--------------------------------------------------------------------------


/*========================================================================*\
|* Codigo No OpenGL Moderno
\*========================================================================*/
//--------------------------------------------------------------------------
// Activamos la textura para apartir de aqui poder dibujar la textura.
//--------------------------------------------------------------------------
void cTextura::activa(bool activeSampler, GLenum unitTextura)
{
    if (m_iTex == 0)
    {
        //carga();
    }

    if (m_iTex > 0)
    {
        //------------------------------------------------------------------
        // Si Blend
        //------------------------------------------------------------------
        //if (getTipoTextura() == eTipoTextura::eCOL0)
        //{
        //    m_bActiveBlend = false;
        //    if (glIsEnabled(GL_BLEND))
        //    {
        //        this->
        //            m_bActiveBlend = true;
        //    }
        //    else
        //    {
        //        glEnable(GL_BLEND);
        //        glEnable(GL_ALPHA_TEST);
        //        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);      // La funcion de blending, no se si es la que uso.
        //    }
        //}
        //------------------------------------------------------------------

        //------------------------------------------------------------------
        // Si activeSampler
        //------------------------------------------------------------------
        if (activeSampler)
        {
            glActiveTexture(unitTextura);
        }
        else
        {
            if (!glIsEnabled(GL_TEXTURE_2D))
            {
                glEnable(GL_TEXTURE_2D);
                m_bActiveTex = false;
            }
            else
            {
                m_bActiveTex = true;
            }
        }
        //------------------------------------------------------------------
        glBindTexture(GL_TEXTURE_2D, m_iTex);
        //------------------------------------------------------------------
    }
}


//--------------------------------------------------------------------------
// Activamos la textura para apartir de aqui poder dibujar la textura.
//--------------------------------------------------------------------------
void cTextura::desActiva(void)
{
    if (!m_bActiveTex)
        glDisable(GL_TEXTURE_2D);

    // Deberia volver m_bActiveTex a true ???

    if (!m_bActiveBlend)
    {
        glDisable(GL_BLEND);
        glDisable(GL_ALPHA_TEST);
    }
    m_bActiveBlend = false;
    //------------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, 0);
    //------------------------------------------------------------------
}


//--------------------------------------------------------------------------
// Para decirnos si estaba habilitada o no GL_TEXTURE_2D
//--------------------------------------------------------------------------
bool cTextura::estaActivaTex2D(void)
{
    return m_bActiveTex;
}
/*========================================================================*/


/*========================================================================*\
|* Fin de cTextura.cpp
\*========================================================================*/
