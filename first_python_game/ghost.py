import pygame
from Coordinate_Check import speed

class ghost():

    def __init__(self):
            self.speed=speed()

            self.ball = pygame.image.load('ghost 1.gif')
            self.geometry = self.ball.get_rect()
            self.mode=1
            self.time=0

    def shift(self):
            self.geometry = self.geometry.move(self.speed)
            if self.geometry.left <= 0 or self.geometry.right >= 1200:
                self.speed = [0, 0]
            if self.geometry.top <= 0 or self.geometry.bottom >= 900:
                self.speed = [0, 0]
