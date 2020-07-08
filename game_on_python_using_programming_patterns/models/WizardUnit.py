from abc import ABC, abstractmethod
from models.Unit import Unit


class WizardUnit(Unit):
    def set_speed(self):
        return 10

