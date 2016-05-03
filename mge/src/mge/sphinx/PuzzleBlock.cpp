#include "PuzzleBlock.hpp"
#include "mge/core/Timer.hpp"
#include "mge/Materials/LitTextureMaterial.hpp"
#include "mge/util/Utils.hpp"

PuzzleBlock::PuzzleBlock(std::string pModelName, std::string pTextureName, std::string pObjectName,
                         float x, float y, float z):GameObject(pObjectName)
{
    _targetForward = GameObject::getForward();
    _targetUp = GameObject::getUp();

    _material = std::shared_ptr<LitTextureMaterial>(new LitTextureMaterial(Texture::load("mge/textures/" + pTextureName)));

    _meshRenderer = new MeshRenderer(pModelName, _material, this);
    _colorFlasher = new ColorFlasher(this);
    _colorFlasher->setMaterial(_material);

    //set position
    setLocalPosition(glm::vec3(x, y, z));

    //randomize block rotation
    randomize();
}

PuzzleBlock::~PuzzleBlock()
{
    //dtor
}

float PuzzleBlock::flash(float pDuration)
{
    _colorFlasher->flash(glm::vec3(1.0f, 1.0f, 0.0f), pDuration);
}

void PuzzleBlock::randomize()
{
    rotate(Utils::randomRange(0.0f, 6.28319f), glm::vec3(1,0,0));
    rotate(Utils::randomRange(0.0f, 6.28319f), glm::vec3(0,1,0));
    rotate(Utils::randomRange(0.0f, 6.28319f), glm::vec3(0,0,1));
}

float PuzzleBlock::getProgress()
{
    glm::vec3 forwardDelta = _targetForward - GameObject::getForward();
    glm::vec3 backwardDelta = -_targetForward - GameObject::getForward();
    glm::vec3 upDelta = _targetUp - GameObject::getUp();

    float forwardFraction = (glm::length(forwardDelta) / 2.0f + glm::length(upDelta) / 2.0f) * 0.5f;
    float backwardFraction = (glm::length(backwardDelta) / 2.0f + glm::length(upDelta) / 2.0f) * 0.5f;

    if (forwardFraction <= backwardFraction)
        return 1.0f - forwardFraction;
    else
        return 1.0f - backwardFraction;
}

void PuzzleBlock::update(float pStep, const glm::mat4& pParentTransform)
{
    GameObject::update(pStep, pParentTransform);

//    if (Input::getKey(0))
//    {
//        roll(1.0f * pStep);
//    }
}
