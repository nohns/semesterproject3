/** @format */

import useGetContainers from "@/api/endpoints/container/getContainers";
import useGetDrinks, {
  Drink,
  Ingredient,
} from "@/api/endpoints/drinks/getDrinks";

// O(n^3) Who the fuck cares it works
const useCalculateDrinks = () => {
  const { data } = useGetDrinks();
  const containers = useGetContainers();

  const calcPossibleDrinks = () => {
    if (data?.drinks.length! > 0 && containers.data?.containers.length! > 0) {
      const drinks = data?.drinks!;
      const fluids = containers.data?.containers!;

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
    //Calculate the pour time based on the highest fluidAmountInCl // 0.16cl per second
    totalPourTime = highestFluidAmount / 0.16;

    //Convert to milliseconds

    return totalPourTime * 1000;
  };

  return { calcPossibleDrinks, calcPourTime, calcFluidLeft };
};

export default useCalculateDrinks;
