
#ifndef MAINOBJ_H
#define MAINOBJ_H

#include <vector>                 // tạo 1 danh sách các viên đạn liên tục

#include "CommonFunction.h"
#include "BaseObj.h"
#include "BulletObj.h"

#define PLAYER_FRAME_NUM 8        // lượng frame được load
#define GRAVITY_SPEED 0.8         // tốc độ rơi
#define MAX_FAIL_SPEED 9          // tốc độ rơi tối đa
#define PLAYER_SPEED 3.5          // tốc độ chạy
#define PLAYER_JUMP_VAL 20        // giới hạn nhảy
#define PLAYER_BULLET 0.4         // vị trí viên đạn được bắn ra
#define BULLET_SPEED 12           // tốc độ đạn
#define DELAY_BULLET 10           // tốc độ bắn

class MainObj : public BaseObj
{
public:
    MainObj();
    ~MainObj();

    enum WalkType
    {
        WALK_NONE = 0,
        WALK_RIGHT = 1,
        WALK_LEFT = 2,
    };

    bool LoadImg(std::string path, SDL_Renderer* screen);   // hàm load ảnh
    void Show(SDL_Renderer* des);                           // hàm show ảnh
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen);  // hàm tương tác nhân vật từ bàn phím
    void set_clips();

    void DoPlayer(Map& map_data, Uint32 &mark_value); // hàm xử lí các hoạt động của nhân vật
    void CheckToMap(Map& map_data, Uint32 &mark_value);
    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;}  // cung cấp vị trí của map
    void CenterEntityOnMap(Map& map_data);   // tính toán ra thông số của map khi nhân vật di chuyển
    void UpdateImagePlayer(SDL_Renderer* des);  // update lại png của nhân vật và các animations
    bool IsDeath(Map& map_data, int &num_die);  // check map when player droped and decrease img health

    SDL_Rect GetRectFrame();

    void set_bullet_list(std::vector<BulletObj*> bullet_list)
    {
        p_bullet_list_ = bullet_list;
    }

    std::vector<BulletObj*> get_bullet_list() const {return p_bullet_list_;}
    void HandelBullet(SDL_Renderer* des, Map& map_data);
    void RemoveBullet(const int& idx);  // hàm xóa bullet khi va chạm
    void IncreaseItem1();  // hàm thu thập và đếm lượng item
    void IncreaseItem2();
    void IncreaseItem3();
    void set_comeback_time(const int& cb_time) {come_back_time = cb_time;}
    int GetItem1Count() const {return item_count1;}   // hàm lấy ra lượng item ăn được
    int GetItem2Count() const {return item_count2;}
    int GetItem3Count() const {return item_count3;}


private:

    int item_count1;    // biến đếm lượng vật phẩm ăn được
    int item_count2;
    int item_count3;
    std::vector<BulletObj*> p_bullet_list_;
    float x_val_;             // lượng thay đổi
    float y_val_;

    float x_pos_;             // tọa độ hiện tại
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[PLAYER_FRAME_NUM];
    Input input_type_;
    int frame_;
    int status_;
    bool on_ground_;

    int map_x_;
    int map_y_;

    int come_back_time;

    int delay_bullet;

    Mix_Chunk* chunkitem;     // biến âm thanh
    Mix_Chunk* chunkbullet;
    Mix_Chunk* chunkwin;
};

#endif // MAINOBJ_H
