/** @format */
import { Drink } from "@/api/endpoints/drinks/getDrinks";

import { Card, CardFooter, CardTitle } from "./ui/card";
import { BarChart, Bar, ResponsiveContainer, XAxis, YAxis } from "recharts";

interface DrinkSelectionProps {
  drink: Drink;
  selected: number;
  setSelectedDrink: React.Dispatch<React.SetStateAction<number | undefined>>;
}

function DrinkSelection({
  drink,
  selected,
  setSelectedDrink,
}: DrinkSelectionProps): JSX.Element {
  const handleSelectDrink = () => {
    setSelectedDrink(drink.id);
  };

  const indicatorHeight = `${drink.remainingFluid}%`;
  console.log(indicatorHeight);

  return (
    <>
      <Card
        onClick={drink.remainingFluid <= 10 ? undefined : handleSelectDrink}
        className={`flex flex-col w-80 h-60 m-3 bg-zinc-700 shadow-slate-800 shadow-2xl ${
          selected === drink.id ? "bg-zinc-800 selectedCard" : ""
        }`}
        style={{
          backgroundImage: `url(${drink.image.path})`,
          backgroundPosition: "center",
          backgroundSize: "auto 90%",
          backgroundRepeat: "no-repeat",
          position: "relative", // Add position relative to the card
        }}
      >
        {drink.remainingFluid <= 10 && (
          <div
            className="absolute top-0 left-0 w-full h-full flex items-center text-9xl justify-center text-red-500  text-center"
            style={{ pointerEvents: "none" }}
          >
            X
          </div>
        )}
        <CardTitle className="text-white mx-auto pt-2">{drink.name}</CardTitle>

        <div className="flex flex-row justify-between mx-1 ">
          <div>
            <div className="relative h-4">
              <div
                className="absolute bottom-0 left-0 w-full bg-blue-500"
                style={{ height: indicatorHeight }}
              ></div>
            </div>
          </div>
        </div>
        <div className="h-8 rounded-b-xl mt-auto text-center bg-zinc-600 border-white">
          {drink.remainingFluid} % remaining
        </div>
      </Card>
    </>
  );
}

export default DrinkSelection;
