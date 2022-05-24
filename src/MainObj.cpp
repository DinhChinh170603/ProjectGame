
#include "MainObj.h"
#include <iostream>

// hàm khởi tạo
MainObj::MainObj()
{
    frame_ = 0;                // xử lí animations của player
    x_pos_ = 0;                // xử lí vị trí của player
    y_pos_ = 0;                //
    x_val_ = 0;                // xử lí lượng di chuyển của player
    y_val_ = 0;                //
    width_frame_ = 0;          // chiều rộng player
    height_frame_ = 0;         // chiều cao player
    status_ = WALK_NONE;       // trạng thái của player
    input_type_.left_ = 0;        //
    input_type_.right_ = 0;       //
    input_type_.jump_ = 0;        // xử lí chuyển động nhân vật
    input_type_.down_ = 0;        //
    input_type_.up_ = 0;          //
    on_ground_ = false;      // xử lí nhân vật đứng trên đất
    map_x_ = 0;              // xử lí map
    map_y_ = 0;
    come_back_time = 0;      // xử lí thời gian hồi sinh
    item_count1 = 0;
    item_count2 = 0;         // đếm lượng item ăn được
    item_count3 = 0;
    delay_bullet = 0;
    chunkitem = Mix_LoadWAV("audio//item.wav");        // xử lí âm thanh
    chunkbullet = Mix_LoadWAV("audio//bullet.wav");    //
    chunkwin = Mix_LoadWAV("audio//win.wav");          //

}

MainObj::~MainObj()
{
    // Free
}

bool MainObj::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObj::LoadImg(path, screen);

    if (ret == true)
    {
        width_frame_ = rect_.w/8;
        height_frame_ = rect_.h;
    }

    return ret;
}

SDL_Rect MainObj::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
}


// hàm xử lí animations của nhân vật
void MainObj::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].w = width_frame_;
        frame_clip_[0].h = height_frame_;

        frame_clip_[1].x = width_frame_;
        frame_clip_[1].y = 0;
        frame_clip_[1].w = width_frame_;
        frame_clip_[1].h = height_frame_;

        frame_clip_[2].x = 2*width_frame_;
        frame_clip_[2].y = 0;
        frame_clip_[2].w = width_frame_;
        frame_clip_[2].h = height_frame_;

        frame_clip_[3].x = 3*width_frame_;
        frame_clip_[3].y = 0;
        frame_clip_[3].w = width_frame_;
        frame_clip_[3].h = height_frame_;

        frame_clip_[4].x = 4*width_frame_;
        frame_clip_[4].y = 0;
        frame_clip_[4].w = width_frame_;
        frame_clip_[4].h = height_frame_;

        frame_clip_[5].x = 5*width_frame_;
        frame_clip_[5].y = 0;
        frame_clip_[5].w = width_frame_;
        frame_clip_[5].h = height_frame_;

        frame_clip_[6].x = 6*width_frame_;
        frame_clip_[6].y = 0;
        frame_clip_[6].w = width_frame_;
        frame_clip_[6].h = height_frame_;

        frame_clip_[7].x = 7*width_frame_;
        frame_clip_[7].y = 0;
        frame_clip_[7].w = width_frame_;
        frame_clip_[7].h = height_frame_;

    }
}

void MainObj::Show(SDL_Renderer* des)
{
    UpdateImagePlayer(des);

    if (input_type_.left_ == 1 ||
        input_type_.right_ == 1)
    {
        frame_++;
    }
    else
    {
        frame_ = 0;
    }

    if (frame_ >= 8)
    {
        frame_ = 0;
    }

    if (come_back_time == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;

        SDL_Rect* current_clip = &frame_clip_[frame_];

        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

        SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
    }
}

