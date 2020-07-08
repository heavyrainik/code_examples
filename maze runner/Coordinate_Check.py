from math import hypot
import pygame
import random

def speed():
    ms=2
    s = random.randint(1, 4)
    if s == 1:
        speed = [0, ms]
    if s == 2:
        speed = [0, -ms]
    if s == 3:
        speed = [ms, 0]
    if s == 4:
        speed = [-ms, 0]

    return speed

def coordinate_check(pl,en):
    x1=pl.geometry.x
    y1=pl.geometry.y

    x2=en.geometry.x
    y2=en.geometry.y

    if hypot(x2-x1,y2-y1)<28:
        if pl.mode==2:
            en.mode=0
            en.time=60
            pl.score+=100
            en.ball = pygame.image.load('glasses.gif')
        else:
            pl.mode=-1

    return pl,en

def check_seed(pl,en):
    x1 = pl.geometry.x
    y1 = pl.geometry.y

    x2 = en.geometry.x
    y2 = en.geometry.y

    if hypot(x2 - x1, y2 - y1) < 15:
        if en.mode==1:
            en.mode=0
            pl.score+=10

        elif en.mode==2:
            en.mode=0
            pl.score+=30
            pl.mode=2
            pl.time=random.randint(30,50)

    return pl,en


    return pl,en

def check_wall(pl,lvl):
    ms=2

    x1 = pl.geometry.x+15
    y1 = pl.geometry.y+15

    x = x1 // 30
    y = y1 // 30


    if lvl[y*40+x]==1:
        if pl.speed==[0,ms]:
            if lvl[y * 40 + x - 40] != 1:
                pl.geometry.y -= 10
                pl.speed = speed()

            elif lvl[y * 40 + x - 1] != 1:
                pl.geometry.x -= 10
                pl.speed = speed()

            elif lvl[y * 40 + x + 1] != 1:
                pl.geometry.x += 10
                pl.speed = speed()

            elif lvl[y * 40 + x + 40] != 1:
                pl.geometry.y += 10
                pl.speed = speed()
            else:
                pl.speed = [0, 0]

        if pl.speed==[0,-ms]:
            if lvl[y * 40 + x + 40] != 1:
                pl.geometry.y += 10
                pl.speed = speed()

            elif lvl[y * 40 + x - 40] != 1:
                pl.geometry.y -= 10
                pl.speed = speed()

            elif lvl[y * 40 + x - 1] != 1:
                pl.geometry.x -= 10
                pl.speed = speed()

            elif lvl[y * 40 + x + 1] != 1:
                pl.geometry.x += 10
                pl.speed = speed()

            else:
                pl.speed = [0, 0]

        if pl.speed==[ms,0]:
            if lvl[y * 40 + x - 1] != 1:
                pl.geometry.x -= 10
                pl.speed = speed()

            elif lvl[y * 40 + x - 40] != 1:
                pl.geometry.y -= 10
                pl.speed = speed()

            elif lvl[y * 40 + x + 1] != 1:
                pl.geometry.x += 10
                pl.speed = speed()

            elif lvl[y * 40 + x + 40] != 1:
                pl.geometry.y += 10
                pl.speed = speed()
            else:
                pl.speed = [0, 0]

        if pl.speed==[-ms,0]:
            if lvl[y * 40 + x + 1] != 1:
                pl.geometry.x += 10
                pl.speed = speed()

            elif lvl[y * 40 + x - 40] != 1:
                pl.geometry.y -= 10
                pl.speed = speed()

            elif lvl[y * 40 + x - 1] != 1:
                pl.geometry.x -= 10
                pl.speed = speed()

            elif lvl[y * 40 + x + 40] != 1:
                pl.geometry.y += 10
                pl.speed = speed()
            else:
                pl.speed = [0, 0]

    return pl

def check_wall_pac(pl,lvl):
    ms=3

    x1 = pl.geometry.x+15
    y1 = pl.geometry.y+15

    x = x1 // 30
    y = y1 // 30


    if lvl[y*40+x]==1:
        if pl.speed==[0,ms]:
            if lvl[y * 40 + x - 40] != 1:
                pl.geometry.y -= 10
                pl.speed = [0,0]

            elif lvl[y * 40 + x - 1] != 1:
                pl.geometry.x -= 10
                pl.speed = [0,0]

            elif lvl[y * 40 + x + 1] != 1:
                pl.geometry.x += 10
                pl.speed = [0,0]

            elif lvl[y * 40 + x + 40] != 1:
                pl.geometry.y += 10
                pl.speed = [0,0]

        if pl.speed==[0,-ms]:
            if lvl[y * 40 + x + 40] != 1:
                pl.geometry.y += 10
                pl.speed = [0,0]

            elif lvl[y * 40 + x - 40] != 1:
                pl.geometry.y -= 10
                pl.speed = [0,0]

            elif lvl[y * 40 + x - 1] != 1:
                pl.geometry.x -= 10
                pl.speed = [0,0]

            elif lvl[y * 40 + x + 1] != 1:
                pl.geometry.x += 10
                pl.speed = [0,0]

        if pl.speed==[ms,0]:
            if lvl[y * 40 + x - 1] != 1:
                pl.geometry.x -= 10
                pl.speed = [0,0]

            elif lvl[y * 40 + x - 40] != 1:
                pl.geometry.y -= 10
                pl.speed = [0,0]

            elif lvl[y * 40 + x + 1] != 1:
                pl.geometry.x += 10
                pl.speed = [0,0]

            elif lvl[y * 40 + x + 40] != 1:
                pl.geometry.y += 10
                pl.speed = [0,0]

        if pl.speed==[-ms,0]:
            if lvl[y * 40 + x + 1] != 1:
                pl.geometry.x += 10
                pl.speed = [0,0]

            elif lvl[y * 40 + x - 40] != 1:
                pl.geometry.y -= 10
                pl.speed = [0,0]

            elif lvl[y * 40 + x - 1] != 1:
                pl.geometry.x -= 10
                pl.speed = [0,0]

            elif lvl[y * 40 + x + 40] != 1:
                pl.geometry.y += 10
                pl.speed = [0,0]

    return pl