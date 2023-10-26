


# Domain classes
class Fluid:
    id: int
    name: str

class Ingredient:
    id: int
    amount_in_cl: int
    fluid: Fluid
    
class Statistics:
    amount_poured: int
    pour_duration: int
    error: str
    timestamp: str

class Image:
    id: int
    path: str

class Drink:
    id: int
    name: str
    amount_in_cl: int #0-100
    image: Image
    Ingredients: list[Ingredient]

class FluidContainer:
    container_id: int
    fluid_amount_in_cl: int
    fluid_type: Fluid