// hàm xử lí các thao tác từ bản phím
void MainObj::HandelInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if (delay_bullet > 0)
    {
        delay_bullet--;
    }
    if (events.type == SDL_KEYDOWN) // KEYDOWN là ấn bất kì nút nào từ bàn phím
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_d:        // nút mũi tên sang phải
            {
                status_= WALK_RIGHT;
                input_type_.right_ = 1;
                input_type_.left_ = 0;
                UpdateImagePlayer(screen);
            }
            break;
        case SDLK_a:         // nút mũi tên sang trái
            {
                status_ = WALK_LEFT;
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                UpdateImagePlayer(screen);
            }
            break;
        }
    }
    else if (events.type == SDL_KEYUP)  // KEYUP là nhả phím
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_d:                    // nhả d ra không chạy sang phải
            {
                input_type_.right_ = 0;
            }
            break;
        case SDLK_a:                    // nhả a ra không chạy sang trái
            {
                input_type_.left_ = 0;
            }
            break;
        }
    }

    if (events.type == SDL_KEYDOWN)
    {
        if (events.key.keysym.sym == SDLK_w)     // events... là phím mình bấm
        {
            input_type_.jump_ = 1;
        }
        else if (events.key.keysym.sym == SDLK_j && delay_bullet == 0)  // ấn key j để bắn, hãm đạn bắn liên tục
        {
            BulletObj* p_bullet = new BulletObj();
            p_bullet->LoadImg("img//player_bullet.png", screen);    // load vào hình ảnh đạn bắn
            Mix_PlayChannel(-1, chunkbullet, 0);               // phát ra âm thanh đạn bắn
            if (status_ == WALK_LEFT)
            {
                p_bullet->set_bullet_dir(BulletObj::DIR_LEFT);
                p_bullet->SetRect(this->rect_.x, rect_.y + height_frame_*PLAYER_BULLET);   // set vị trí đạn bắn ra
            }
            else
            {
                p_bullet->set_bullet_dir(BulletObj::DIR_RIGHT);
                p_bullet->SetRect(this->rect_.x + width_frame_ - 20, rect_.y + height_frame_*PLAYER_BULLET);   // set vị trí đạn bắn ra
            }

            p_bullet->set_x_val(BULLET_SPEED);       // tốc độ bullet
            p_bullet->set_is_move(true);             // bấm phím là bắn

            p_bullet_list_.push_back(p_bullet);  // thêm bullet vào danh sách
            delay_bullet = DELAY_BULLET;         // hàm tốc độ bắn

        }
    }
}


// hàm xử lí bắn đạn ra
void MainObj::HandelBullet(SDL_Renderer* des, Map& map_data)
{
    for (int i = 0; i < p_bullet_list_.size(); i++)
    {
        BulletObj* p_bullet = p_bullet_list_.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move() == true)   // ktra trạng thái để được phép bắn
            {
                p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_bullet->Render(des);
            }
            else
            {
                p_bullet_list_.erase(p_bullet_list_.begin() + i);  // loại đạn khỏi danh sách
                if (p_bullet != NULL)   // ktra xem đã loại chưa rồi mới xóa
                {
                    delete p_bullet;    // xóa đạn tránh tốn bộ nhớ
                    p_bullet = NULL;
                }
            }
        }
    }
}

// hàm xóa viên đạn
void MainObj::RemoveBullet(const int& idx)
{
    int size = p_bullet_list_.size();
    if (size > 0 && idx < size)
    {
        BulletObj* p_bullet = p_bullet_list_.at(idx);
        p_bullet_list_.erase(p_bullet_list_.begin() + idx);

        if (p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}


// xử lí toàn bộ các events player
void MainObj::DoPlayer(Map& map_data, Uint32 &mark_value)
{
    if (come_back_time == 0)  // chỉ khi nào nhân vật chạm đất mới thực hiện các chức năng này
    {
        x_val_ = 0;
        y_val_ += GRAVITY_SPEED;

        if (y_val_ >= MAX_FAIL_SPEED)
        {
            y_val_ = MAX_FAIL_SPEED;
        }

        if (input_type_.left_ == 1)
        {
            x_val_ -= PLAYER_SPEED;
        }
        else if (input_type_.right_ == 1)
        {
            x_val_ += PLAYER_SPEED;
        }

        if (input_type_.jump_ == 1)
        {
            if (on_ground_ == true) // xử lí chỉ khi nào trên mặt đất mới có thể nhảy (không cho nhảy 2 lần)
            {
                y_val_ = - PLAYER_JUMP_VAL;
            }

            on_ground_ = false; // fix lỗi nhảy rời rạc
            input_type_.jump_ = 0; // nhảy xong thì gán về 0
        }

        CheckToMap(map_data, mark_value );
        CenterEntityOnMap(map_data);
    }

    if (come_back_time > 0)  // chỉ khi nào nhân vật bị rơi khỏi map mới thực hiện các chức năng này
    {
        come_back_time--;
        if (come_back_time == 0)
        {
            on_ground_ = false;
            if (x_pos_ > 256)
            {
                x_pos_ -= 256; // 4 ô tile map
            }
            else
            {
                x_pos_ = 0;
            }

            y_pos_ = 0;
            x_val_ = 0;
            y_val_ = 0;
        }
    }
}

// hàm xử lí map di chuyển theo nhân vật
void MainObj::CenterEntityOnMap(Map& map_data)
{
    map_data.start_x_ = x_pos_ - (SCREEN_WIDTH/2);
    if (map_data.start_x_ < 0) // đầu map khi player tại vị trí 0->screen/2 thì map chưa bị dịch chuyển
    {
        map_data.start_x_ = 0;
    }
    else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_) // tương tự với cuối map
    {
        map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
    }

    map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT/2);
    if (map_data.start_y_ < 0)
    {
        map_data.start_y_ = 0;
    }
    else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
    {
        map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
    }
}

