/** @format */
import { Drink, Ingredient } from "@/api/endpoints/drinks/getDrinks";

import { Card, CardTitle } from "./ui/card";
import { useToast } from "@/components/ui/use-toast";
import { Toaster } from "./ui/toaster";

interface DrinkSelectionProps {
  drink: Drink;
  selectedDrink: Drink | undefined;
  setSelectedDrink: React.Dispatch<React.SetStateAction<Drink | undefined>>;
}

function DrinkSelection({
  drink,
  selectedDrink,
  setSelectedDrink,
}: DrinkSelectionProps): JSX.Element {
  const handleSelectDrink = () => {
    setSelectedDrink(drink);
    beat2.play();
  };

  //I need a function which calculates the total amountInCl of the drink based on the array of ingredients

  const indicatorHeight = `${drink.remainingFluid}%`;
  console.log(indicatorHeight);

  let beat = new Audio("src/assets/noselect.mp3");
  beat.volume = 0.1;

  let beat2 = new Audio("src/assets/jaja.mp3");
  beat2.volume = 0.1;

  const { toast } = useToast();

  return (
    <>
      <Card
        onClick={drink.remainingFluid <= 10 ? undefined : handleSelectDrink}
        className={`flex flex-col w-80 h-60 m-3 bg-zinc-700 shadow-slate-800 shadow-2xl border-2 border-zinc-600 ${
          selectedDrink === drink ? "bg-zinc-800 selectedCard" : ""
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
            /*  style={{ pointerEvents: "none" }} */
            onClick={() => {
              toast({
                variant: "destructive",
                title: `Oh oh! Refill container with ${drink.name} `,
                description: "Error: Refill container with vodka",
              });
            }}
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

        {drink.remainingFluid <= 10 && (
          <div className="h-8 rounded-b-xl mt-auto text-center text-lg bg-red-400 border-white">
            Refill container with vodka
          </div>
        )}

        {drink.remainingFluid > 10 && (
          <div className="h-8 rounded-b-xl mt-auto text-center text-lg bg-green-400 border-white">
            {drink.remainingFluid} % remaining
          </div>
        )}
      </Card>
    </>
  );
}

export default DrinkSelection;
