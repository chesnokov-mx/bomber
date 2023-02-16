//
// Created by Mac on 01/03/2021.
//

#ifndef INC_2048_WITH_SFML_MATRIXTOKEN_H
#define INC_2048_WITH_SFML_MATRIXTOKEN_H

#include "token.h"
#include <vector>
using namespace std;

class MatrixToken {
public:
    vector<vector<token>> matrix;
    int Number_of_mines;
    bool BOOM = false;
    int widX;
    int widY;

    MatrixToken CreateMatrixGame(int x, int y, int Number_of_mines){
        MatrixToken result;
        result.Number_of_mines = Number_of_mines;
        result.widX = x;
        result.widY = y;
        for (int i = 0; i < x; ++i){
            std::vector<token> tmp;
            for (int j = 0; j < y; ++j){
                tmp.push_back(token());
            }
            result.matrix.push_back(tmp);
            tmp.clear();
        }


        std::vector<std::vector<char>> numbers;
        for (int i = 0; i < x; ++i){
            std::vector<char> tmp;
            for (int j = 0; j < y; ++j){
                tmp.push_back('0');
            }
            numbers.push_back(tmp);
            tmp.clear();
        }

        srand(time(NULL));
        std::vector<int> bombs;

        for (int i = 0; i < Number_of_mines; ++i) {
            int xo = rand() % (x * y);

            for (auto &i : bombs) {
                if (i == xo) {
                    --i;
                    continue;
                }
            }
            bombs.push_back(xo);
        }

        for (auto i : bombs){
            result.matrix[i / y][i % y].bomb = true;
        }

        std::cout << std::endl << std::endl;

        for (int i = 0; i < x; ++i){
            for (int j = 0; j < y; ++j){
                if (result.matrix[i][j].bomb) continue;
                result.matrix[i][j].num = result.CalcNear(i, j);
            }
        }

        return result;
    }

    bool outBounds(int x, int y){
        return x < 0|| y < 0||x > widX - 1|| y > widY-1;
    }

    int CalcNear(int i, int j){
        if (outBounds(i, j)) return 0;
        int bombes = 0;
        for (int offsetX=-1; offsetX<=1; offsetX++) {
            for (int offsetY=-1; offsetY<=1; offsetY++) {
                if (outBounds(offsetX+i, offsetY+j))continue;
                if (matrix[offsetX+i][offsetY+j].bomb) bombes++;
            }
        }
        return bombes;
    }

    int GetUnpressedField() const {
        int counter = 0;
        for (auto x : matrix){
            for (auto i : x){
                if (i.pressed == false) counter++;
            }
        }
        return counter;
    }

    void Flag(int i, int j){
        matrix[i][j].flag = true;
    }

    void Press(int i, int j){
        //if(out_of_bounds(i, j)) return;
        if(outBounds(i, j)) return;
        if(matrix[i][j].pressed) return;

        if(matrix[i][j].bomb) {
            BOOM = true;
            RevealEverything();
            matrix[i][j].num = 777;
        }
        matrix[i][j].pressed = true;

        if (matrix[i][j].num != 0) return;
        {
            Press(i - 1, j - 1);
            Press(i - 1, j + 1);
            Press(i - 1 , j);
            Press(i + 1 , j - 1);

            Press(i + 1, j + 1);
            Press(i + 1, j);
            Press(i, j - 1);
            Press(i, j + 1);
        }
    }

    void RevealEverything(){
        for (auto& x: matrix){
            for (auto& i : x){
                i.pressed = true;
            }
        }
    };
};

#endif //INC_2048_WITH_SFML_MATRIXTOKEN_H
