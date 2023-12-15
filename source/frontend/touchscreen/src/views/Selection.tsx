/** @format */

import DrinkCard from "@/components/DrinkCard";
import { DrinkMachineState } from "@/App";
import Spinner from "@/components/Spinner";
import { Button } from "@/components/ui/button";

import usePourDrink from "@/api/endpoints/drinks/pourDrink";
import { Drink } from "@/api/endpoints/drinks/getDrinks";
import useCalculateDrinks from "@/hooks/useCalculateDrinks";
import { useEffect } from "react";

interface SelectionProps {
  view: DrinkMachineState;
  setView: React.Dispatch<React.SetStateAction<DrinkMachineState>>;
  selectedDrink: Drink | undefined;
  setSelectedDrink: React.Dispatch<React.SetStateAction<Drink | undefined>>;
}

function Selection({
  view,
  setView,
  selectedDrink,
  setSelectedDrink,
}: SelectionProps): JSX.Element {
  const calc = useCalculateDrinks();
  const drinks = calc.calcPossibleDrinks();
  console.log("Current configured drinks", drinks);
  let beat = new Audio("/assets/click.mp3");

  useEffect(() => {
    const timeout = setTimeout(() => {
      setView(DrinkMachineState.Waiting);
    }, 200000);

    return () => clearTimeout(timeout);
  }, [view, setView]);

  const pour = usePourDrink();

  const handleClick = (event: React.MouseEvent<HTMLButtonElement>) => {
    event.preventDefault();
    beat.play();

    pour.mutate({ id: selectedDrink?.id! });

    setView(DrinkMachineState.Pouring);
  };

  if (!drinks) {
    return (
      <>
        <div className="flex flex-col items-center h-full w-full">
          <h1 className="scroll-m-20  text-white mt-10 text-6xl font-extrabold  tracking-tight lg:text-5xl border-b border-white">
            SELECT DRINK
          </h1>
          <Spinner />
          <Button
            onClick={() => setView(DrinkMachineState.Pouring)}
            className="mt-auto mb-8 p-8 bg-white"
            disabled
          >
            <h2 className="scroll-m-20 w-72  text-3xl font-semibold tracking-tight transition-colors first:mt-0">
              Pour Drink
            </h2>
          </Button>
        </div>
      </>
    );
  }

  return (
    <>
      <div className="flex flex-col items-center h-full w-full">
        <div className="drop-shadow-2xl shadow-green-700 mt-10 pb-4">
          <h1 className="scroll-m-20 text-white   text-6xl font-extrabold tracking-tight lg:text-5xl   ">
            SELECT DRINK
          </h1>
        </div>

        {drinks?.map((drink) => (
          <DrinkCard
            key={drink.id}
            drink={drink}
            selectedDrink={selectedDrink!}
            setSelectedDrink={setSelectedDrink}
          />
        ))}

        <Button
          onClick={handleClick}
          className="mt-auto mb-8 p-8 bg-white"
          disabled={selectedDrink ? false : true}
        >
          <h2 className="scroll-m-20 w-72 text-3xl font-semibold tracking-tight transition-colors first:mt-0 ">
            Pour Drink
          </h2>
        </Button>
      </div>
    </>
  );
}

export default Selection;
