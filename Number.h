#ifndef NUMBER_H
#define NUMBER_H
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define NUM 100
#define win_w 500
#define win_h 650

class Number
{
    public:
        Number();
        virtual ~Number();
        int getnum();
    protected:

    private:
        int num;
};

#endif // NUMBER_H
