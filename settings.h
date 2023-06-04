#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <vector>
#include "game.h"

const float WINDOW_WIDTH = 1920;
const float WINDOW_HEIGHT = 1080;
const float FPS = 60.f;
float Pspeed = 10.0;
float Espeed = 0.0;
const int MAX_PLAYER_LIVES = 10;
int prevTime = 0;
const int BONUS_OPERATING_TIME = 1000 ;
const int MaxPlayerSpeed = 20;