#define _CRT_SECURE_NO_WARNINGS
#include "Riddle.h"

Riddle::Riddle(const char* r_text[Game::MAX_Y], int r_x, int r_y,int r_room_connected, char the_answer): x(r_x), y(r_y), room_connected(r_room_connected), answer(the_answer)
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        strcpy(text[i], r_text[i]);
    }
}
Riddle::Riddle()
{
}
//// **Copy Constructor** (Deep Copy)
//Riddle::Riddle(const Riddle& other): x(other.x), y(other.y), room_connected(other.room_connected), answer(other.answer)
//{
//    for (int i = 0; i < Game::MAX_Y; i++)
//    {
//        strcpy(text[i], other.text[i]);
//    }
//}




//Riddle& Riddle::operator=(const Riddle& other)
//{
//    if (this != &other) // Check for self-assignment
//    {
//        // 1. Clean up existing resources (Destructor Logic)
//        for (int i = 0; i < Game::MAX_Y; i++)
//        {
//            if (text[i] != nullptr)
//            {
//                std::free((void*)text[i]);
//            }
//        }
//
//        // 2. Deep copy new resources
//        for (int i = 0; i < Game::MAX_Y; i++)
//        {
//
//            if (other.text[i] != nullptr)
//            {
//                text[i] = _strdup(other.text[i]);
//            }
//            else
//            {
//                text[i] = nullptr;
//            }
//        }
//
//        x = other.x;
//        y = other.y;
//        room_connected = other.room_connected;
//        answer = other.answer;
//    }
//    return *this;
//}

void Riddle::Show_Riddle() const
{
    if (is_active)
    {
        cls();
        gotoxy(0, 0);
        for (size_t i = 0; i < Game::MAX_Y - 1; ++i) {
            cout << text[i] << endl;
        }
        cout << text[Game::MAX_Y - 1];
        cout.flush();
    }
}

