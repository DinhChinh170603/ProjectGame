
#include "CommonFunction.h"
#include "BaseObj.h"
#include "game_map.h"
#include "MainObj.h"
#include "ImpTimer.h"
#include "BulletObj.h"
#include "ThreatsObj.h"
#include "ExplosionObj.h"
#include "TextObj.h"
#include "ImgSp.h"
#include <iostream>

BaseObj g_background;
TTF_Font* font_time = NULL;

// hàm khởi tạo
bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_windows = SDL_CreateWindow("Chú chó đáng thương - By: DinhChinh - 21020288",
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SCREEN_WIDTH, SCREEN_HEIGHT,
                                 SDL_WINDOW_SHOWN);

    if (g_windows == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_windows, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }

        if (TTF_Init() == -1)
        {
            success = false;
        }

        font_time = TTF_OpenFont("font//dlxfont.ttf", 15); // đọc font bằng con trỏ
        if (font_time == NULL)
        {
            success = false;
        }
    }
    //khởi tạo âm thanh
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        printf("%s", Mix_GetError());
    }

    return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img//background.png", g_screen);
    if (ret == false)
        return false;

    return true;
}

// đóng chương trình
void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_windows);
    g_windows = NULL;

    IMG_Quit();
    SDL_Quit();
}

std::vector<ThreatsObj*> MakeThreadList()    // hàm tạo ra các loại threats
{
    std::vector<ThreatsObj*> list_threats;

// sinh quái động
    ThreatsObj* dynamic_threats = new ThreatsObj[50];
    for (int i = 0; i < 50; i++)
    {
        ThreatsObj* p_threat = (dynamic_threats + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("img//threat_left.png", g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObj::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(630 + i*500);
            p_threat->set_y_pos(200);             // rơi từ vị trí 200 xuống

            int pos1 = p_threat->get_x_pos() - 60;
            int pos2 = p_threat->get_x_pos() + 60;                // fix ngày 06/06/2022 lỗi chặn pos2
            p_threat->SetAnimationPos(pos1, pos2);
            p_threat->set_input_left(1);

            list_threats.push_back(p_threat);            // p_threat cùng trỏ tới tĩnh và động

        }
    }

// sinh quái tĩnh
//    ThreatsObj* threats_objs = new ThreatsObj[20];
//
//    for (int i = 0; i < 20; i++)
//    {
//        ThreatsObj* p_threat = (threats_objs + i);
//        if (p_threat != NULL)
//        {
//            p_threat->LoadImg("img//threat_level.png", g_screen);
//            p_threat->set_clips();
//            p_threat->set_x_pos(700 + i*1200);
//            p_threat->set_y_pos(250);
//            p_threat->set_type_move(ThreatsObj::STATIC_THREAT);
//            p_threat->set_input_left(0);
//
//
//            list_threats.push_back(p_threat);
//        }
//    }

    return list_threats;
}


int main(int argc, char* argv[])
{
    ImpTimer fps_timer;

    if (InitData() == false)
        return -1;

    if (LoadBackground() == false)
        return -1;

    bool exit_game = false;
    Uint32 high_scores = 0;
    while (!exit_game)
    {
        exit_game = true;


        GameMap game_map;
        game_map.LoadMap("map/map01.dat");
        game_map.LoadTiles(g_screen);

        MainObj p_player;
        p_player.LoadImg("img//player_right.png", g_screen);
        p_player.set_clips();

        ImgSp player_life;
        player_life.Init(g_screen);

        PlayerItem player_item1;
        player_item1.Init1(g_screen);
        PlayerItem player_item2;
        player_item2.Init2(g_screen);
        PlayerItem player_item3;
        player_item3.Init3(g_screen);


    //xử lí va chạm kết hợp animations của nhân vật khi va chạm
        ExplosionObj exp_main;
        bool mRet = exp_main.LoadImg("img//player_death.png", g_screen);
        if (!mRet) return -1;
        exp_main.set_clip();

        std::vector<ThreatsObj*> threats_list = MakeThreadList();

        int frame_exp_width = exp_main.get_width_frame();
        int frame_exp_height = exp_main.get_height_frame();

        int num_die = 0; // số mạng
        Uint32 final_scores = 0;

        //Text Show
        TextObj time_game; // thời gian
        time_game.SetColor(TextObj::WHITE_TEXT);

        TextObj mark_game; // điểm số
        mark_game.SetColor(TextObj::WHITE_TEXT);
        Uint32 mark_value = 0;

        TextObj item_game; // đếm
        item_game.SetColor(TextObj::WHITE_TEXT);

        TextObj life_game; // mạng
        life_game.SetColor(TextObj::WHITE_TEXT);

    //  âm thanh
        Mix_Chunk* chunkdie = Mix_LoadWAV("audio//die.wav");
        Mix_Chunk* chunkend = Mix_LoadWAV("audio//win.wav");

        Mix_Music* musicgame = Mix_LoadMUS("audio//musicgame.mp3");
        Mix_VolumeMusic(MIX_GAME);          // chỉnh âm lượng
        Mix_PlayMusic(musicgame, 1);  // phát nhạc nền

    // vòng lặp để chơi
        bool is_quit = false;
        TTF_Font* menu_font;
        menu_font = TTF_OpenFont("font/dlxfont.ttf", 25);
        if (menu_font == NULL) return -1;

        int ret_menu = SDLCommonFunc::ShowMenu(g_screen, menu_font);
        if (ret_menu == 1) is_quit = true;
        while (!is_quit)
        {
            fps_timer.start();
            while (SDL_PollEvent(&g_event) != 0)
            {
                if (g_event.type == SDL_QUIT)
                {
                    is_quit = true;
                }

                p_player.HandelInputAction(g_event, g_screen);
            }

            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);

            g_background.Render(g_screen, NULL);

            Map map_data = game_map.getMap();

            p_player.HandelBullet(g_screen, map_data);
            p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
            p_player.DoPlayer(map_data, mark_value);
            p_player.Show(g_screen);

            //show map
            game_map.SetMap(map_data);
            game_map.DrawMap(g_screen);

            //show mạng
            player_life.Show(g_screen);

            //show item
            player_item1.Show(g_screen);
            player_item1.SetPos(SCREEN_WIDTH*0.5 - 250, 8);
            player_item2.Show(g_screen);
            player_item2.SetPos(SCREEN_WIDTH*0.5 - 100, 8);
            player_item3.Show(g_screen);
            player_item3.SetPos(SCREEN_WIDTH*0.5 + 50, 8);


            //show threats
            for (int i = 0; i < threats_list.size(); i++)
            {
                ThreatsObj* p_threat = threats_list.at(i);
                if (p_threat != NULL)
                {
                    p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                    p_threat->ImpMoveType(g_screen);
                    p_threat->DoPlayer(map_data);
                    p_threat->Show(g_screen);

                    // xử lí va chạm player với threats
                    SDL_Rect rect_player = p_player.GetRectFrame(); // gọi ra các thông số về tọa độ (x,y,w,h) của 2 đối tượng
                    SDL_Rect rect_threat = p_threat->GetRectFrame();


                    bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat); // check
                    if (bCol2)
                    {

                        // chưa có xóa nhân vật
                        for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                        {

                            int x_pos = p_player.GetRect().x;
                            int y_pos = p_player.GetRect().y;

                            exp_main.set_frame(ex);
                            exp_main.SetRect(x_pos, y_pos);
                            SDL_Delay(1);
                            exp_main.Show(g_screen);
                            SDL_RenderPresent(g_screen);
                        }

                        num_die++;
                        if (num_die < 3)
                        {
                            p_player.SetRect(0, 0);
                            p_player.set_comeback_time(60);
                            Mix_PlayChannel(-1, chunkdie, 0);
                            SDL_Delay(1000);
                            player_life.Decrease();       // giảm mạng
                            player_life.Render(g_screen); // load lại màn hình
                            continue;

                        }
                        else
                        {
                            p_threat->Free();
                            close();
                            SDL_Quit();
                            return 0;
                        }
    //                    if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
    //                    {
    //                        p_threat->Free();
    //                        close();
    //                        SDL_Quit();
    //                        return 0;
    //                    }
                    }
                }
            }
            bool is_death = false;
            is_death = p_player.IsDeath(map_data, num_die);

            // xử lí mất mạng khi rơi xuống vực ở mảng Img
            if (is_death)
            {
    //            std::cout << num_die << std::endl; // check
                Mix_PlayChannel(-1, chunkdie, 0);
                SDL_Delay(1000);
                player_life.Decrease();
                player_life.Render(g_screen);
            }

    // xử lí va chạm bullet với threats
    std::vector<BulletObj*> bullet_arr = p_player.get_bullet_list();
            for (int r = 0; r < bullet_arr.size(); r++)
            {
                BulletObj* p_bullet = bullet_arr.at(r);
                if (p_bullet != NULL)
                {
                    for (int t = 0; t < threats_list.size(); t++)
                    {
                        ThreatsObj* obj_threat = threats_list.at(t);
                        if (obj_threat != NULL)
                        {

                            SDL_Rect tRect;
                            tRect.x = obj_threat->GetRect().x;
                            tRect.y = obj_threat->GetRect().y;
                            tRect.w = obj_threat->get_width_frame(); // vì sử dụng khung hình để load hiệu ứng động nên chỉ lấy ra cái khung hình width chuẩn
                            tRect.h = obj_threat->get_height_frame();

                            SDL_Rect bRect = p_bullet->GetRect();

                            bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

                            if (bCol)
                            {
                                mark_value += 5;
                                p_player.RemoveBullet(r);   // trước tiên đạn trúng thì phải xóa đạn
                                obj_threat->Free();         // xóa threat bị trúng đạn
                                threats_list.erase(threats_list.begin() + t);
                            }
                        }
                    }
                }
            }


     //Show thời gian
            std::string str_time = "Time: ";
            Uint32 time_val = SDL_GetTicks() / 1000;
            Uint32 val_time = 450 - time_val;
            if (val_time <= 0)
            {
                return 0;
            }
            else
            {
                std::string str_val = std::to_string(val_time);
                str_time += str_val;

                time_game.SetText(str_time);                            // đọc nội dung
                time_game.LoadFromRenderText(font_time, g_screen);      // Đọc chuyển nội dung sang font
                time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15); // show lên màn hình tại vị trí....
            }

    // Show điểm
            std::string val_str_mark = std::to_string(mark_value);
            std::string strMark("Mark: ");
            strMark += val_str_mark;

            mark_game.SetText(strMark);
            mark_game.LoadFromRenderText(font_time, g_screen);
            mark_game.RenderText(g_screen, SCREEN_WIDTH*0.5 + 250, 15);

    // Text mạng
            std::string strLife("Life: ");

            life_game.SetText(strLife);
            life_game.LoadFromRenderText(font_time, g_screen);
            life_game.RenderText(g_screen, 10, 20);

    // Show lượng item ăn được
            int item_count1 = p_player.GetItem1Count();
            std::string item_str1 = std::to_string(item_count1);

            item_game.SetText(item_str1);
            item_game.LoadFromRenderText(font_time, g_screen);
            item_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 200, 18);

            int item_count2 = p_player.GetItem2Count();
            std::string item_str2 = std::to_string(item_count2);

            item_game.SetText(item_str2);
            item_game.LoadFromRenderText(font_time, g_screen);
            item_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 50, 18);

            int item_count3 = p_player.GetItem3Count();
            std::string item_str3 = std::to_string(item_count3);

            item_game.SetText(item_str3);
            item_game.LoadFromRenderText(font_time, g_screen);
            item_game.RenderText(g_screen, SCREEN_WIDTH*0.5 + 100, 18);

            final_scores = mark_value + val_time;

            if (num_die >= 3 || item_count3 >= 3)
            {
                if (final_scores > high_scores)
                {
                    high_scores = final_scores;      // cập nhật điểm cao nhất
                }
                Mix_PlayChannel(-1, chunkend, 0);
                SDL_Delay(3000);
                break;
            }

            SDL_RenderPresent(g_screen);

            int real_imp_time = fps_timer.get_ticks();
            int time_one_frame = 1000/FRAME_PER_SECOND; // ms

            if (real_imp_time < time_one_frame)
            {
                int delay_time = time_one_frame - real_imp_time;
                if (delay_time >= 0)
                    SDL_Delay(delay_time);
            }
        }


    // tránh thừa bộ nhớ (xóa lớp threat sau khi xong)
        for (int i = 0; i < threats_list.size(); i++)
        {
            ThreatsObj* p_threats = threats_list.at(i);
            if (p_threats)
            {
                p_threats->Free();
                p_threats = NULL;
            }
        }
        threats_list.clear();

        bool ret_exit = SDLCommonFunc::ShowExit(g_screen, font_time, final_scores, high_scores);
        if (ret_exit == 0)
        {
            exit_game = false;
        }
    }
    close();
    return 0;
}



