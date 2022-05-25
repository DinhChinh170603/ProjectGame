
#include "CommonFunction.h"
#include "BaseObj.h"
#include "TextObj.h"

// Show menu
int SDLCommonFunc::ShowMenu(SDL_Renderer* des, TTF_Font* font, Uint32 &time_menu) // truyền vào screen và font
{
    BaseObj Menu;
    bool ret_menu = Menu.LoadImg("img//menu.png", des); // Load ảnh vào file

    const int kMenuItemNum = 2;

    TextObj text_menu[kMenuItemNum];

    text_menu[0].SetText("Play Game");
    text_menu[0].SetColor(TextObj::WHITE_TEXT);          // set màu
    text_menu[0].rect_.x = 540;                          // tọa độ hiển thị
    text_menu[0].rect_.y = 410;                          //
    text_menu[0].LoadFromRenderText(font, des);          // Load text sang font
    text_menu[0].rect_.h = text_menu[0].GetHeight();
    text_menu[0].rect_.w = text_menu[0].GetWidth();

    text_menu[1].SetText("Exit");
    text_menu[1].SetColor(TextObj::WHITE_TEXT);
    text_menu[1].rect_.x = 540;
    text_menu[1].rect_.y = 460;
    text_menu[1].LoadFromRenderText(font, des);
    text_menu[1].rect_.h = text_menu[0].GetHeight();
    text_menu[1].rect_.w = text_menu[0].GetWidth();

    bool selected[kMenuItemNum] = {0, 0};
    int xm = 0, ym = 0;
    SDL_Event m_event;

    while(1)
    {
        SDL_RenderClear(des);
        Menu.Render(des, NULL);
        for (int i = 0; i < kMenuItemNum; i++)
        {
            text_menu[i].LoadFromRenderText(font, des);
            text_menu[i].RenderText(des, text_menu[i].rect_.x, text_menu[i].rect_.y);
        }
        while (SDL_PollEvent(&m_event))
        {
            time_menu = SDL_GetTicks();   // đếm thời gian ở trong menu
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
                {
                    xm = m_event.motion.x;
                    ym = m_event.motion.y;

                    for (int i = 0; i < kMenuItemNum; i++)
                    {
                        if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
                        {
                            if (selected[i] == false)
                            {
                                selected[i] = 1;
                                text_menu[i].SetColor(TextObj::RED_TEXT);
                            }
                        }
                        else
                        {
                            if (selected[i] == true)
                            {
                                selected[i] = 0;
                                text_menu[i].SetColor(TextObj::WHITE_TEXT);

                            }
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    xm = m_event.button.x;
                    ym = m_event.button.y;

                    for (int i = 0; i< kMenuItemNum; i++)
                    {
                        if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
                        {
                            return i;
                        }
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 1;
                }
            default:
                break;
            }
        }
        SDL_RenderPresent(des);
    }

    return 0;
}

int SDLCommonFunc::ShowExit(SDL_Renderer* des, TTF_Font* font, Uint32 scores_last, Uint32 high_scores)
{
    BaseObj Exit;
    TTF_Font* title_font = TTF_OpenFont("font//dlxfont.ttf", 50);
    TTF_Font* title_font2 = TTF_OpenFont("font//dlxfont.ttf", 40);

    bool ret_Exit = Exit.LoadImg("img//backtomenu.png", des);     // load ảnh kết thúc game

    if (!ret_Exit) return -1;

    const int kExitItemNum = 2;     // số lượng text muốn hiển thị

    TextObj text_Exit[kExitItemNum], title, scores, high_scr;

    std::string scores_txt = std::to_string(scores_last);
    scores.SetText(scores_txt);
    scores.SetColor(TextObj::WHITE_TEXT);

    title.SetText("Your scores: ");
    title.SetColor(TextObj::WHITE_TEXT);

    std::string high_scores_txt = "High scores: ";
    high_scores_txt += std::to_string(high_scores);
    high_scr.SetText(high_scores_txt);
    high_scr.SetColor(TextObj::WHITE_TEXT);


    text_Exit[0].SetText("Back To Menu");                       // Nhập text
    text_Exit[0].SetColor(TextObj::WHITE_TEXT);                 // Set màu cho Text
    text_Exit[0].rect_.x = 600;                                 // tọa độ của texgt
    text_Exit[0].rect_.y = 480;                                 //
    text_Exit[0].LoadFromRenderText(title_font2, des);          // chuyển text đọc được sang dạng font
    text_Exit[0].rect_.h = text_Exit[0].GetHeight();            // lưu lại độ rộng và độ cao của text để sau checkfocus
    text_Exit[0].rect_.w = text_Exit[0].GetWidth();             //

    text_Exit[1].SetText("Exit");
    text_Exit[1].SetColor(TextObj::WHITE_TEXT);
    text_Exit[1].rect_.x = 600;
    text_Exit[1].rect_.y = 530;
    text_Exit[1].LoadFromRenderText(title_font2, des);
    text_Exit[1].rect_.h = text_Exit[0].GetHeight();
    text_Exit[1].rect_.w = text_Exit[0].GetWidth();

    bool selected[kExitItemNum] = {0, 0};   // khởi tạo 2 giá trị false tương ứng với 2 check
    int xm = 0, ym = 0;          // khởi tạo tọa độ của chuột
    SDL_Event m_event;

    while(1)
    {

        SDL_RenderClear(des);
        Exit.Render(des, NULL);

        title.LoadFromRenderText(title_font, des);
        title.RenderText(des, 300, 50);                   // tọa độ để render "Score: "
        scores.LoadFromRenderText(title_font, des);
        scores.RenderText(des, 500, 150);                 // tọa độ để render điểm đạt được ra màn hình
        high_scr.LoadFromRenderText(title_font2, des);
        high_scr.RenderText(des, 300, 280);               // tọa độ để render điểm cao nhất qua các lần chơi ra màn hình

        for (int i = 0; i < kExitItemNum; i++)
        {
            text_Exit[i].LoadFromRenderText(font, des);      // load và render 2 text lên màn hình
            text_Exit[i].RenderText(des, text_Exit[i].rect_.x, text_Exit[i].rect_.y);
        }
        while (SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:    // di chuột
                {
                    xm = m_event.motion.x;
                    ym = m_event.motion.y;

                    for (int i = 0; i < kExitItemNum; i++)
                    {
                        if (CheckFocusWithRect(xm, ym, text_Exit[i].GetRect()))
                        {
                            if (selected[i] == false) // nếu đang ở ngoài
                            {
                                selected[i] = 1;
                                text_Exit[i].SetColor(TextObj::RED_TEXT);

                            }
                        }
                        else
                        {
                            if (selected[i] == true)   // nếu đang ở trong
                            {
                                selected[i] = 0;
                                text_Exit[i].SetColor(TextObj::WHITE_TEXT);

                            }
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    xm = m_event.button.x;
                    ym = m_event.button.y;

                    for (int i = 0; i < kExitItemNum; i++)
                    {
                        if (CheckFocusWithRect(xm, ym, text_Exit[i].GetRect()))
                        {
                            return i;
                        }
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 1;
                }
            default:
                break;
            }
        }
        SDL_RenderPresent(des);
    }
    return 0;
}

bool SDLCommonFunc::CheckFocusWithRect(const int &x, const int &y, const SDL_Rect& rect)
{
    if (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h)  // kiểm tra tọa độ của chuột với tọa độ của text
    {
        return true;
    }
    return false;
}


// set kiểm tra va chạm giữa 2 đối tượng
bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2) // truyền vào tọa độ của 2 đối tượng
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

// Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {

            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

// Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {

            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

// Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }
    return false;
}
