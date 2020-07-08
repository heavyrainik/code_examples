import pygame
from models.InfantryUnit import InfantryUnit
from models.CavalryUnit import CavalryUnit
from models.WizardUnit import WizardUnit
from models.SpecialUnit import SpecialUnit


class ElfInfantryUnit(InfantryUnit):
    def set_hp(self):
        return 90

    def __init__(self):
        self.image = pygame.image.load("images/elf_war1.png")
        self.image = pygame.transform.scale(self.image, (50, 70))
        self.speed = [0, -1]
        self.geometry = self.image.get_rect()
        self.geometry.y = 200
        self.geometry.x = 1000
        self.attack = 15


class ElfCavalryUnit(CavalryUnit):
    def set_hp(self):
        return 50

    def __init__(self):
        self.image = pygame.image.load("images/elf_cav1.jpg")
        self.image = pygame.transform.scale(self.image, (50, 70))
        self.speed = [0, -1]
        self.geometry = self.image.get_rect()
        self.geometry.y = 250
        self.geometry.x = 900
        self.attack = 30


class ElfWizardUnit(WizardUnit):
    def set_hp(self):
        return 90

    def __init__(self):
        self.image = pygame.image.load("images/elf_wiz1.png")
        self.image = pygame.transform.scale(self.image, (50, 70))
        self.speed = [0, -1]
        self.geometry = self.image.get_rect()
        self.geometry.y = 300
        self.geometry.x = 800
        self.attack = 20


class ElfSpecialUnit(SpecialUnit):
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
