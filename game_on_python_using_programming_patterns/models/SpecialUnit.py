from abc import ABC, abstractmethod
from models.Unit import Unit


class SpecialUnit(Unit):
    @abstractmethod
    def set_speed(self) -> int:
        pass

