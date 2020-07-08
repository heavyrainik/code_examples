import pygame

class pacman():

    def __init__(self):
        self.score=0
        self.speed = [0,0]
        self.ball = pygame.image.load('pacman-d5.gif')
        self.geometry=self.ball.get_rect()
        self.mode=0
        self.time=0

    def move_key(self, key):
        ms=3
        key = chr(key)
        if key == 'w':
            self.speed=[0,-ms]
        elif key == 's':
            self.speed = [0,ms]
        elif key == 'a':
            self.speed = [-ms,0]
        elif key == 'd':
            self.speed = [ms,0]

    def shift(self):
        self.geometry = self.geometry.move(self.speed)

        if self.geometry.left <= 0 or self.geometry.right >= 1200:
            self.speed=[0,0]
        if self.geometry.top <= 0 or self.geometry.bottom >= 900:
            self.speed=[0,0]

    def anim(self):
        ms=3

        if self.speed==[0,-ms]:
            self.ball = pygame.image.load('pacman-t5.gif')

        elif self.speed==[0,ms]:
            self.ball = pygame.image.load('pacman-d5.gif')

        elif self.speed==[-ms,0]:
            self.ball = pygame.image.load('pacman-l5.gif')

        else:
            self.ball = pygame.image.load('pacman-r5.gif')