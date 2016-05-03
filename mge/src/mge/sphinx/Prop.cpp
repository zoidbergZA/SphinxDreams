#include "Prop.hpp"

#include "mge/Materials/LitTextureMaterial.hpp"

Prop::Prop(std::string pModelName, std::string pTextureName, std::string pObjectName):GameObject(pObjectName)
{
    _material = std::shared_ptr<LitTextureMaterial>(new LitTextureMaterial(Texture::load("mge/textures/" + pTextureName)));
    _meshRenderer = std::shared_ptr<MeshRenderer>(new MeshRenderer(pModelName, _material, this));
}

Prop::~Prop()
{
    //dtor
}

void Prop::update(float pStep, const glm::mat4& pParentTransform)
{
    GameObject::update(pStep, pParentTransform);
}
