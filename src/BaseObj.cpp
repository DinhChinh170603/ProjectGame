#include "BaseObj.h"

// hàm khởi tạo
BaseObj::BaseObj()
{
    p_object_ = NULL;    //
    rect_.x = 0;         // tọa độ của ảnh
    rect_.y = 0;         //
    rect_.w = 0;         //
    rect_.h = 0;         //
}

BaseObj::~BaseObj()
{
    Free(); // giải phóng
}

bool BaseObj::LoadImg(std::string path, SDL_Renderer* screen)
{
    Free(); // giúp xóa đối tượng baseobj trước và trỏ sang vùng nhớ mới (giúp xóa rác, tắt game đi nhanh hơn, tiết kiệm bộ nhớ)
    SDL_Texture* new_texture = NULL;

    SDL_Surface* load_surface = IMG_Load(path.c_str()); //đọc tấm ảnh từ đường dẫn rồi load lên màn hình
    if (load_surface != NULL) // ktra xem hàm có chạy không
    {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B)); // xóa background nhân vật với key rgb
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface); // biến new lưu thuộc tính và thông số của ảnh
        if (new_texture != NULL)
        {
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;
        }

        SDL_FreeSurface(load_surface);
    }

    p_object_ = new_texture;

    return p_object_ != NULL;
}

void BaseObj::Render(SDL_Renderer* des, const SDL_Rect* clip /* = NULL */)
{
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopy(des, p_object_, clip, &renderquad);
}

// giải phóng p_object
void BaseObj::Free()
{
    if (p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}


