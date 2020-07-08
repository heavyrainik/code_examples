import pygame
from models.InfantryUnit import InfantryUnit
from models.CavalryUnit import CavalryUnit
from models.WizardUnit import WizardUnit
from models.SpecialUnit import SpecialUnit


class HumanInfantryUnit(InfantryUnit):
    def set_hp(self):
        return 100

    def __init__(self):
        self.image = pygame.image.load("images/hum_war1.png")
        self.image = pygame.transform.scale(self.image, (50, 70))
        self.speed = [0, -1]
        self.geometry = self.image.get_rect()
        self.geometry.y = 350
        self.geometry.x = 900
        self.attack = 20


class HumanCavalryUnit(CavalryUnit):
    def set_hp(self):
        return 150

    def __init__(self):
        self.image = pygame.image.load("images/hum_cav1.jpg")
        self.image = pygame.transform.scale(self.image, (50, 70))
        self.speed = [0, -1]
        self.geometry = self.image.get_rect()
        self.geometry.y = 450
        self.geometry.x = 850
        self.attack = 25


class HumanWizardUnit(WizardUnit):
    def set_hp(self):
        return 50

    def __init__(self):
        self.image = pygame.image.load("images/hum_wiz1.jpg")
        self.image = pygame.transform.scale(self.image, (50, 70))
        self.speed = [0, -1]
        self.geometry = self.image.get_rect()
        self.geometry.y = 500
        self.geometry.x = 900
        self.attack = 35


class HumanSpecialUnit(SpecialUnit):
    def set_hp(self):
        pass

    def set_speed(self):
        pass

    def __init__(self):
        self.image = pygame.image.load("images/dem_wiz1.gif")
        self.image = pygame.transform.scale(self.image, (50, 70))
        self.speed = [0, -1]
        self.geometry = self.image.get_rect()
        self.geometry.y = 0
        self.geometry.x = 0
