#include <iostream>
#include <memory>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
constexpr int WIDTH = 1000, HEIGHT = 720, R = 25;

std::shared_ptr<SDL_Texture> icon;
std::shared_ptr<SDL_Texture> icon2;

std::shared_ptr<SDL_Texture> Make_icon(SDL_Renderer *renderer, const char *name)
{
	std::shared_ptr<SDL_Texture> picture = std::shared_ptr<SDL_Texture>(
			IMG_LoadTexture(renderer, name),
			SDL_DestroyTexture);
	if(picture == nullptr)
	{
		std::cerr << "Не могу загрузить картинку" <<
		SDL_GetError()<<std::endl;
		return nullptr;
	}
	return picture;
}
void DrawCircle(SDL_Renderer * ren, int x, int y, int r, int X, int Y)
{
            int delta = 1 - 2 * r;
            int error = 0;
            SDL_SetRenderDrawColor(ren, 255, 220, 0, 0);
            while(y >= 0)
            {
                SDL_RenderDrawPoint(ren, X + x, Y + y);
                SDL_RenderDrawPoint(ren, X + x, Y - y);
                SDL_RenderDrawPoint(ren, X - x, Y + y);
                SDL_RenderDrawPoint(ren, X - x, Y - y);
                error = 2 * (delta + y) - 1;
                if (delta < 0 and error <= 0)
                {
                    ++x;
                    delta += 2 * x + 1;
                    continue;
                }
                if (delta > 0 and error > 0)
                {
                    --y;
                    delta -= 2 * y + 1;
                    continue;
                }
                ++x;
                --y;
                delta += 2 * (x - y);
            }
}
int main(int, char **)
{
    std::cout << "Начало работы программы" << std::endl;
    SDL_Init(SDL_INIT_EVERYTHING);
    auto win = std::shared_ptr<SDL_Window>(
            SDL_CreateWindow("Home_Boiko",
                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                    WIDTH, HEIGHT,
                    SDL_WINDOW_SHOWN),
            SDL_DestroyWindow);
    if (win == nullptr) {
        std::cerr << "Ошибка при создании окна: " <<
                SDL_GetError() << std::endl;
        return 1;
    }
    auto ren = std::shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(win.get(), -1,
                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
            SDL_DestroyRenderer);
    if (ren == nullptr) {
        std::cerr << "Ошибка при создании рендерера: " <<
                SDL_GetError() << std::endl;
        return 1;
    }


	bool f = true;
	int icon_x = 90, icon_y = 40;// координаты где появиться летающий
	bool f2 = true;
	int icon_x2 = 500, icon_y2 = 600;// координаты где появится бегающий

	auto keys = SDL_GetKeyboardState(nullptr);

    SDL_Event event;
    bool finish = false;
    // Основной цикл программы
    while (not finish)
    {
        // Цикл обработки событий
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                finish = true;
        }
        //Фон
        SDL_SetRenderDrawColor(ren.get(), 0, 200, 250, 1);//Цвет в формате rgba
        SDL_RenderClear(ren.get());
        //Земля
        SDL_Rect r { 0, 525, WIDTH, 220 };
        SDL_SetRenderDrawColor(ren.get(), 0, 170, 70, 1);//Цвет в формате rgba
        SDL_RenderFillRect(ren.get(), &r);
        //забор
        SDL_SetRenderDrawColor(ren.get(), 143, 51, 21, 1);
        SDL_Rect rr2 {0, 490, 1000, 20 };
        SDL_RenderFillRect(ren.get(), &rr2);
        for (int i = 20; i < WIDTH; i += 100) {
        	SDL_SetRenderDrawColor(ren.get(), 179, 87, 0, 1);// палки на заборе
            SDL_Rect r1 { i, 450, 50, 100 };
            SDL_RenderFillRect(ren.get(), &r1);

            SDL_SetRenderDrawColor(ren.get(), 150, 60, 0, 1);// треугольник на заборе
            for (double x1 = i + 25, x2 = i + 25,  y = 425; y < 450; --x1, ++x2, y++)
            { SDL_RenderDrawLine(ren.get(), x1, y, x2, y);
            } }
        //дом
        SDL_Rect r1 { 500, 300, 400, 300 };
        SDL_SetRenderDrawColor(ren.get(), 225, 85, 50, 1);//Цвет в формате rgba
        SDL_RenderFillRect(ren.get(), &r1);
        //Окно
        SDL_Rect r2 { 525, 380, 100, 100 };
        SDL_SetRenderDrawColor(ren.get(), 181, 193, 250, 1);//внутри //Цвет в формате rgba
        SDL_RenderFillRect(ren.get(), &r2);

        SDL_SetRenderDrawColor(ren.get(), 0, 0, 0, 1);// палочки //Цвет в формате rgba
        SDL_RenderDrawLine(ren.get(), WIDTH / 2 + 75, 380, WIDTH / 2 + 75, 480);

        SDL_SetRenderDrawColor(ren.get(), 0, 0, 0, 1);// палочки //Цвет в формате rgba
        SDL_RenderDrawLine(ren.get(), WIDTH / 2 + 25, 430, WIDTH / 2 + 125, 430);

        SDL_Rect rw2 { 775, 380, 100, 100 };
        SDL_SetRenderDrawColor(ren.get(), 181, 193, 250, 1);//внутри //Цвет в формате rgba
        SDL_RenderFillRect(ren.get(), &rw2);

        SDL_SetRenderDrawColor(ren.get(), 0, 0, 0, 1);// палочки //Цвет в формате rgba
        SDL_RenderDrawLine(ren.get(), 825, 380, 825, 480);

        SDL_SetRenderDrawColor(ren.get(), 0, 0, 0, 1);// палочки //Цвет в формате rgba
        SDL_RenderDrawLine(ren.get(), 775, 430, 875, 430);

        //Труба
        SDL_Rect r3 { 550, 150, 40, 100 };
        SDL_SetRenderDrawColor(ren.get(), 50, 30, 30, 1);//Цвет в формате rgba
        SDL_RenderFillRect(ren.get(), &r3);
        //Крыша
        SDL_SetRenderDrawColor(ren.get(), 0, 50, 27, 1);//Цвет в формате rgba
        for (double x1 = 700, x2 = 700,  y = 150; y < 300; x1 -= 1.7, x2 += 1.7, y++) {
            SDL_RenderDrawLine(ren.get(), x1, y, x2, y);
        }
        //дверь
        SDL_Rect r4 { 650, 400, 100, 200 };
        SDL_SetRenderDrawColor(ren.get(), 59, 6, 12, 1);//Цвет в формате rgba
        SDL_RenderFillRect(ren.get(), &r4);
        //Трава
        SDL_SetRenderDrawColor(ren.get(), 0, 64, 0, 1);//Цвет в формате rgba
        for(int i = 0; i <= 50; i += 20)
            for (int x = 15 + i,  y1 = HEIGHT - i, y2 = HEIGHT - (i+50) ; x < WIDTH - 15; x += 50 )
                SDL_RenderDrawLine(ren.get(), x, y1, x, y2);

        //окружность
        for (int i = 50; i > 0; i--){
        	 DrawCircle(ren.get(), 0, i, i, 100, 100);
        }

		//Летающая птичка
		if (f)
			icon = Make_icon(ren.get(), "bird_p.png");
		else
			icon = Make_icon(ren.get(), "bird_l.png");

		if(keys[SDL_SCANCODE_RIGHT] and icon_x < WIDTH - 100){ icon_x += 6; f = true;}//тут и далее цифра 8 это скорость полета
		if(keys[SDL_SCANCODE_LEFT] and icon_x > 0 ){ icon_x -= 6; f = false;}
		if(keys[SDL_SCANCODE_UP] and icon_y > 0){ icon_y -= 6; }
		if(keys[SDL_SCANCODE_DOWN] and icon_y < HEIGHT - 50){ icon_y += 6; }

		if(icon == nullptr) return 1;
		SDL_Rect icon_rect {icon_x, icon_y, 50, 59};//тут предпоследние 2 числа это  ширина и высота картинки твоей
		SDL_RenderCopy(ren.get(), icon.get(), nullptr, &icon_rect);

		//бегающий пес
		if(icon_x2 < WIDTH - 150 and f2){
			icon2 = Make_icon(ren.get(), "dog_p.png");
			icon_x2 += 6;//скорость бега вправо
		}
		else f2 = false;
		if(icon_x2 > 0 and !f2){
			icon2 = Make_icon(ren.get(), "dog_l.png");
			icon_x2 -= 6;//скорость бега влево
		}
		else f2 = true;

		if(icon2 == nullptr) return 1;
		SDL_Rect icon_rect2 {icon_x2, icon_y2, 100, 93};//тут предпоследние 2 числа это  ширина и высота картинки твоей
		SDL_RenderCopy(ren.get(), icon2.get(), nullptr, &icon_rect2);

        SDL_RenderPresent(ren.get());
        }
        /*
         * Двойная буферизация:
         * 1 буфер (передний) - буфер, содержимое которого отображается.
         * 2 буфер (задний) - буфер, в котором осуществляется построение изображения.
         *
         */
        std::cout << "Конец работы программы" << std::endl;
        return 0;
}
