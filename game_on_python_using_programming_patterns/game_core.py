import pygame

import cursor
import graphics
import config
import division


class GameLogic:
    def __init__(self):
        self.graphics = graphics.GameGraphics()
        self.mouse = cursor.Cursor()
        self.game_in_process = True
        self.menu_objects = []
        self.game_objects = []
        self.selected_units = []
        self.squad = []
        self.army = []
        self.resources = config.starting_resources
        self.graphics.create_menu(self.menu_objects, self.resources)

    def create_unit(self, factory, unit_type):
        if unit_type == 1:
            self.game_objects.append(factory.create_infantry_unit())
        elif unit_type == 2:
            self.game_objects.append(factory.create_cavalry_unit())
        elif unit_type == 3:
            self.game_objects.append(factory.create_wizard_unit())
        elif unit_type == 4:
            self.game_objects.append(factory.create_special_unit())

    def check_click(self, core):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                core.game_in_process = False

            if event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == 1 and event.pos[1] > config.RECT_HEIGHT:
                    self.mouse.start_selection(event.pos)
                if event.button == 1 and event.pos[1] <= config.RECT_HEIGHT:
                    self.proceed_press_on_button(event.pos)

            if event.type == pygame.MOUSEBUTTONUP:
                if event.button == 1:
                    self.proceed_selection(event)

    def proceed_selection(self, event):
        selected_part = self.mouse.proceed_selection(event.pos)
        self.graphics.draw_selected_part(selected_part[0], selected_part[1])

        self.selected_units = []

        for game_object in self.game_objects:
            if selected_part[0][0] <= game_object.geometry.x <= selected_part[1][0] and \
                    selected_part[0][1] <= game_object.geometry.y <= selected_part[1][1]:
                self.selected_units.append(game_object)

    def proceed_press_on_button(self, pos):
        for menu_object in self.menu_objects:
            if menu_object.bounds.collidepoint(pos):
                if menu_object.type == config.BUTTON1_KEY and self.resources >= 10:
                    new_division = division.Squad()
                    new_division.append(self.selected_units)
                    self.delete_units_from_different_divisions()
                    self.squad.append(new_division)
                    self.resources -= 10
                if menu_object.type == config.BUTTON2_KEY and self.resources >= 25 and self.check_fight():
                    new_division = division.Army()
                    new_division.append(self.selected_units)
                    self.delete_units_from_different_divisions()
                    self.army.append(new_division)
                    self.resources -= 25

    def check_fight(self):
        for game_object in self.selected_units:
            if game_object.is_fighting:
                return False

    def delete_units_from_different_divisions(self):
        if len(self.squad) != 0:
            for division in self.squad:
                for unit in self.selected_units:
                    division.units.remove(unit)
        if len(self.army) != 0:
            for division in self.army:
                for unit in self.selected_units:
                    division.units.remove(unit)

    def action(self):
        pass

    def draw(self):
        self.graphics.draw(self.game_objects, self.menu_objects)
