/** @format */
import { Drink } from "@/api/endpoints/drinks/getDrinks";

interface ShowDrinksProps {
  drinks: Drink[];
}

function ShowDrinks({ drinks }: ShowDrinksProps): JSX.Element {
  return (
    <>
      <div className="flex flex-row">
        {drinks.map((drink) => (
          <div
            className="flex flex-col m-3 rounded-2xl bg-emerald-600 transition duration-300 hover:bg-emerald-700 hover:opacity-75"
            key={drink.id}
          >
            <div className="text-white text-2xl mx-auto">{drink.name}</div>
            <img className="h-40 w-40 mx-auto" src={drink.image?.path} />
          </div>
        ))}
      </div>
    </>
  );
}

export default ShowDrinks;
