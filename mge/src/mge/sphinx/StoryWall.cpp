#include "StoryWall.hpp"

StoryWall::StoryWall(std::string pModelName, std::string pTextureName, std::string pObjectName)  : GameObject(pObjectName)
{
    _material = std::shared_ptr<LitTextureMaterial>(new LitTextureMaterial(Texture::load("mge/textures/" + pTextureName)));
    _meshRenderer = new MeshRenderer(pModelName, _material, this);
}

StoryWall::~StoryWall()
{
    //dtor
}

void StoryWall::setTexture(string pTextureName)
{
    _material->changeDiffuseTexture(pTextureName);
}

void StoryWall::update(float pStep, const glm::mat4& pParentTransform)
{
    GameObject::update(pStep, pParentTransform);
}
