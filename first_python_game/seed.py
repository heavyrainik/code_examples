import pygame

class seed():
    def __init__(self):
        self.speed = [0, 0]
        self.ball = pygame.image.load('pellet.gif')
        self.geometry = self.ball.get_rect()
        self.mode = 0