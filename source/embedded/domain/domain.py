from dataclasses import dataclass


# Domain classes
@dataclass
class Fluid:
    def __init__(self, name: str):
        self.name = name
        self.id = None

    id: int
    name: str


@dataclass
class Ingredient:
    def __init__(self, fluid: Fluid, amount_in_cl: int):
        self.fluid = fluid
        self.amount_in_cl = amount_in_cl
        self.id = None

    id: int
    amount_in_cl: int
    fluid: Fluid


@dataclass
class Statistics:
    amount_poured: int
    pour_duration: int
    error: str
    timestamp: str


@dataclass
class Image:
    def __init__(self, path: str):
        self.path = path
        self.id = None

    id: int
    path: str


@dataclass
class Drink:
    def __init__(
        self, name: str, amount_in_cl: int, image: Image, ingredients: list[Ingredient]
    ):
        self.name = name
        self.amount_in_cl = sum(ingredient.amount_in_cl for ingredient in ingredients)
        self.image = image
        self.ingredients = ingredients
        self.id = None

    id: int
    name: str
    amount_in_cl: int  # 0-100
    image: Image
    ingredients: list[Ingredient]


@dataclass
class FluidContainer:
    def __init__(self, fluid_amount_in_cl: int, fluid_type: Fluid):
        self.fluid_amount_in_cl = fluid_amount_in_cl
        self.fluid_type = fluid_type
        self.container_id = None

    container_id: int
    fluid_amount_in_cl: int
    fluid_type: Fluid
