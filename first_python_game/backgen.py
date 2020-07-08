from PIL import Image
import Maps
from seed import seed
import pygame

def backgen(lvl):
    listofimages = []
    np=[]

    if lvl==1:
        level=Maps.Level_1
    elif lvl==2:
        level=Maps.Level_2
    else:
        level=Maps.Level_3

    for i in range(len(level)):
            ts=level[i]

            if ts == 1:
                name = 'wall.png'
            else:
                if ts>1 and ts<7 :
                    np.append([i%40*30,i//40*30])
                name = 'empty.jpg'
                if ts==10:
                    name='unnamed.png'

            listofimages.append(name)

    create_collage(1200, 900, listofimages)
    return np

def create_collage(width, height, listofimages):
    cols = 40
    rows = 30
    thumbnail_width = 30
    thumbnail_height = 30
    size = thumbnail_width, thumbnail_height
    new_im = Image.new('RGB', (width, height))

    ims = []

    for p in listofimages:
        im = Image.open(p)
        im.thumbnail(size)
        ims.append(im)

    i = 0
    x = 0
    y = 0

    for col in range(rows):
        for row in range(cols):
            new_im.paste(ims[i], (x, y))
            i += 1
            x += thumbnail_width

        y += thumbnail_height
        x = 0

    new_im.save("Collage.jpg")

def seeds_gen(level):
    seeds=[]

    for i in range(len(level)):
        if level[i]==8:
            s=seed()
            s.geometry.x=i%40*30
            s.geometry.y=i//40*30
            s.ball=pygame.image.load('pellet.gif')
            s.mode=1
            seeds.append(s)

        if level[i]==9:
            s=seed()
            s.geometry.x=i%40*30
            s.geometry.y=i//40*30
            s.ball=pygame.image.load('fruit.png')
            s.mode=2
            seeds.append(s)

    return seeds