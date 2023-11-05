from dataclasses import dataclass



# Domain classes
@dataclass
class Fluid:
    id: int
    name: str

@dataclass
class Ingredient:
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
    id: int
    path: str

@dataclass
class Drink:
    id: int
    name: str
    amount_in_cl: int #0-100
    image: Image
    Ingredients: list[Ingredient]

@dataclass
class FluidContainer:
    container_id: int
    fluid_amount_in_cl: int
    fluid_type: Fluid







