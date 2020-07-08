import config

from pygame.rect import Rect
from pygame import draw
from text_object import TextObject


class GameObject:
    def __init__(self, x, y, w, h, speed=(0, 0)):
        self.type = None
        self.bounds = Rect(x, y, w, h)
        self.speed = speed

    @property
    def left(self):
        return self.bounds.left

    @property
    def right(self):
        return self.bounds.right

    @property
    def top(self):
        return self.bounds.top

    @property
    def bottom(self):
        return self.bounds.bottom

    @property
    def width(self):
        return self.bounds.width

    @property
    def height(self):
        return self.bounds.height

    @property
    def center(self):
        return self.bounds.center

    @property
    def centerx(self):
        return self.bounds.centerx

    @property
    def centery(self):
        return self.bounds.centery

    def draw(self, surface):
        pass

    def move(self, dx, dy):
        self.bounds = self.bounds.move(dx, dy)

    def update(self):
        if self.speed == [0, 0]:
            return

        self.move(*self.speed)


class MenuBackground(GameObject):
    def __init__(self, x, y, w, h, color, special_effect=None):
        GameObject.__init__(self, x, y, w, h)
        self.color = color
        self.special_effect = special_effect

    def draw(self, surface):
        draw.rect(surface, self.color, self.bounds)


class Button(GameObject):
    def __init__(self, x, y, w, h, text, button_type):
        super().__init__(x, y, w, h)
        self.type = button_type
        self.text = TextObject(x + 1, y + 10, lambda: text, config.BUTTON_TEXT_COLOR, config.BUTTON_FONT,
                               config.BUTTON_SIZE)

    def draw(self, surface):
        draw.rect(surface, config.BUTTON_COLOR, self.bounds)
        self.text.draw(surface)
