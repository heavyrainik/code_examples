from abc import ABC, abstractmethod


class Unit(ABC):
    is_fighting = False
    @abstractmethod
    def set_hp(self) -> int:
        pass

    def draw(self, screen):
        screen.blit(self.image, self.geometry)

