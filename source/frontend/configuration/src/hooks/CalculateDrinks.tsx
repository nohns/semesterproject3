/** @format */

import { Drink } from "@/api/endpoints/drinks/getDrinks";
import { Fluid } from "@/api/endpoints/fluid/getFluids";

const useCalculateDrinks = () => {
  //const { data } = useGetDrinks();
  console.log("useCalculateDrinkws called");

  const calculate = (fluids: Fluid[], drinks: Drink[]) => {
    if (drinks.length > 0) {
      const possibleDrinks: Drink[] = [];
      console.log("I am actually calculating stuff");

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
    return [];
  };

  return { calculate };
};

export default useCalculateDrinks;
