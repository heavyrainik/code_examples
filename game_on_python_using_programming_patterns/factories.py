from abc import ABC
import models.HumanModels
import models.OrkModels
import models.ElfModels
import models.DemonModels
from models.InfantryUnit import InfantryUnit
from models.CavalryUnit import CavalryUnit
from models.WizardUnit import WizardUnit
from models.SpecialUnit import SpecialUnit


class UnitFactory(ABC):
    def create_infantry_unit(self) -> InfantryUnit:
        pass

    def create_cavalry_unit(self) -> CavalryUnit:
        pass

    def create_wizard_unit(self) -> WizardUnit:
        pass

    def create_special_unit(self) -> SpecialUnit:
        pass


class HumanFactory(UnitFactory):
    def create_infantry_unit(self) -> InfantryUnit:
        return models.HumanModels.HumanInfantryUnit()

    def create_cavalry_unit(self) -> CavalryUnit:
        return models.HumanModels.HumanCavalryUnit()

    def create_wizard_unit(self) -> WizardUnit:
        return models.HumanModels.HumanWizardUnit()

    def create_special_unit(self) -> SpecialUnit:
        return models.HumanModels.HumanSpecialUnit()


class OrkFactory(UnitFactory):
    def create_infantry_unit(self) -> InfantryUnit:
        return models.OrkModels.OrkInfantryUnit()

    def create_cavalry_unit(self) -> CavalryUnit:
        return models.OrkModels.OrkCavalryUnit()

    def create_wizard_unit(self) -> WizardUnit:
        return models.OrkModels.OrkWizardUnit()

    def create_special_unit(self) -> SpecialUnit:
        return models.OrkModels.OrkSpecialUnit()


class ElfFactory(UnitFactory):
    def create_infantry_unit(self) -> InfantryUnit:
        return models.ElfModels.ElfInfantryUnit()

    def create_cavalry_unit(self) -> CavalryUnit:
        return models.ElfModels.ElfCavalryUnit()

    def create_wizard_unit(self) -> WizardUnit:
        return models.ElfModels.ElfWizardUnit()

    def create_special_unit(self) -> SpecialUnit:
        return models.ElfModels.ElfSpecialUnit()


class DemonFactory(UnitFactory):
    def create_infantry_unit(self) -> InfantryUnit:
        return models.DemonModels.DemonInfantryUnit()

    def create_cavalry_unit(self) -> CavalryUnit:
        return models.DemonModels.DemonCavalryUnit()

    def create_wizard_unit(self) -> WizardUnit:
        return models.DemonModels.DemonWizardUnit()

    def create_special_unit(self) -> SpecialUnit:
        return models.DemonModels.DemonSpecialUnit()
