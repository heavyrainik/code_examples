import pygame
import game_core
import factories


def main():
    pygame.init()
    core = game_core.GameLogic()

    demons = factories.DemonFactory()

    core.create_unit(demons, 1)
    core.create_unit(demons, 2)
    core.create_unit(demons, 3)
    core.create_unit(demons, 4)

    while core.game_in_process:
        core.draw()

        core.check_click(core)

        core.action()


if __name__ == '__main__':
    main()
