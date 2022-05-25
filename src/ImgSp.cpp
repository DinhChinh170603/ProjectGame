
#include "ImgSp.h"

// hàm khởi tạo
ImgSp::ImgSp()
{
    number_ = 0;
}

ImgSp::~ImgSp()
{
    //Free
}

void ImgSp::AddPos(const int& xp)
{
    pos_list_.push_back(xp);
}

void ImgSp::Init(SDL_Renderer* screen)
{
    LoadImg("img//player_life.png", screen);
    number_ = 3;
    if (pos_list_.size() > 0)
    {
        pos_list_.clear();
    }

    AddPos(85);
    AddPos(135);
    AddPos(185);
}

// Show mạng
void ImgSp::Show(SDL_Renderer* screen)
{
    for (int i = 0; i < pos_list_.size(); i++)
    {
        rect_.x = pos_list_.at(i);
        rect_.y = 0;
        Render(screen);
    }
}

// Xử lí mất mạng
void ImgSp::Decrease()
{
    number_--;
    pos_list_.pop_back();   // xóa phần tử cuối
}


PlayerItem::PlayerItem()
{
    x_pos_ = 0;
    y_pos_ = 0;
}

PlayerItem::~PlayerItem()
{
    // Free
}

// hàm khởi tạo đọc file ảnh
void PlayerItem::Init1(SDL_Renderer* screen)
{
    bool ret = LoadImg("img//item1.png", screen);
}
void PlayerItem::Init2(SDL_Renderer* screen)
{
    bool ret = LoadImg("img//item2.png", screen);
}
void PlayerItem::Init3(SDL_Renderer* screen)
{
    bool ret = LoadImg("img//item3.png", screen);
}

// hàm show
void PlayerItem::Show(SDL_Renderer* screen)
{
    rect_.x = x_pos_;
    rect_.y = y_pos_;
    Render(screen);
}
