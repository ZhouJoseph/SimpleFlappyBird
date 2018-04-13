#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Pipe.hpp"
#include "Land.hpp"
#include "Bird.hpp"
#include "Collision.hpp"
#include "Flash.hpp"
#include "HUD.hpp"

namespace Sonar
{
    class GameState : public State
    {
    public:
        GameState(GameDataRef data);
        
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        
    private:
        GameDataRef _data;
        
        sf::Sprite _background;
        
        Pipe *pipe;
        Land *land;
        Bird *bird;
        Collision collision;
        Flash *flash;
        
        sf::Clock clock;
        
        int _gameState;

        sf::RectangleShape _gameOverFlash;
        bool _flashOn;
        int _score;
        HUD* hud;
        
        
        sf::SoundBuffer _hitSoundBuffer;
        sf::SoundBuffer _wingSoundBuffer;
        sf::SoundBuffer _pointSoundBuffer;
        sf::SoundBuffer _bgSoundBuffer;
        sf::Sound _hitSound;
        sf::Sound _wingSound;
        sf::Sound _pointSound;
        sf::Sound _bg;
    };
}
