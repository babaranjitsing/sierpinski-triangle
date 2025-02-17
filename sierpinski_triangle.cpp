#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Point {
    double x, y;
};

Point random_point_in_triangle(const Point &p1, const Point &p2, const Point &p3) {
    double r1 = (double) rand() / RAND_MAX;
    double r2 = (double) rand() / RAND_MAX;

    if (r1 + r2 > 1) {
        r1 = 1 - r1;
        r2 = 1 - r2;
    }

    Point p;
    p.x = r1 * p1.x + r2 * p2.x + (1 - r1 - r2) * p3.x;
    p.y = r1 * p1.y + r2 * p2.y + (1 - r1 - r2) * p3.y;
    return p;
}

SDL_Window* create_window(int width, int height) {
    SDL_Window* window = SDL_CreateWindow("Sierpinski Triangle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    return window;
}

void draw_points(SDL_Renderer* renderer, const std::vector<Point> &points, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    for (const auto &p : points) {
        SDL_RenderDrawPoint(renderer, static_cast<int>(p.x), static_cast<int>(p.y));
    }
}

bool check_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
            return false;
        }
    }
    return true;
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    const int width = 500, height = 500;
    SDL_Window* window = create_window(width, height);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Color background = {255, 255, 255, 255};
    SDL_Color foreground_black = {0, 0, 0, 255};

    std::vector<Point> points = {{250, 125}, {0, 375}, {500, 375}};
    std::vector<Point> new_points;

    Point random_point = random_point_in_triangle(points[0], points[1], points[2]);

    bool running = true;
    while (running) {
        running = check_events();

        Point random_vert = points[rand() % 3];
        Point mid_point = {(random_point.x + random_vert.x) / 2, (random_point.y + random_vert.y) / 2};
        new_points.push_back(mid_point);

        SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, 255);
        SDL_RenderClear(renderer);
        draw_points(renderer, new_points, foreground_black);
        SDL_RenderPresent(renderer);

        random_point = mid_point;
        //SDL_Delay(5);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
