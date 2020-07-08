import pygame
import pacman
import ghost
import Coordinate_Check
import Maps
from RecordTable import new_record
import backgen

def gen_heroes(np):
    pac = pacman.pacman()
    pac.geometry.x = np[0][0]
    pac.geometry.y = np[0][1]

    g1 = ghost.ghost()
    g1.geometry.x = np[1][0]
    g1.geometry.y = np[1][1]
    g1.ball = pygame.image.load('ghost 1.gif')

    g2 = ghost.ghost()
    g2.geometry.x = np[2][0]
    g2.geometry.y = np[2][1]
    g2.ball = pygame.image.load('ghost 1.gif')

    g3 = ghost.ghost()
    g3.geometry.x = np[3][0]
    g3.geometry.y = np[3][1]
    g3.ball = pygame.image.load('ghost 1.gif')

    g4 = ghost.ghost()
    g4.geometry.x = np[4][0]
    g4.geometry.y = np[4][1]
    g4.ball = pygame.image.load('ghost 1.gif')

    print(pac.geometry.x,pac.geometry.y)

    return pac,g1,g2,g3,g4

def game(np,lvl):
    bg_color = pygame.image.load("Collage.jpg")
    if lvl==1:
        level=Maps.Level_1
    elif lvl==2:
        level=Maps.Level_2
    else:
        level=Maps.Level_3

    k=0
    size = [1200, 900]

    screen = pygame.display.set_mode(size)
    w_close = False

    pygame.init()

    pac,g1,g2,g3,g4=gen_heroes(np)

    ghosts=[g1,g2,g3,g4]

    seeds=backgen.seeds_gen(level)

    while not w_close and pac.mode != -1:
        # --- отрисовка картинки ---
        screen.blit(bg_color, [0, 0])
        pygame.time.Clock().tick(60)

        k += 1
        if k % 12 == 0:
            for i in range(4):
                if ghosts[i].time!=0:
                    ghosts[i].time-=1
                if ghosts[i].time==0:
                    ghosts[i].ball=pygame.image.load('ghost 1.gif')
                    ghosts[i].mode=1

            if pac.time != 0:
                pac.time -= 1
                for i in range(4):
                    if ghosts[i].mode==1:
                        ghosts[i].ball = pygame.image.load('Ghost.png')
                if pac.time == 0:
                    for i in range(4):
                        ghosts[i].ball = pygame.image.load('ghost 1.gif')
                    pac.mode = 0

        if k % 74 == 0:
            for i in range(4):
                ghosts[i].speed = Coordinate_Check.speed()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                w_close = True
            if event.type == pygame.KEYDOWN:
                pac.move_key(event.key)

        if level[(pac.geometry.y+15)//30 * 40 + (pac.geometry.x+15)//30] == 10:
            pygame.quit()
            new_record(pac.score)

        pac.shift()

        for i in range(len(seeds)):
            pac,seeds[i]=Coordinate_Check.check_seed(pac,seeds[i])

        pac.anim()

        for i in range(4):
            ghosts[i].shift()

        for i in range(4):
            pac, ghosts[i] = Coordinate_Check.coordinate_check(pac, ghosts[i])
            ghosts[i]=Coordinate_Check.check_wall(ghosts[i], level)

        pac = Coordinate_Check.check_wall_pac(pac, level)

        #отрисовка игры
        screen.blit(bg_color, [0, 0])

        for i in seeds:
            if i.mode!=0:
                screen.blit(i.ball, i.geometry)

        screen.blit(pac.ball, pac.geometry)
        for i in range(4):
            screen.blit(ghosts[i].ball, ghosts[i].geometry)

        pygame.display.flip()
    pygame.quit()

    new_record(pac.score)