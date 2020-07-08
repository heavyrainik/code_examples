import pygame
import config
import text_object
import game_object


class GameGraphics:
    def __init__(self):
        self.background_image = pygame.image.load(config.background_image)
        self.background_image = pygame.transform.scale(self.background_image, (config.WIDTH, config.HEIGHT))
        self.screen = pygame.display.set_mode((config.WIDTH, config.HEIGHT))
        self.clock = pygame.time.Clock()
        self.frame_rate = config.FRAME_RATE

    @staticmethod
    def create_resource_label(menu_objects, resources):
        resource_label = text_object.TextObject(config.RESOURCE_X, config.RESOURCE_Y,
                                                lambda: f'RESOURCES: {resources}$',
                                                config.RESOURCE_COLOR, config.RESOURCE_FONT, config.RESOURCE_SIZE)
        menu_objects.append(resource_label)

    @staticmethod
    def create_menu_background(menu_objects):
        menu_background = game_object.MenuBackground(config.RECT_X, config.RECT_Y, config.RECT_WIDTH,
                                                     config.RECT_HEIGHT, config.RECT_COLOR)
        menu_objects.append(menu_background)

    @staticmethod
    def create_upgrade_buttons(menu_objects):
        button1 = game_object.Button(config.WIDTH * 4 / 6, config.BUTTON_Y, config.BUTTON_WIDTH, config.BUTTON_HEIGHT,
                                     config.BUTTON1_MESSAGE, config.BUTTON1_KEY)
        menu_objects.append(button1)

        button2 = game_object.Button(config.WIDTH * 5 / 6, config.BUTTON_Y, config.BUTTON_WIDTH, config.BUTTON_HEIGHT,
                                     config.BUTTON2_MESSAGE, config.BUTTON2_KEY)
        menu_objects.append(button2)

    def create_menu(self, menu_objects, resources):
        self.create_menu_background(menu_objects)
        self.create_resource_label(menu_objects, resources)
        self.create_upgrade_buttons(menu_objects)

    def draw(self, game_objects, menu_objects):
        self.screen.blit(self.background_image, (0, 0))

        for menu_object in menu_objects:
            menu_object.draw(self.screen)

        for game_object in game_objects:
            game_object.draw(self.screen)

        pygame.display.update()
        self.clock.tick(self.frame_rate)

    def draw_selected_part(self, start_pos, end_pos):
        pass
