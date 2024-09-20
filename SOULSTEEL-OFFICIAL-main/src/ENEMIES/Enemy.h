//
// Created by lrfri on 04.06.2024.
//

#ifndef RAYLIBSTARTER_ENEMY_H
#define RAYLIBSTARTER_ENEMY_H

#include "../gameplay.h"
#include "raylib.h"
#include "../scene.h"
#include "raymath.h"
#include "../enemymodus.h"
#include <iostream>
#include "../Enums.h"
#include "../Utils.h"
#include "../HealthManager.h"


class gameplay;
class Wall;
class maincharacter;

class Enemy{
public:
    Enemy(gameplay*scene,int hp, int damage, bool melee, bool ranged, bool armed,
          float left, float down, float right, float up);

    //position
    float stopleft;
    float stopdown;
    float stopright;
    float stopup;
    Vector2 position{}; //current position of enemy
    void updateAnimationBasedOnMovement(const Vector2& oldPosition); //for Enemy stop points
    Direction currentMoveDirection; //for Enemy stop points

    int id = 0;

    // Speed
    float normalSpeed = 1.0f;  // Default normal movement speed

    // Chase maincharacter
    bool isChasing;
    float chaseRadius;
    float chaseSpeed;
    void updateMovement(const Vector2& targetPosition);

    //HEALTH
    HealthManager healthManager;
    int health;

    void takeDamage(int amount);
    //void heal(int amount);
    bool isAlive() const;
    float getHealthPercentage() const;

    //*NEW CODE*
    void drawHealthStatus() const;
    static constexpr float HEALTH_TEXT_OFFSET_X = 20.0f;
    static constexpr float HEALTH_TEXT_OFFSET_Y = -20.0f;
    static constexpr int HEALTH_TEXT_FONT_SIZE = 15;

    virtual void update();
    virtual void draw();
    virtual Texture2D getCurrentTexture();

    void calculatePathAsRectangle();

    ControlType controltype;

    Direction facingDirection = Direction::Down;

    gameplay *_scene;

   // Enemy(gameplay *scene);

    virtual ~Enemy() = default; //virtual destructor for proper cleanup

    std::vector<Vector2> path; // stores the path the enemy will follow

    //Collision check
    bool checkCollision(const Wall &wall);
    Rectangle getCollisionRectangle() const;


    float stepsize = 2;
    float size = 12;
    int currentPathIndex = 0;


protected:
    struct AnimationData {
        AnimationState currentAnimationState;
        Direction facingDirection;
        int currentFrame;
        static const int FRAME_COUNT = 8;
        std::string entityType;
    };

    std::string enemyType;  // This will be set in derived classes
    AnimationData animData;
    float animationTimer;

//*NEW CODE*
    static const float FRAME_DURATION;


    static std::string toLowercase(const std::string& str);

    //std::string enemyType;


    virtual void updateAnimation(float deltaTime);


    int enemyDamage{};
    bool enemyTypeMelee{};
    bool enemyTypeRanged{};
    bool enemyTypeArmed{};


    // position and direction
    //Direction direction{};
    ControlRandom controlrandom;

    virtual void moveOnPath();
    virtual void moveRandomly();

};



#endif //RAYLIBSTARTER_ENEMY_H
