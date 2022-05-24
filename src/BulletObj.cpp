

#include "BulletObj.h"

// hàm khởi tạo các thông số ban đầu cho bullet
BulletObj::BulletObj()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
}

BulletObj::~BulletObj()
{
    //dtor
}

void BulletObj::HandleMove(const int& x_border, const int& y_border)
{
    if (bullet_dir_ == DIR_RIGHT)
    {
        rect_.x += x_val_;
        if (rect_.x > x_border - BULLET_LIMIT)    // xử lí đạn bắn về phía phải
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_LEFT)
    {
        rect_.x -= x_val_;
        if (rect_.x < BULLET_LIMIT)           // xử lí đạn bắn về phía trái
        {
            is_move_ = false;
        }
    }
}
