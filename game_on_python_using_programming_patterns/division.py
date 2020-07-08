class Squad:
    units = []

    def __init__(self):
        self.attack = 0

    def count_attack(self):
        attack = 0

        for unit in self.units:
            attack += unit.attack

        attack /= len(self.units)
        return attack

    def append(self, units):
        for unit in units:
            self.units.append(unit)


class Army:
    units = []

    def __init__(self):
        self.attack = 0

    def count_attack(self):
        attack = 0

        for unit in self.units:
            attack += unit.attack

        attack /= len(self.units)
        return attack*1.1

    def append(self, units):
        for unit in units:
            self.units.append(unit)

