/** @format */

import useGetDrinks, { Drink } from "@/api/endpoints/drinks/getDrinks";
import { Fluid } from "@/api/endpoints/fluid/getFluids";

// O(n^3) Who the fuck cares it works
const useCalculateDrinks = () => {
  const { data } = useGetDrinks();

  const calculate = (fluids: Fluid[]) => {
    if (data?.drinks.length! > 0) {
      const drinks = data?.drinks!;

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

  return { calculate };
};

export default useCalculateDrinks;
