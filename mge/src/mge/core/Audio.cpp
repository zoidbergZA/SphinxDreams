#include "Audio.hpp"
#include "mge/util/Utils.hpp"

std::shared_ptr<Audio> Audio::instance = NULL;

//Make it a Singleton -- Only one instance allowed.
std::shared_ptr<Audio> Audio::Instance() {
    if (!instance) {
        instance = std::shared_ptr<Audio>(new Audio);
    }
    return instance;
}

Audio::Audio() {
    soundsPath = config::MGE_SOUNDS_PATH.c_str();
    musicPath = config::MGE_MUSIC_PATH.c_str();
}

Audio::~Audio() {
}

/// PRELOADING -- OPTIONAL
void Audio::PreloadAudio() {
    Instance()->LoadAudio();
}

void Audio::LoadAudio() {
    std::vector<std::string> soundNames = Utils::findFilesIn(soundsPath);

    for (size_t i=0; i < soundNames.size(); i++) {
        AddSound(soundNames[i]);
        std::cout << soundNames[i] << " preloaded!" << std::endl;
    }

    //Not tested!
    std::vector<std::string> musicNames = Utils::findFilesIn(musicPath);
    for (size_t i=0; i < musicNames.size(); i++) {
        AddMusic(musicNames[i]);
        std::cout << musicNames[i] << " indexed!" << std::endl;
    }
}
/// END PRELOADING

void Audio::AddSound(std::string fileName) {
    Buffers[fileName].loadFromFile(soundsPath + fileName);
    if (Buffers[fileName].getSampleCount() == 0)
        std::cout << "WARNING: You're playing an empty buffer on '" << fileName << "'!" << std::endl;
    Sounds[fileName].setBuffer(Buffers[fileName]);
}

sf::Sound &Audio::GetSound(std::string fileName) {
    Sounds[fileName].setBuffer(Buffers[fileName]);
    return Sounds[fileName];
}

void Audio::PlayEffect(std::string fileName) {
    instance = Instance();

    // Check if sound is loaded
    if(instance->Sounds.find(fileName) == Instance()->Sounds.end()) {                           // Sound not loaded.
        std::cout << "NOTE: First call... Loading sound '" << fileName << "'." << std::endl;
        instance->AddSound(fileName);                                                           // Load sound.
    }

    instance->GetSound(fileName).play();                                                        // Play sound.
    std::cout << "NOTE: Playing sound '" << fileName << "'." << std::endl;
}

// StopSound does not care about whether a sound is actually loaded/playing.
// It shows no errors.
void Audio::StopEffect(std::string fileName) {
    instance = Instance();

    if(instance->Sounds.find(fileName) == instance->Sounds.end()) {
        std::cout << "ERROR: Could not stop sound '" << fileName << "'." << std::endl;
        return;
    }

    instance->GetSound(fileName).stop();
    std::cout << "NOTE: Stopped sound '" << fileName << "'." << std::endl;
}

void Audio::PlayMusic(std::string fileName, bool loop) {
    instance = Instance();

    // Check if music is indexed
    if(instance->Music.find(fileName) == instance->Music.end()) {                               // Music not indexed.
        std::cout << "NOTE: First call... Indexing '" << fileName << "'." << std::endl;
        instance->AddMusic(fileName);                                                           // Load music.
    }

    instance->GetMusic(fileName).setLoop(loop);
    instance->GetMusic(fileName).play();                                                        // Play music.
    std::cout << "NOTE: Playing/Resuming music '" << fileName << "'." << std::endl;
}

// StopMusic cares about if a music is indexed! Not whether its playing or not.
void Audio::StopMusic(std::string fileName) {
    instance = Instance();
    if(instance->Music.find(fileName) == instance->Music.end()) {
        std::cout << "ERROR: Could not stop music '" << fileName << "'." << std::endl;
        return;
    }

    instance->GetMusic(fileName).stop();
    std::cout << "NOTE: Stopped music '" << fileName << "'." << std::endl;
}

void Audio::PauseMusic(std::string fileName) {
    instance = Instance();
    if(instance->Music.find(fileName) == instance->Music.end()) {
        std::cout << "ERROR: Could not pause music '" << fileName << "'." << std::endl;
        return;
    }

    instance->GetMusic(fileName).pause();
    std::cout << "NOTE: Paused music '" << fileName << "'." << std::endl;
}

void Audio::AddMusic(std::string fileName) {
    auto music = std::unique_ptr<sf::Music>(new sf::Music());
    music->openFromFile(musicPath + fileName);
    MapMusic(fileName,std::move(music));
}

//musicName is the map key.
void Audio::MapMusic(std::string fileName, std::unique_ptr<sf::Music> value) {
    Music.insert(std::pair<std::string, std::unique_ptr<sf::Music> >(fileName, std::move(value)));
}

sf::Music &Audio::GetMusic(std::string fileName) {
    return *Music.at(fileName);
}
