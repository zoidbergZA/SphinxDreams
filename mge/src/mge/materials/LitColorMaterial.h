#ifndef LITCOLORMATERIAL_H
#define LITCOLORMATERIAL_H

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Mesh.hpp"
#include <glm.hpp>
#include <iostream>
#include <sstream>
#include <ostream>
#include "BaseLight.h"

#define MAX_LIGHTS_NUM 5
/**
 * Lit color material.
 * This material uses lights.
 */

using namespace std;

class LitColorMaterial : public AbstractMaterial
{
    public:
        LitColorMaterial(glm::vec3 pColor, Texture* pDiffuseTexture);
        virtual ~LitColorMaterial();

        virtual void render(RenderPipeline* pRenderPipeline, World* pWorld, GameObject* pGameObject, std::shared_ptr<Mesh> pMesh, Camera* pCamera);


        //in rgb values
        void setDiffuseColor (glm::vec3 pDiffuseColor);
        void setDiffuseTexture (Texture* pDiffuseTexture);

        static string uniName(string propertyName, int lightIndex);

    private:
        //all the static properties are shared between instances of ColorMaterial
        //note that they are all PRIVATE, we do not expose this static info to the outside world
        static ShaderProgram* _shader;
        void _lazyInitializeShader();

        //in this example we cache all identifiers for uniforms & attributes
        static GLint _uModelMatrix;
        static GLint _uViewMatrix;
        static GLint _uPerspectiveMatrix;
        static GLint _light_MVP;


        static GLint uGlobalAmbientIndex[];
        static GLint uDiffuseColorIndex[];
        static GLint uLightPositionIndex[];
        static GLint uConeDirectionIndex[];
        static GLint uConeAnglesIndex[];

        static GLint uCameraPosIndex;
        static GLint lightsUniforArraySize;
        static GLint _aVertex;
        static GLint _aNormal;
        static GLint _aUV;

        // ----------- STUFF FOR 2-ND SHADER TO SHOW SHADOW MAP ----------- //
        static ShaderProgram* _shaderSS;
        static GLint _light_MVP2;
        static GLint _aVertex2;
        static GLint _aUV2;
        // ----------- STUFF FOR 2-ND SHADER TO SHOW SHADOW MAP ----------- //

        //this one is unique per instance of material
        glm::vec3 _diffuseColor;
        Texture* _diffuseTexture;

        static std::vector<Texture*> _shadowTextures;
        static int tempSize;
        static glm::mat4 biasMat;
};

#endif // LITCOLORMATERIAL_H
