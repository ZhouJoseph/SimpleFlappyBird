#include <sstream>
#include "DEFINITIONS.hpp"
#include "GameOverState.hpp"
#include "GameState.hpp"
#include <iostream>
#include <fstream>

namespace Sonar
{
    GameOverState::GameOverState(GameDataRef data, int score) : _data(data),_score(score)
    {
        
    }
    
    void GameOverState::Init()
    {
        std::ifstream ifs(HIGHEST_SCORE_FILEPATH);
        if(!ifs){
            std::cout << "ha";
            exit(0);
        }
        ifs >> _highScore;
        ifs.close();
        
        std::ofstream writeFile(HIGHEST_SCORE_FILEPATH);
        if(writeFile.is_open()){
            if(_score>_highScore){
                _highScore = _score;
            }
            writeFile << _highScore;
        }
        writeFile.close();
        
        this->_data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
        this->_data->assets.LoadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
        this->_data->assets.LoadTexture("Game Over Body", GAME_OVER_BODY_FILEPATH);
        
        
        this->_data->assets.LoadTexture("Bronze Medal", BRONZE_MEDAL_FILEPATH);
        this->_data->assets.LoadTexture("Silver Medal", SILVER_MEDAL_FILEPATH);
        this->_data->assets.LoadTexture("Gold Medal", GOLD_MEDAL_FILEPATH);
        this->_data->assets.LoadTexture("Platinum Medal", PLAY_BUTTON_FILEPATH);
        
        
        _background.setTexture(this->_data->assets.GetTexture("Game Over Background"));
        _gameOverTitle.setTexture(this->_data->assets.GetTexture("Game Over Title"));
        _gameOverContainer.setTexture(this->_data->assets.GetTexture("Game Over Body"));
        _retryButton.setTexture(this->_data->assets.GetTexture("Play Button"));
        
        int ContainerWidth = _data->window.getSize().x/2 - (_gameOverContainer.getGlobalBounds().width/2);
        int ContainerHeight = _data->window.getSize().y/2 - (_gameOverContainer.getGlobalBounds().height/2);
        _gameOverContainer.setPosition(ContainerWidth,ContainerHeight);

        int TitleWidth = _data->window.getSize().x/2 - (_gameOverTitle.getGlobalBounds().width/2);
        int TitleHeight = _gameOverContainer.getPosition().y - (_gameOverTitle.getGlobalBounds().height * 1.2);
        _gameOverTitle.setPosition(TitleWidth, TitleHeight);

        int butWidth = _data->window.getSize().x/2 - (_retryButton.getGlobalBounds().width/2);
        int butHeight =_gameOverContainer.getPosition().y + (_gameOverContainer.getGlobalBounds().height * 1.2);
        _retryButton.setPosition(butWidth, butHeight);
        
        _scoreText.setFont(_data->assets.GetFont("Flappy Font"));
        _scoreText.setString(std::to_string(_score));
        _scoreText.setCharacterSize(56);
        _scoreText.setFillColor(sf::Color::White);
        _scoreText.setOrigin(_scoreText.getGlobalBounds().width/2, _scoreText.getGlobalBounds().height/2);
        _scoreText.setPosition(_data->window.getSize().x / 10 * 7.25, _data->window.getSize().y / 2.15);
        
        _highScoreText.setFont(_data->assets.GetFont("Flappy Font"));
        _highScoreText.setString(std::to_string(_highScore));
        _highScoreText.setCharacterSize(56);
        _highScoreText.setFillColor(sf::Color::White);
        _highScoreText.setOrigin(_highScoreText.getGlobalBounds().width/2, _highScoreText.getGlobalBounds().height/2);
        _highScoreText.setPosition(_data->window.getSize().x / 10 * 7.25, _data->window.getSize().y / 1.78);
        
        if(_score >= PLATINUM_MEDAL_SCORE){
            _medal.setTexture(_data->assets.GetTexture("Platinum Medal"));
        } else if(_score>=GOLD_MEDAL_SCORE){
            _medal.setTexture(_data->assets.GetTexture("Gold Medal"));
        } else if(_score>=SILVER_MEDAL_SCORE){
            _medal.setTexture(_data->assets.GetTexture("Silver Medal"));
        } else {
            _medal.setTexture(_data->assets.GetTexture("Bronze Medal"));
        }
        
        _medal.setPosition(175, 465);
    
    }
    
    void GameOverState::HandleInput()
    {
        sf::Event event;
        
        while (this->_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                this->_data->window.close();
            }
            
            if(_data->input.IsSpriteClicked(_retryButton, sf::Mouse::Left, _data->window)){
                _data->machine.AddState(StateRef( new GameState(_data)), true);
            }
        }
    }
    
    void GameOverState::Update(float dt)
    {
        
    }
    
    void GameOverState::Draw(float dt)
    {
        this->_data->window.clear(sf::Color::Red);
        
        this->_data->window.draw(this->_background);
        this->_data->window.draw(_gameOverContainer);
        this->_data->window.draw(_gameOverTitle);
        this->_data->window.draw(_retryButton);
        this->_data->window.draw(_scoreText);
        this->_data->window.draw(_highScoreText);
        
        this->_data->window.draw(_medal);
        
        this->_data->window.display();
        
        
        
    }
}
