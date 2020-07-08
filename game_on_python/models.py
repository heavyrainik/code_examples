import pygame
import config
import random

from game_object import GameObject


class Groupmate(GameObject):
    def __init__(self, x, groupmate_type, special_effect=None):
        super().__init__(x, config.GROUP_MATE_BIRTH, 0, 0)
        self.special_effect = special_effect
        self.speed = [0, -1]
        self.hp, self.value, self.image = self.define_type(groupmate_type)
        self.type = groupmate_type
        self.geometry = self.image.get_rect()
        self.geometry.y = config.GROUP_MATE_BIRTH
        self.geometry.x = x

    @staticmethod
    def define_type(groupmate_type):
        creep_type = 1
        value = creep_type
        hp = creep_type

        if groupmate_type == 1:
            hp = 3
            value = 100

        if groupmate_type == 2:
            hp = 1
            value = -50

        if groupmate_type == 3:
            creep_type = random.randint(1, config.MAX_AMOUNT_OF_SKINS)
            if creep_type != 4:
                hp = random.randint(2, 5)
                value = random.randint(-10, 10)
            else:
                hp = 1
                value = 45

        if groupmate_type == 4:
            hp = 1

        if groupmate_type == 5:
            hp = random.randint(30, 60)
            value = random.randint(-100, 100)

        if groupmate_type == 6:
            hp = 1
            print("nu tyt ya ughe hz che pridumat")

        image = pygame.image.load(config.IMAGES_DIRECTORY + "/" + str(groupmate_type) + str(creep_type) + ".png")
        image = pygame.transform.scale(image, (config.GROUP_MATE_WIDTH, config.GROUP_MATE_HEIGHT))
        return hp, value, image

    def draw(self, screen):
        screen.blit(self.image, self.geometry)

    def update(self):
        self.geometry.y += config.GROUP_MATE_Y_SPEED
        self.geometry.x -= 0