void MainObj::CheckToMap(Map& map_data, Uint32 &mark_value)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    // Kiểm tra theo chiều ngang
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_)/TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1)/TILE_SIZE;

    y1 = (y_pos_)/TILE_SIZE;
    y2 = (y_pos_ + height_min - 1)/TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val_ > 0) // mainobj đang di chuyển sang phải
        {

            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

            if (val1 == STATE_ITEM1 || val2 == STATE_ITEM1)    // khi player chạm vào các ô vật phẩm
            {
                map_data.tile[y1][x2] = 0;         // xóa ô vật phẩm mà nhân vật chạm vào
                map_data.tile[y2][x2] = 0;
                IncreaseItem1();
                mark_value += 10;
                Mix_PlayChannel(-1, chunkitem, 0);
            }
            else if (val1 == STATE_ITEM2 || val2 == STATE_ITEM2)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                IncreaseItem2();
                mark_value += 20;
                Mix_PlayChannel(-1, chunkitem, 0);
            }
            else if (val1 == STATE_ITEM3 || val2 == STATE_ITEM3)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                IncreaseItem3();
                mark_value -= 10;
                Mix_PlayChannel(-1, chunkitem, 0);
            }
            else if (val1 == STATE_ITEM4 || val2 == STATE_ITEM4)
            {
                Mix_PlayChannel(-1, chunkwin, 0);
                SDL_Delay(3000);
                SDL_Quit();
            }
            else
            {
                if (val1 != BLANK_TILE || val2 != BLANK_TILE) // player gặp phải những ô không phải ô trống
                {
                    x_pos_ = x2*TILE_SIZE;
                    x_pos_ -= width_frame_ + 1;
                    x_val_ = 0;                     // không cho nhân vật đi thêm nữa
                }
            }
        }
        else if (x_val_ < 0)                     // tương tự với chiều âm
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if (val1 == STATE_ITEM1 || val2 == STATE_ITEM1)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y2][x1] = 0;
                IncreaseItem1();
                mark_value += 10;
                Mix_PlayChannel(-1, chunkitem, 0);
            }
            else if (val1 == STATE_ITEM2 || val2 == STATE_ITEM2)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y2][x1] = 0;
                IncreaseItem2();
                mark_value += 20;
                Mix_PlayChannel(-1, chunkitem, 0);
            }
            else if (val1 == STATE_ITEM3 || val2 == STATE_ITEM3)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y2][x1] = 0;
                IncreaseItem3();
                mark_value -= 10;
                Mix_PlayChannel(-1, chunkitem, 0);
            }
            else if (val1 == STATE_ITEM4 || val2 == STATE_ITEM4)
            {
                Mix_PlayChannel(-1, chunkwin, 0);
                SDL_Delay(3000);
                SDL_Quit();
            }
            else
            {
                if (val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    x_pos_ = (x1 + 1)*TILE_SIZE;
                    x_val_ = 0;
                }
            }
        }
    }


    // ktra theo chiều dọc
    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_)/TILE_SIZE;
    x2 = (x_pos_ + width_min)/TILE_SIZE;

    y1 = (y_pos_ + y_val_)/TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1)/TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
    {
        if (y_val_ > 0)                   // tương tự với chiều dọc (rơi xuống chạm vào vật phẩm)
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if (val1 == STATE_ITEM1 || val2 == STATE_ITEM1)
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                IncreaseItem1();
                mark_value += 10;
                Mix_PlayChannel(-1, chunkitem, 0);
            }
            else if (val1 == STATE_ITEM2 || val2 == STATE_ITEM2)
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                IncreaseItem2();
                mark_value += 20;
                Mix_PlayChannel(-1, chunkitem, 0);
            }
            else if (val1 == STATE_ITEM3 || val2 == STATE_ITEM3)
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                IncreaseItem3();
                mark_value -= 10;
                Mix_PlayChannel(-1, chunkitem, 0);
            }
            else if (val1 == STATE_ITEM4 || val2 == STATE_ITEM4)
            {
                Mix_PlayChannel(-1, chunkwin, 0);
                SDL_Delay(3000);
                SDL_Quit();
            }
            else
            {
                if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
                {
                    y_pos_ = y2*TILE_SIZE;
                    y_pos_ -= (height_frame_ + 1);
                    y_val_ = 0;

                    on_ground_ = true;
                    if (status_ == WALK_NONE)
                    {
                        status_ = WALK_RIGHT;
                    }

                }
            }
        }
        else if (y_val_ < 0)            // tương tự với nhảy lên chạm vào vật phẩm
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];
            if (val1 == STATE_ITEM1 || val2 == STATE_ITEM1)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
                IncreaseItem1();
                mark_value += 10;
                Mix_PlayChannel(-1, chunkitem, 0);
            }
            else if (val1 == STATE_ITEM2 || val2 == STATE_ITEM2)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
                IncreaseItem2();
                mark_value += 20;
                Mix_PlayChannel(-1, chunkitem, 0);
            }
            else if (val1 == STATE_ITEM3 || val2 == STATE_ITEM3)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
                IncreaseItem3();
                mark_value -= 10;
                Mix_PlayChannel(-1, chunkitem, 0);
            }
            else if (val1 == STATE_ITEM4 || val2 == STATE_ITEM4)
            {
                Mix_PlayChannel(-1, chunkwin, 0);
                SDL_Delay(3000);
                SDL_Quit();
            }
            else
            {
                if (val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    y_pos_ = (y1 + 1)*TILE_SIZE;
                    y_val_ = 0;
                }
            }
        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if (x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ > map_data.max_x_)
    {
        x_pos_ = map_data.max_x_ - width_frame_ - 1;
    }

    if (y_pos_+64 > map_data.max_y_) // xử lí lỗi 1 vài hố rơi không chết (+1 tile map)
    {
        come_back_time = 60;

    }

}

