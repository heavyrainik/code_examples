import pygame
from models.InfantryUnit import InfantryUnit
from models.CavalryUnit import CavalryUnit
from models.WizardUnit import WizardUnit
from models.SpecialUnit import SpecialUnit


class OrkInfantryUnit(InfantryUnit):
    def set_hp(self):
        return 250

    def __init__(self):
        self.image = pygame.image.load("images/ork_war1.jpg")
        self.image = pygame.transform.scale(self.image, (50, 70))
        self.speed = [0, -1]
        self.geometry = self.image.get_rect()
        self.geometry.y = 300
        self.geometry.x = 250
        self.attack = 25


class OrkCavalryUnit(CavalryUnit):
    def set_hp(self):
        return 200

    def __init__(self):
        self.image = pygame.image.load("images/ork_cav1.jpg")
        self.image = pygame.transform.scale(self.image, (50, 70))
        self.speed = [0, -1]
        self.geometry = self.image.get_rect()
        self.geometry.y = 400
        self.geometry.x = 250
        self.attack = 35


class OrkWizardUnit(WizardUnit):
    def set_hp(self):
        return 100

    def __init__(self):
        self.image = pygame.image.load("images/ork_wiz1.gif")
        self.image = pygame.transform.scale(self.image, (50, 70))
        self.speed = [0, -1]
        self.geometry = self.image.get_rect()
        self.geometry.y = 500
        self.geometry.x = 250
        self.attack = 10


class OrkSpecialUnit(SpecialUnit):
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
