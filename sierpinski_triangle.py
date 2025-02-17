import pygame
import random

def random_point_in_triangle(p1, p2, p3):
    r1 = random.random()
    r2 = random.random()

    if r1 + r2 > 1:
        r1 = 1 - r1
        r2 = 1 - r2

    x = r1 * p1[0] + r2 * p2[0] + (1 - r1 - r2) * p3[0]
    y = r1 * p1[1] + r2 * p2[1] + (1 - r1 - r2) * p3[1]

    return (x, y)

def create_window(width, height):
    window = pygame.display.set_mode((width, height))
    pygame.display.set_caption("Sierpinski Triangle")

    return window

def check_events():
    window.fill(back_ground)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            return False
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                return False

    return True

def draw_points(points, color):
    for p in points:
        pygame.draw.circle(window, color, ((p[0]), p[1]), 1)

if __name__ == "__main__":
    pygame.init()

    width, height = 500, 500

    window = create_window(width, height)
    back_ground = (255, 255, 255)
    fore_ground_red = (255, 0, 0)
    fore_ground_black = (0, 0, 0)

    points = [(250, 125), (0, 375), (500, 375)]
    new_points = []

    origin_point = random_point_in_triangle(*points)

    while check_events():
        random_vert = random.choice(points)
        mid_point = ((origin_point[0] + random_vert[0]) / 2, (origin_point[1] + random_vert[1]) / 2)
        new_points.append(mid_point)
        origin_point = mid_point

        draw_points(new_points, fore_ground_black)

        pygame.display.update()

    pygame.quit()