// hàm thu thập lượng iteam ăn được
void MainObj::IncreaseItem1()
{
    item_count1++;
}
void MainObj::IncreaseItem2()
{
    item_count2++;
}
void MainObj::IncreaseItem3()
{
    item_count3++;
}

// hàm cập nhật hình ảnh cho nhân vật
void MainObj::UpdateImagePlayer(SDL_Renderer* des)
{
    if (on_ground_ == true)
    {
        if (status_ == WALK_LEFT)
        {
            LoadImg("img//player_left.png", des);
        }
        else
        {
            LoadImg("img//player_right.png", des);
        }
    }
    else
    {
        if (status_ == WALK_LEFT)
        {
            LoadImg("img//jump_left.png", des);
        }
        else
        {
            LoadImg("img//jump_right.png", des);
        }
    }
}


// hàm xử lí rơi xuống vực bị mất mạng
bool MainObj::IsDeath(Map& map_data, int &num_die)
{
    if (y_pos_+64 > map_data.max_y_ && come_back_time == 59) // xử lí mất mạng khi rơi xuống hố (come_back_time phải nằm trong khoảng 0->60 vì backtime đếm ngược từ 60)
    {
        num_die++;
        return true;  // trả về true nếu player death
//        std::cout << num_die << std::endl; // check
    }
    return false;
}
