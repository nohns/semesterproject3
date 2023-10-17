/** @format */

import DrinkSelection from "@/components/DrinkSelection";
import { DrinkMachineState } from "@/App";
import { useState } from "react";
import Spinner from "@/components/Spinner";
import { Button } from "@/components/ui/button";

import usePourDrink from "@/api/endpoints/drinks/pourDrink";
import useGetDrinks from "@/api/endpoints/drinks/getDrinks";
import Clock from "@/components/Clock";

interface SelectionProps {
  setView: React.Dispatch<React.SetStateAction<DrinkMachineState>>;
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
        <div className="flex flex-col items-center h-screen w-screen">
          <div>
            <h1 className="scroll-m-20 text-white mt-10 text-6xl font-extrabold tracking-tight lg:text-5xl border-b border-white">
              Drinks Machine
            </h1>
            <Clock />
          </div>
          <h1 className="scroll-m-20 text-white mt-10 text-6xl font-extrabold tracking-tight lg:text-5xl border-b border-white">
            Select drink
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
      <div className="flex flex-col items-center h-screen w-screen">
        <div className="flex flex-row mt-4 justify-center w-full mx-20">
          {/*   <h1 className="text-sm text-muted-foreground">Drinks Machine</h1> */}
          <small className="text-sm font-medium leading-none text-muted-foreground">
            Drinks Machine
          </small>
          <Clock />
        </div>
        <h1 className="scroll-m-20 text-white mt-10 text-6xl font-extrabold tracking-tight lg:text-5xl border-white">
          Select drink
        </h1>
        {drinksQuery.data?.drinks?.map((drink) => (
          <DrinkSelection
            key={drink.id}
            drink={drink}
            selected={selectedDrink!}
            setSelectedDrink={setSelectedDrink}
          />
        ))}
        <Button
          /* onClick={() => setView(DrinkMachineState.Pouring)} */
          onClick={handleClick}
          className="mt-auto mb-8 p-8 bg-white"
          disabled={selectedDrink ? false : true}
        >
          <h2 className="scroll-m-20  text-3xl font-semibold tracking-tight transition-colors first:mt-0">
            Pour drink
          </h2>
        </Button>{" "}
      </div>
    </>
  );
}

export default Selection;
