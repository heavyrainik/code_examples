import pygame


class Cursor:
    is_active = False
    rect = pygame.Rect((0, 0, 0, 0))

    def __init__(self):
        self.is_active = False
        self.rect.x = 0
        self.rect.y = 0
        self.rect.h = 0
        self.rect.w = 0
        self.starting_pos = (0, 0)

    def start_selection(self, pos):
        self.is_active = True
        self.rect.x = pos[0]
        self.rect.y = pos[1]
        self.rect.h = 1
        self.rect.w = 1
        self.starting_pos = pos

    def finish_selection(self):
        self.is_active = False
        return self.starting_pos

    def get_current_state(self):
        return self.is_active

    def proceed_selection(self, mouse_pos):
        starting_pos = self.finish_selection()

        left_top_point = (min(starting_pos[0], mouse_pos[0]), min(starting_pos[1], mouse_pos[1]))
        right_bottom_point = (max(starting_pos[0], mouse_pos[0]), max(starting_pos[1], mouse_pos[1]))

        return left_top_point, right_bottom_point
