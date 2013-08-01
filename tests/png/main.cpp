#include "texture.h"

#include <iostream>

int main() {
    glEnable(GL_TEXTURE_2D);
    for(unsigned int i = 0 ; i < 10 ; i++)
    {
        {
            Texture t("test.png");
            std::cout
                << "; id : " << t.id()
                << "; wi : " << t.width()
                << "; he : " << t.height()
                << std::endl;
        }
        {
            Texture t("test2.png");
            std::cout
                << "; id : " << t.id()
                << "; wi : " << t.width()
                << "; he : " << t.height()
                << std::endl;
        }
    }
    return 0;
}
