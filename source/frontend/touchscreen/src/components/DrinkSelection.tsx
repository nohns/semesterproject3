/** @format */
import { Drink } from "@/api/endpoints/drinks/getDrinks";
import CocktailSvg from "./CocktailSvg";
import FluidLevel from "./FluidLevel";
import { Card, CardDescription, CardTitle } from "./ui/card";

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

  return (
    <>
      <Card
        onClick={handleSelectDrink}
        className={`flex flex-row w-80 h-40 m-3 mt-8 bg-zinc-700 shadow-slate-800 shadow-2xl ${
          selected === drink.id ? "bg-zinc-800 selectedCard" : ""
        }`}
      >
        <img src={drink.image.path} alt={drink.name} className="h-40 w-40" />
        <CardTitle className="text-white mt-6 mr-auto">{drink.name}</CardTitle>
        <CardDescription></CardDescription>
        <div className="flex flex-col justify-end p-1 mr-4 shadow-2xl shadow-emerald-700 border-2 bg-zinc-600 my-4 rounded-lg relative">
          <FluidLevel level={100} />
          <div className="absolute bottom-0 left-0 w-full h-px bg-white opacity "></div>
        </div>
      </Card>
    </>
  );
}

export default DrinkSelection;
