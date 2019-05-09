#include "../header/config.h"

Config NewConfig() {
    Config config; 
    config.screenWidth = 640;
    config.screenHeight = 480;
    config.title = "I, robot";
    config.fps = 60;

    return config;
}