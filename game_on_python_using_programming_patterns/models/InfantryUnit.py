from abc import ABC, abstractmethod
from models.Unit import Unit


class InfantryUnit(Unit):
    def set_speed(self):
        return 5

