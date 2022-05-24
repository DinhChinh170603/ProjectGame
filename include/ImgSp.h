

#ifndef IMGSP_H
#define IMGSP_H

#include "CommonFunction.h"
#include "BaseObj.h"

// Sp Life
class ImgSp : public BaseObj
{
public:
    ImgSp();
    ~ImgSp();

    void SetNum(const int& num) {number_ = num;}
    void AddPos(const int& xPos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);

//    void Increase();
    void Decrease();    // hàm giảm chỉ số mạng

private:
    int number_;              // chỉ số mạng
    std::vector<int> pos_list_; // danh sách vị trí hiển thị
};

// Sp item
class PlayerItem : public BaseObj
{
public:
    PlayerItem();
    ~PlayerItem();

    void Init1(SDL_Renderer* screen);
    void Init2(SDL_Renderer* screen);
    void Init3(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetPos(const int& x, const int& y) {x_pos_ = x, y_pos_ = y;}

private:
    int x_pos_;
    int y_pos_;
};
#endif // IMGSP_H
