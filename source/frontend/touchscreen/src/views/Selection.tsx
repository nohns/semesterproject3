/** @format */

import DrinkSelection from "@/components/DrinkSelection";
import { DrinkMachineState } from "@/App";
import { useState } from "react";
import Spinner from "@/components/Spinner";
import { Button } from "@/components/ui/button";

import usePourDrink from "@/api/endpoints/drinks/pourDrink";
import useGetDrinks, { Drink } from "@/api/endpoints/drinks/getDrinks";

interface SelectionProps {
  setView: React.Dispatch<React.SetStateAction<DrinkMachineState>>;
  selectedDrink: Drink | undefined;
  setSelectedDrink: React.Dispatch<React.SetStateAction<Drink | undefined>>;
}

function Selection({ setView }: SelectionProps): JSX.Element {
  const drinksQuery = useGetDrinks();

  if (drinksQuery.error) {
    return <div>{`:()`}</div>;
  }

  //Create some state to manage which drink has been selected
  const [selectedDrink, setSelectedDrink] = useState<number>();

  const mutate = usePourDrink();

  const handleClick = (event: React.MouseEvent<HTMLButtonElement>) => {
    event.preventDefault();

    mutate.mutate({ id: selectedDrink! });

    setView(DrinkMachineState.Pouring);
  };

  if (drinksQuery.isLoading) {
    return (
      <>
        <div className="flex flex-col items-center h-full w-full  ">
          <h1 className="scroll-m-20  text-white mt-10 text-6xl font-extrabold  tracking-tight lg:text-5xl border-b border-white">
            SELECT DRINK
          </h1>
          <Spinner />
          <Button
            onClick={() => setView(DrinkMachineState.Pouring)}
            className="mt-auto mb-8 p-8 bg-white"
          >
            <h2 className="scroll-m-20  text-3xl font-semibold tracking-tight transition-colors first:mt-0">
              Pour drink
            </h2>
          </Button>
        </div>
      </>
    );
  }

  return (
    <>
      <div className="flex flex-col items-center h-full w-full   ">
        <div className="drop-shadow-2xl shadow-green-700 mt-10 pb-4">
          <h1 className="scroll-m-20 text-white   text-6xl font-extrabold tracking-tight lg:text-5xl   ">
            SELECT DRINK
          </h1>
        </div>

        {drinksQuery.data?.drinks?.map((drink) => (
          <DrinkSelection
            key={drink.id}
            drink={drink}
            selected={selectedDrink!}
            setSelectedDrink={setSelectedDrink}
          />
        ))}

        <Button
          onClick={handleClick}
          className="mt-auto mb-8 p-8 bg-white"
          disabled={selectedDrink ? false : true}
        >
          <h2 className="scroll-m-20  text-3xl font-semibold tracking-tight transition-colors first:mt-0">
            Pour Drink
          </h2>
        </Button>
      </div>
    </>
  );
}

export default Selection;
