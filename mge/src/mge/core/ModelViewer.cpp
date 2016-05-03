#include "ModelViewer.hpp"
#include "mge/sphinx/PuzzleBlock.hpp"
#include "mge/util/Utils.hpp"

ModelViewer::ModelViewer() : GameObject("Model Viewer")
{
    initialize();
}

void ModelViewer::initialize()
{
    _cameraObject = new GameObject("camera", glm::vec3(0, 0, 5));

    Camera* cb = new Camera();
    _cameraObject->addBehaviour(cb);
    World::Instance()->setMainCamera(cb);

    refresh();
}

void ModelViewer::update(float pStep, const glm::mat4& pParentTransform)
{
    GameObject::update(pStep, pParentTransform);

    // show list of all available models
//    vector<string> modelnames = getModelNames();
//    for (size_t i=0; i < modelnames.size(); i++)
//    {
//        if(_hud->Button(0, i * 25, modelnames[i]) == true)
//        {
//            changeModelMesh(modelnames[i]);
//        }
//    }

//    // show list of all available textures
//    vector<string> texturenames = _modelViewer->getTextureNames();
//    for (size_t i=0; i < texturenames.size(); i++)
//    {
//        if(_hud->Button(195, i * 25, texturenames[i]) == true)
//        {
//            _modelViewer->changeModelTexture(texturenames[i]);
//        }
//    }
}

void ModelViewer::refresh()
{
    std::cout << "refresh model viewer" << std::endl;

    if (_model != NULL)
    {
        delete _model;
    }

    _modelNames = Utils::findFilesIn("mge/models/");
    _textureNames = Utils::findFilesIn("mge/textures/");

    _model = new GameObject(_modelNames[0]);

    _textureMaterial = std::shared_ptr<TextureMaterial>(new TextureMaterial(Texture::load("mge/textures/" + _textureNames[0])));
    _meshRenderer = new MeshRenderer(_modelNames[0], _textureMaterial);
    RotatingBehaviour* rb = new RotatingBehaviour();

    _model->addBehaviour(_meshRenderer);
    _model->addBehaviour(rb);

}

void ModelViewer::changeModelMesh(std::string pFilename)
{
    if (_meshRenderer == NULL)
        return;

    _meshRenderer->setMesh(pFilename);
}

void ModelViewer::changeModelTexture(std::string pFilename)
{
    if (_meshRenderer == NULL)
        return;

    _textureMaterial->changeDiffuseTexture(pFilename);
}

ModelViewer::~ModelViewer()
{
    //dtor
}
