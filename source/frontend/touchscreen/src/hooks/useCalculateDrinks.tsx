/** @format */

import useGetContainers from "@/api/endpoints/container/getContainers";
import useGetDrinks, {
  Drink,
  Fluid,
  Ingredient,
} from "@/api/endpoints/drinks/getDrinks";

// O(n^3) Who the fuck cares it works
const useCalculateDrinks = () => {
  const { data } = useGetDrinks();
  const containers = useGetContainers();
  console.log(containers.data);

  //const fluids = containers.data?.containers!;
  const calcPossibleDrinks = () => {
    if (data?.drinks.length! > 0 && containers.data?.containers.length! > 0) {
      const drinks = data?.drinks!;
      let fluids: Fluid[] = [];

      //Loop over containers and append the fluid to fluids
      containers.data?.containers.forEach((container) => {
        fluids.push(container.fluid);
      });
      console.log("fluids", fluids);

      const possibleDrinks: Drink[] = [];
      drinks.forEach((drink) => {
        const isPossible = drink.ingredients.every((ingredient) =>
          fluids.some((fluid) => fluid.id === ingredient.fluid.id)
        );

        if (isPossible) {
          possibleDrinks.push(drink);
        }
      });

      return possibleDrinks;

      console.log("POSSIBLE DRINKS KEKW", possibleDrinks);
      return possibleDrinks;
    }
  };

  // O(N^2) :) Not optmized at all but it works
  const calcFluidLeft = (ingredients: Ingredient[]) => {
    //Use passed in ingredients to find the fluid left in the container with the lowest amount of fluid left
    const fluidContainers = containers.data?.containers!;

    //Check if the drink is pourable
    const isPourable = ingredients.every((ingredient) =>
      fluidContainers.some(
        (fluidContainer) =>
          fluidContainer.fluid.id === ingredient.fluid.id &&
          fluidContainer.fluidAmountInCl >= ingredient.amountInCl
      )
    );
    console.log("Is pourable", isPourable);
    // O(n^3) Fuck it
    let lowestFluidLeft = 0;
    fluidContainers
      .filter((fluidContainer) => {
        return ingredients.some((ingredient) => {
          return fluidContainer.fluid.id === ingredient.fluid.id;
        });
      })
      .forEach((fluidContainer) => {
        ingredients.forEach((ingredient) => {
          if (fluidContainer.fluid.id === ingredient.fluid.id) {
            if (lowestFluidLeft === 0) {
              lowestFluidLeft = fluidContainer.fluidAmountInCl;
            } else if (fluidContainer.fluidAmountInCl < lowestFluidLeft) {
              lowestFluidLeft = fluidContainer.fluidAmountInCl;
            }
          }
        });
      });

    const fluidThatMustBeRefilled = ingredients.filter((ingredient) => {
      return fluidContainers.some(
        (fluidContainer) =>
          fluidContainer.fluid.id === ingredient.fluid.id &&
          fluidContainer.fluidAmountInCl < ingredient.amountInCl
      );
    });
    return {
      drinkPourable: isPourable,
      lowestFluidLeft: lowestFluidLeft,
      fluidThatMustBeRefilled: fluidThatMustBeRefilled,
    };
  };

  // Add this function inside the Pouring component in src/views/Pouring.tsx
  const calcPourTime = (drink: Drink) => {
    let totalPourTime = 0;
    //Loop through the ingrediens of the drink and find the biggest fluidAmountInCl
    let highestFluidAmount = 0;
    drink.ingredients.forEach((ingredient) => {
      if (ingredient.amountInCl > highestFluidAmount) {
        highestFluidAmount = ingredient.amountInCl;
      }
    });
    //Calculate the pour time based on the highest fluidAmountInCl // 0.135cl per second
    totalPourTime = highestFluidAmount / 0.135;

    //Convert to milliseconds

    return totalPourTime * 1000;
  };

  return { calcPossibleDrinks, calcPourTime, calcFluidLeft };
};

export default useCalculateDrinks;
