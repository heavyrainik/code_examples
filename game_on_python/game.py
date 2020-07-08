import pygame
import core
import config
import models
import random
import numpy
import text_object
import game_object


class Clicker(core.Game):
    def __init__(self):
        core.Game.__init__(self, 'Тут надо бить Игоря!!', config.WIDTH, config.HEIGHT, config.BACKGROUND_IMAGE,
                           config.FRAME_RATE)
        self.amount_of_game_objects = 0
        self.columns = [i-i for i in range(config.COLUMN_COUNT)]
        self.score = config.STARTING_SCORE
        self.start_ticks = pygame.time.get_ticks()
        self.create_menu()

    def find_right_column(self, cur_time):
        column = random.randint(0, config.COLUMN_COUNT - 1)

        if cur_time - self.columns[column] >= 5:
            self.columns[column] = cur_time
            return column

        return -1

    def add_game_object(self, cur_time):
        if self.amount_of_game_objects < config.MAX_AMOUNT_OF_GAME_OBJECTS:
            column = self.find_right_column(cur_time)
            random_generator_of_groupmate_type = numpy.random.choice(config.GROUP_MATES_TYPES, 50,
                                                                     p=config.DROP_CHANCES)
            groupmate_type = random_generator_of_groupmate_type[random.randint(0, 49)]

            if column != -1:
                groupmate = models.Groupmate(column * config.COLUMN_WIDTH, groupmate_type)
                self.game_objects.append(groupmate)
                self.amount_of_game_objects += 1

    def check_if_object_out(self):
        for groupmate in self.game_objects:
            if groupmate.geometry.y >= config.GROUP_MATE_DEATH:
                self.game_objects.remove(groupmate)
                self.amount_of_game_objects -= 1
                self.score -= 5

                if self.score < 0:
                    self.score = 0

    def object_click_processing(self, x, y):
        for groupmate in self.game_objects:
            if groupmate.geometry.collidepoint(x, y):
                groupmate.hp -= 1

                if not groupmate.hp:
                    if groupmate.type == 4:
                        self.random_background_image()

                    self.score += groupmate.value

                    if self.score < 0:
                        self.score = 0

                    self.game_objects.remove(groupmate)
                    self.amount_of_game_objects -= 1

        for menu_object in self.menu_objects:
            if menu_object.bounds.collidepoint((x, y)):
                if menu_object.type == config.BUTTON1_KEY and self.score >= 1000:
                    self.score -= 1000
                    config.MAX_AMOUNT_OF_SKINS = 4
                    self.menu_objects.remove(menu_object)
                if menu_object.type == config.BUTTON2_KEY and self.score >= 250:
                    self.score -= 250
                    self.background_image = pygame.image.load(config.OPTIONAL_BACKGROUND_IMAGE)
                    self.background_image = pygame.transform.scale(self.background_image, (config.WIDTH, config.HEIGHT))
                    self.menu_objects.remove(menu_object)

    def create_score_label(self):
        score_label = text_object.TextObject(config.SCORE_X, config.SCORE_Y, lambda: f'SCORE: {self.score}',
                                             config.SCORE_COLOR, config.SCORE_FONT, config.SCORE_SIZE)
        self.menu_objects.append(score_label)

    def create_menu_background(self):
        menu_background = game_object.MenuBackground(config.RECT_X, config.RECT_Y, config.RECT_WIDTH,
                                                     config.RECT_HEIGHT, config.RECT_COLOR)
        self.menu_objects.append(menu_background)

    def create_upgrade_buttons(self):
        button1 = game_object.Button(config.WIDTH * 4 / 6, config.BUTTON_Y, config.BUTTON_WIDTH, config.BUTTON_HEIGHT,
                                     config.BUTTON1_MESSAGE, config.BUTTON1_KEY)
        self.menu_objects.append(button1)

        button2 = game_object.Button(config.WIDTH * 5 / 6, config.BUTTON_Y, config.BUTTON_WIDTH, config.BUTTON_HEIGHT,
                                     config.BUTTON2_MESSAGE, config.BUTTON2_KEY)
        self.menu_objects.append(button2)

    def create_menu(self):
        self.create_menu_background()
        self.create_score_label()
        self.create_upgrade_buttons()

    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.game_over = True

            if event.type == pygame.MOUSEBUTTONDOWN:
                if event.type == pygame.MOUSEBUTTONDOWN:
                    x, y = event.pos

                    self.object_click_processing(x, y)

                if event.button == 1:
                    pygame.draw.circle(self.screen, (225, 0, 50), event.pos, 20)

    def update(self):
        seconds = int((pygame.time.get_ticks() - self.start_ticks) / 1000)

        if seconds % random.randint(1, 50) == 0:
            self.add_game_object(seconds)

        super().update()

        self.check_if_object_out()

    def random_background_image(self):
        random_generator_of_images = numpy.random.choice(config.IMAGES_TYPES, 50, p=config.IMAGES_DROP_CHANCES)
        image_type = random_generator_of_images[random.randint(0, 49)]
        print(config.BACKGROUND_IMAGES[image_type])
        self.background_image = pygame.image.load(
            config.BACKGROUND_IMAGES_DIRECTORY + "/" + config.BACKGROUND_IMAGES[image_type])
        self.background_image = pygame.transform.scale(self.background_image, (config.WIDTH, config.HEIGHT))
