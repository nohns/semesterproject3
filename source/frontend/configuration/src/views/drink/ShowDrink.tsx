/** @format */

import { Drink } from "@/api/endpoints/drinks/getDrinks";
import React from "react";

interface ShowDrinkProps {
  drinks: Drink[];
}

function ShowDrink({ drinks }: ShowDrinkProps): JSX.Element {
  return (
    <>
      <div className="flex flex-col">
        <div className="text-white">These are the available drinks: </div>
        <div className="flex flex-col">
          {drinks.map((drink) => (
            <div className="flex flex-col" key={drink.id}>
              <div className="text-white mx-4">{drink.name}</div>
              <img className="h-20 w-20" src={drink.image?.path} />
            </div>
          ))}
        </div>
      </div>
    </>
  );
}

export default ShowDrink;
