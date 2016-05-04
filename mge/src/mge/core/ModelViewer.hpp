#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include <iostream>
#include <windows.h>

#include "mge/core/GameObject.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/behaviours/MeshRenderer.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

class ModelViewer : public GameObject
{
    public:
        ModelViewer();
        virtual ~ModelViewer();

        virtual void update(float pStep, const glm::mat4& pParentTransform);
        void refresh();
        void changeModelMesh(std::string pFilename);
        void changeModelTexture(std::string pFilename);
        vector<string> getModelNames()
        {
            return _modelNames;
        }
        vector<string> getTextureNames()
        {
            return _textureNames;
        }
        GameObject* getModel()
        {
            return _model;
        }

    protected:

    private:
        void initialize();

        GameObject* _cameraObject;
        GameObject* _model;
        MeshRenderer* _meshRenderer;
        std::shared_ptr<TextureMaterial> _textureMaterial;
        vector<string> _modelNames;
        vector<string> _textureNames;
};

#endif // MODELVIEWER_H
