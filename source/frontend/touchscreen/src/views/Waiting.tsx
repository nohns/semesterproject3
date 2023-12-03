/** @format */

import { Button } from "@/components/ui/button";

import { DrinkMachineState } from "@/App";

interface WaitingProps {
  setView: React.Dispatch<React.SetStateAction<DrinkMachineState>>;
}

//This view must show an awaiting screen when the UI has been inactive for a few minutes.
//It should have a taking up majority of the screen and a button at the bottum to toggle to home screen.
function Waiting({ setView }: WaitingProps): JSX.Element {
  let beat = new Audio("/assets/jaja.mp3");
  beat.volume = 0.1;

  return (
    <>
      <div className="flex flex-col  items-center h-full w-full bg-drink ">
        <h1 className="scroll-m-20 text-white mt-10 text-6xl font-extrabold z-10 tracking-tight lg:text-5xl border-white">
          Drinks Machine
        </h1>

        <Button
          onClick={() => setView(DrinkMachineState.Selection)}
          className="mt-auto mb-8 p-8 bg-white z-10 selectedCard"
        >
          <h2 className="scroll-m-20 w-72 text-3xl font-semibold tracking-tight transition-colors first:mt-0">
            Select Drink
          </h2>
        </Button>
      </div>
    </>
  );
}

export default Waiting;
