


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
    statistics: Statistics

class FluidContainer:
    containerId: int
    fluidAmountInCl: int
    fluidType: Fluid



#Needs to contain alot of comparison logic to figure out if drinks are possible to make
class DrinksMachine:
    drinks: list[Drink] #list of unlimited size
    containers: list[FluidContainer] # list of size 3
    





