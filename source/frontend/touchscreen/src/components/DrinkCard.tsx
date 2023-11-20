/** @format */
import { Drink, Ingredient } from "@/api/endpoints/drinks/getDrinks";

import { Card, CardTitle } from "./ui/card";
import { useToast } from "@/components/ui/use-toast";
import useCalculateDrinks from "@/hooks/useCalculateDrinks";
import { Toaster } from "./ui/toaster";

interface DrinkCardProps {
  drink: Drink;
  selectedDrink: Drink | undefined;
  setSelectedDrink: React.Dispatch<React.SetStateAction<Drink | undefined>>;
}

function DrinkCard({
  drink,
  selectedDrink,
  setSelectedDrink,
}: DrinkCardProps): JSX.Element {
  const handleSelectDrink = () => {
    setSelectedDrink(drink);
    beat2.play();
  };

  //I need a function which calculates the total amountInCl of the drink based on the array of ingredients

  //const indicatorHeight = `${drink.remainingFluid}%`;

  let beat = new Audio("src/assets/noselect.mp3");
  beat.volume = 0.1;

  let beat2 = new Audio("src/assets/jaja.mp3");
  beat2.volume = 0.1;

  const calc = useCalculateDrinks();

  const pourable = calc.calcFluidLeft(drink.ingredients);
  const fluidLeft = pourable?.lowestFluidLeft;

  const { toast } = useToast();

  return (
    <>
      <Card
        onClick={!pourable.drinkPourable ? undefined : handleSelectDrink}
        className={`flex flex-col w-80 h-60 m-3 bg-zinc-800 shadow-slate-800 shadow-2xl border-2 border-zinc-600 ${
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
        {!pourable.drinkPourable && (
          <div
            className="absolute top-0 left-0 w-full h-full flex items-center text-[10rem] justify-center text-red-700  text-center"
            /*  style={{ pointerEvents: "none" }} */
            onClick={() => {
              toast({
                title: `Oh oh! Its maintenance time!`,
                description: `Refill container ${pourable.fluidThatMustBeRefilled[0].id} with ${pourable.fluidThatMustBeRefilled[0].fluid.name} to get this drink back on the menu!`,
              });
            }}
          >
            X
          </div>
        )}
        <CardTitle className="text-white mx-auto pt-2">{drink.name}</CardTitle>

        {/*   {pourable.drinkPourable && ( */}
        <div
          className={`h-8 rounded-b-xl mt-auto text-center text-lg  border-white ${
            pourable.drinkPourable ? "bg-green-400" : "bg-red-400"
          }`}
        >
          {fluidLeft} cl remaining
        </div>
        {/*   )} */}
      </Card>
    </>
  );
}

export default DrinkCard;
