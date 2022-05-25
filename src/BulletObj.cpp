

#include "BulletObj.h"

// hàm khởi tạo các thông số ban đầu cho bullet
BulletObj::BulletObj()
{
    x_val_ = 0;       // tọa độ đạn
    y_val_ = 0;
    is_move_ = false;  // ktra đạn đang di chuyển trên màn hình
}

BulletObj::~BulletObj()
{
    // Free();
}

void BulletObj::HandleMove(const int& x_border, const int& y_border)     // truyền vào các rect hiện tại của màn hình
{
    if (bullet_dir_ == DIR_RIGHT)        // xử lí đạn bắn về phía phải
    {
        rect_.x += x_val_;
        if (rect_.x > x_border - BULLET_LIMIT)    // xử lí giới hạn chiều dài đạn
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_LEFT)           // xử lí đạn bắn về phía trái
    {
        rect_.x -= x_val_;
        if (rect_.x < BULLET_LIMIT)
        {
            is_move_ = false;
        }
    }
}
