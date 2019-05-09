#if !defined(ICONFIG_H)
#define ICONFIG_H 1

typedef struct config {
    int screenWidth;
    int screenHeight;
    char* title;
    int fps;
}Config;

Config NewConfig();

#endif //ICONFIG_H