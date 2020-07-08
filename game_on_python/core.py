import pygame
import config


class Game:
    def __init__(self, caption, width, height, back_image_filename, frame_rate):
        self.background_image = pygame.image.load(back_image_filename)
        self.background_image = pygame.transform.scale(self.background_image, (config.WIDTH, config.HEIGHT))
        self.frame_rate = frame_rate
        self.game_over = False
        self.game_objects = []
        self.menu_objects = []
        pygame.mixer.pre_init(44100, 16, 2, 4096)
        pygame.init()
        pygame.font.init()
        self.screen = pygame.display.set_mode((width, height))
        pygame.display.set_caption(caption)
        self.clock = pygame.time.Clock()

    def update(self):
        for o in self.game_objects:
            o.update()

    def draw(self):
        for menu_object in self.menu_objects:
            menu_object.draw(self.screen)

        for game_object in self.game_objects:
            game_object.draw(self.screen)

    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.game_over = True

            if event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == 1:
                    pygame.draw.circle(self.screen, (225, 0, 50), event.pos, 20)

    def run(self):
        while not self.game_over:
            self.screen.blit(self.background_image, (0, 0))

            self.handle_events()
            self.update()
            self.draw()

            pygame.display.update()
            self.clock.tick(self.frame_rate)
