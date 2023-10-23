


# Domain classes
class Fluid:
    id: int
    name: str

class Ingredient:
    id: int
    amountInCl: int
    fluid: Fluid
    
class Statistics:
    amountPoured: int
    pourDuration: int
    error: str
    timestamp: str

class Image:
    id: int
    path: str

class Drink:
    id: int
    name: str
    amountInCl: int #0-100
    image: Image
    Ingredients: list[Ingredient]

class FluidContainer:
    containerId: int
    fluidAmountInCl: int
    fluidType: Fluid







