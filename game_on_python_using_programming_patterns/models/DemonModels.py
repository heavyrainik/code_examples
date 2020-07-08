import pygame
from models.InfantryUnit import InfantryUnit
from models.CavalryUnit import CavalryUnit
from models.WizardUnit import WizardUnit
from models.SpecialUnit import SpecialUnit


class DemonInfantryUnit(InfantryUnit):
    def set_hp(self):
        return 150

    def __init__(self):
        self.image = pygame.image.load("images/dem_war1.png")
        self.image = pygame.transform.scale(self.image, (50, 70))
        self.speed = [0, -1]
        self.geometry = self.image.get_rect()
        self.geometry.y = 110
        self.geometry.x = 500
        self.attack = 35

class DemonCavalryUnit(CavalryUnit):
    def set_hp(self):
        return 200

    def __init__(self):
        self.image = pygame.image.load("images/dem_cav1.jpg")
        self.image = pygame.transform.scale(self.image, (50, 70))
        self.speed = [0, -1]
        self.geometry = self.image.get_rect()
        self.geometry.y = 110
        self.geometry.x = 600
        self.attack = 10


class DemonWizardUnit(WizardUnit):
    def set_hp(self):
        return 100

    def __init__(self):
        self.image = pygame.image.load("images/dem_wiz1.gif")
        self.image = pygame.transform.scale(self.image, (50, 70))
        self.speed = [0, -1]
        self.geometry = self.image.get_rect()
        self.geometry.y = 110
        self.geometry.x = 700
        self.attack = 15


class DemonSpecialUnit(SpecialUnit):
    def set_hp(self):
        pass

    def set_speed(self):
        pass

    def __init__(self):
        self.image = pygame.image.load("images/dem_wiz1.gif")
        self.image = pygame.transform.scale(self.image, (50, 70))
        self.speed = [0, -1]
        self.geometry = self.image.get_rect()
        self.geometry.y = 00
        self.geometry.x = 00
