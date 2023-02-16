//
// Created by Mac on 01/03/2021.
//

#ifndef INC_2048_WITH_SFML_TOKEN_H
#define INC_2048_WITH_SFML_TOKEN_H

#include <SFML/Graphics.hpp>

class token {
public:
    bool bomb;
    int num;
    bool pressed = false;
    bool flag = false;
    sf::Texture texture;

    void updateToken(){
        if (num == 777){
            texture.loadFromFile("../Images/red_bomb.png");
            return;
        }
        if(pressed == false){
            if (flag){
                texture.loadFromFile("../Images/flag.png");
            }
            else texture.loadFromFile("../Images/field50x50.png");
        }

        else {
            if (bomb){
                texture.loadFromFile("../Images/grey_bomb.png");
            }
            else {
                if (num == 0) {
                    texture.loadFromFile("../Images/pressed_field.png");
                }
                if (num == 1) {
                    texture.loadFromFile("../Images/1.png");
                }
                if (num == 2) {
                    texture.loadFromFile("../Images/2.png");
                }
                if (num == 3) {
                    texture.loadFromFile("../Images/3.png");
                }
                if (num == 4) {
                    texture.loadFromFile("../Images/4.png");
                }
                if (num == 5) {
                    texture.loadFromFile("../Images/5.png");
                }
                if (num == 6) {
                    texture.loadFromFile("../Images/6.png");
                }
                if (num == 7) {
                    texture.loadFromFile("../Images/7.png");
                }
                if (num == 8) {
                    texture.loadFromFile("../Images/8.png");
                }
            }
        }
    }

};




#endif //INC_2048_WITH_SFML_TOKEN_H
