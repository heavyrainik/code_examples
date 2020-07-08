import os

# variables
HEIGHT = 700
WIDTH = 1200
GROUP_MATES_COUNT = 6
FRAME_RATE = 90
MAX_AMOUNT_OF_GAME_OBJECTS = 6
MAX_AMOUNT_OF_SKINS = 3
STARTING_SCORE = 0

COLUMN_COUNT = 8
COLUMN_WIDTH = int(WIDTH / COLUMN_COUNT)

GROUP_MATE_Y_SPEED = 1.5
GROUP_MATE_BIRTH = int(HEIGHT * 1 / 10)
GROUP_MATE_DEATH = int(HEIGHT * 9 / 10)
GROUP_MATE_WIDTH = int(WIDTH * 1 / 8)
GROUP_MATE_HEIGHT = int(HEIGHT * 1 / 5)

# asserts
IMAGES_DIRECTORY = "images/models_images"
IMAGES = os.listdir(IMAGES_DIRECTORY)
GROUP_MATES_TYPES = [i for i in range(1, GROUP_MATES_COUNT + 1)]
DROP_CHANCES = [0.03, 0.03, 0.85, 0.03, 0.03, 0.03]

# score_font
SCORE_X = WIDTH / 20
SCORE_Y = HEIGHT / 40
SCORE_COLOR = (255, 255, 0)
SCORE_FONT = 'Arial'
SCORE_SIZE = 25

# menu background
RECT_X = 0
RECT_Y = 0
RECT_WIDTH = WIDTH
RECT_HEIGHT = HEIGHT / 10
RECT_COLOR = (138, 51, 36)

# buttons
BUTTON_Y = HEIGHT / 40
BUTTON_WIDTH = WIDTH * 1 / 7
BUTTON_HEIGHT = HEIGHT / 20
BUTTON_FONT = 'Arial'
BUTTON_SIZE = 15
BUTTON_TEXT_COLOR = (255, 255, 255)
BUTTON_COLOR = (238, 99, 99)
BUTTON1_MESSAGE = " Новый скин для Игоря! 1000"
BUTTON1_KEY = "Skin"
BUTTON2_MESSAGE = "Новый фон! 250"
BUTTON2_KEY = "Background"

# backgrounds
BACKGROUND_IMAGES_AMOUNT = 5
BACKGROUND_IMAGE = 'images/goth.jpg'
OPTIONAL_BACKGROUND_IMAGE = 'images/mem.jpg'
BACKGROUND_IMAGES_DIRECTORY = "images/background_images"
BACKGROUND_IMAGES = os.listdir(BACKGROUND_IMAGES_DIRECTORY)

IMAGES_TYPES = [i for i in range(0, BACKGROUND_IMAGES_AMOUNT)]
IMAGES_DROP_CHANCES = [0.2, 0.2, 0.2, 0.2, 0.2]