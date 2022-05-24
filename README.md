# --------❤️--------Report ProjectGame--------❤️---------

A. Thông tin sinh viên:
  
  *	Full name: Lưu Đình Chính  
  *	Faculty: Science and Technology (CN1) – Class: K66CD  
  *	Email address: 21020288@vnu.edu.vn  
  *	Phone number: 0816086988  
  *	IDE used: Code::Blocks 20.03
  
B. Hướng dẫn cài đặt:

  * Truy cập vào link: https://cutt.ly/qHMn3yw hoặc chọn Code<màu xanh> rồi chọn Download ZIP
  * Tải file .rar về và giải nén
  * Truy cập theo thứ tự: ProjectGame >> bin >> Debug >> test1

C. Mô tả chung về trò chơi:

  * Tên trò chơi: MISERABLE DOG (dịch ra là "Chú chó đáng thương").
  <img width="400" alt="Demo1" src="https://user-images.githubusercontent.com/96640478/170040667-82866042-3178-4d75-9884-0081f1729cba.png">
   
  * Mô tả: Miserable Dog có thể nói là một tựa game phiêu lưu vô cùng quen thuộc đối với trẻ em hay chính tuổi thơ của mỗi chúng ta. Nó bắt nguồn từ một tựa game vô cùng nổi tiếng có tên Mario đã ra mắt từ những năm 2000.
  * Các ý tưởng chính:
    - Lối chơi: Người chơi sẽ điều khiển nhân vật chính là chú cún. Mục tiêu của trò chơi là tư duy, khéo léo vượt qua mọi địa hình, sống sót trước quái vật biến dị và trở về nơi mình thuộc về. Người chơi sẽ di chuyển nhân vật từ bên trái màn hình sang bên phải màn hình để đi đến được đích ở cuối map. 
    - Thế giới trong trò chơi có rải các ổ bánh mì, thịt dọc đường để chú cún có thể ăn, cộng 10 điểm cho 1 ổ bánh mì và 20 điểm với 1 miếng thịt. Bên cạnh những vật phẩm tốt là những vật phẩm xấu (túi độc) được đặt kèm buộc người chơi phải thật khéo léo và tư duy để có thể né tránh và ăn được bánh mì, thịt.... (Lưu ý: đừng để chú cún của mình ăn tới 3 gói độc lận nhé! Bởi bạn không chỉ mất 10 điểm mà chú cún sẽ chết và bạn sẽ thua đấy!). Người chơi được cho sẵn một số "mạng" nhất định, chú cún sẽ mất mạng nếu bị hại quá nhiều lần như rơi xuống hố, va chạm với quái vật hoặc hết giờ; trò chơi kết thúc khi không còn mạng nào. Đòn tấn công chính của chú cún chính là ném xương về phía trước mặt để tiêu diệt quái vật biến dị, cộng 5 điểm với mỗi quái vật bị hạ.
<img width="600" alt="Demo2" src="https://user-images.githubusercontent.com/96640478/170085256-dc44cedf-e279-4eb3-9f98-7f33ecfc54b2.png">


D. Các chức năng của game:

  * Menu:
    - Game có main menu với giao diện hài hòa, đơn giản nhưng mang đầy sự tinh tế.
    - Chọn Play Game để vào trò chơi, Exit để thoát trò chơi.
  * Mixer:
    - Music: nhạc nền của game chill, du dường, đầy tính thử thách...
    - SFX: tiếng nhân vật ăn được item, tiếng rơi xuống hố, tiếng va chạm với quái, tiếng đạn bắn, tiếng win game, tiếng lose game.
  * Display:
    - Mạng của nhân vật được hiển thị ở phía trên góc trái màn hình, kế tiếp số lượng item ăn được, điểm số và thời gian còn lại.
    - Màn hình gồm có nhân vật, map, background,...
  * Remote:
    - Ấn W để nhảy, A để di chuyển sang trái, D để di chuyển sang phải, J để ném xương.
  * Class:
    - CommonFunction: Dùng setup các thông số màn hình, fps, các biến nền tảng-cố định, xóa background cho nhân vật. Set up các hàm Show menu, exit, check va chạm giữa 2 đối tượng.
    - ImpTimer: Xử lí các vấn đề thời gian.
    - ImpSp: Xử lí các hình ảnh hỗ trợ như sinh mạng, item.
    - TextObj: Xử lí việc đọc, load, render các text lên màn hình.
    - Map: Sử dụng Kỹ thuật Tile Map(đọc từ file), xử lí màn hình di chuyển theo nhân vật.
    - BaseObj: Khởi tạo các hàm như đọc file ảnh, render lên màn hình.
    - MainObj: Xử lí các animations, tọa độ, xử lí toàn bộ các events của nhân vật như các keys thao tác từ bàn phím, va chạm với map, với quái, item, rơi xuống hố chết, đạn bắn,...
    - BulletObj: Xử lí các vấn đề về chức năng đạn bắn, giới hạn đường đạn.
    - ThreatsObj: Xử lí các vấn đề liên quan tới đối tượng quái vật như ảnh, animations, các chức năng đều kế thừa từ MainObj.
    - ExplosionObj: Xử lí vấn đề va chạm như nhân vật va chạm với quái
  * Link demo: ....


 E. Các kỹ thuật lập trình:
 
  * Sử dụng 4 thư viện: SDL2, SDL2_image, SDL2_ttf, SDL2_mixer.
  * Xây dựng tuần tự cấu trúc, khởi tạo rồi đến các lớp,...
  * Mảng: Dùng Vector, cấp phát mảng động để quản lí các lớp như bullet, threats.
  * Các biến: quản lí bằng con trỏ, truyền tham chiếu, truyền tham trị,...
  * Xử lí các thao tác từ bàn phím KeyButtondown...
  * Xử lí text: Đọc text, render sang dạng font, hiển thị lên màn hình
  * Xử lí ảnh: Đọc đường dẫn ảnh, load lên màn hình khi cần thiết
  * Xử lí sound: Đọc đường dẫn sound, load sound khi cần thiết
  * Giải phóng, tiết kiệm bộ nhớ, tránh tràn data,...

F. Tổng kết:

  1. Kết luận
  2. Tâm đắc
  3. Hướng phát triển
  * Tạo thêm nhiều màn chơi với đa dạng các loại map, item, đạn, quái, boss...
  * Nâng mức độ khó của game: Màn hình trôi liên tục khiến người chơi phải suy nghĩ và xử lí nhanh, threats có đạn bắn về 2 phía, threats tấn công bất thường, giới hạn đạn bắn của nhân vật,....




