import pygame
import backgen
import Game
from RecordTable import HoG

class Button:
    Amount = 0

    # --- создание поверхности конпки ---
    def __init__(self, x, y, width, height, text):

        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.text = text

        pygame.font.init()
        Font = pygame.font.SysFont("Calibri", height)

        self.ButtonNormally = pygame.Surface((width, height))
        self.ButtonNormally.fill((30, 55, 100))
        self.TextNormally = Font.render(text, 1, (5, 5, 5))
        self.ButtonNormally.blit(self.TextNormally, (50, 25))

        self.ButtonTargeted = pygame.Surface((width, height))
        self.ButtonTargeted.fill((160, 85, 30))
        self.TextTargeted = Font.render(text, 1, (20, 20, 20))
        self.ButtonTargeted.blit(self.TextTargeted, (30, 20))

        self.rect = pygame.Rect(x, y, width, height)

        self.Amount += 1

    # --- отрисовка кнопки ---
    def show_button(self, surface):

        if self.pressed() == False:
            ButtonMode = self.ButtonNormally
        else:
            ButtonMode = self.ButtonTargeted

        surface.blit(ButtonMode, (self.x, self.y))

    # --- проверка наведения курсора ---
    def pressed(self):
        mouse = pygame.mouse.get_pos()
        if mouse[0] > self.rect.topleft[0]:
            if mouse[1] > self.rect.topleft[1]:
                if mouse[0] < self.rect.bottomright[0]:
                    if mouse[1] < self.rect.bottomright[1]:
                        return True
                    else:
                        return False
                else:
                    return False
            else:
                return False
        else:
            return False

def Main_Menu():

    bg_color = (15, 40, 15)
    size = [1200, 900]

    screen = pygame.display.set_mode(size)
    w_close = False

    buttons = [Button(300, 100, 600, 175, "START"),
               Button(300, 325, 600, 175, "SCORES")]

    pygame.init()
    while not w_close:
        # --- отрисовка картинки ---
        screen.fill(bg_color)

        for i in range(len(buttons)):
            buttons[i].show_button(screen)

        # --- смена кадра ---
        pygame.display.flip()
        pygame.time.Clock().tick(60)

        # --- обработка событий ---
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                w_close = True
            if event.type == pygame.MOUSEBUTTONUP:
                buttons_state = [buttons[i].pressed() for i in range(len(buttons))]
                if buttons_state[0] == True:
                    # --- Levels ---
                    w_close = True
                    Levels_Menu()
                if buttons_state[1] == True:
                    # --- Scoreboard ---
                    w_close = True
                    HoG()

    pygame.quit()


def Levels_Menu():
    bg_color = (15, 40, 15)
    size = [1200, 900]

    screen = pygame.display.set_mode(size)
    w_close = False

    buttons = [Button(100, 100, 450, 150, "Back"),
               Button(100, 300, 450, 150, "Level 1"),
               Button(100, 500, 450, 150, "Level 2"),
               Button(100, 700, 450, 150, "Level 3")]

    pygame.init()
    while not w_close:
        # --- отрисовка картинки ---
        screen.fill(bg_color)

        for i in range(len(buttons)):
            buttons[i].show_button(screen)

        # --- смена кадра ---
        pygame.display.flip()
        pygame.time.Clock().tick(60)

        # --- обработка событий ---
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                w_close = True
            if event.type == pygame.MOUSEBUTTONUP:
                buttons_state = [buttons[i].pressed() for i in range(len(buttons))]

                if buttons_state[0] == True:
                    # --- Back ---
                    w_close = True
                    Main_Menu()

                if buttons_state[1] == True:
                    # --- Level 1 ---
                    w_close = True
                    pygame.quit()
                    np=backgen.backgen(1)
                    Game.game(np,1)

                if buttons_state[2] == True:
                    # --- Level 2 ---
                    w_close = True
                    pygame.quit()
                    np=backgen.backgen(2)
                    Game.game(np,2)

                if buttons_state[3] == True:
                    # --- Level 3 ---
                    w_close = True
                    pygame.quit()
                    np=backgen.backgen(3)
                    Game.game(np,3)

    pygame.quit()

Main_Menu()
