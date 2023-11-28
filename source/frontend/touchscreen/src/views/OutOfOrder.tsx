/** @format */

import { Button } from "@/components/ui/button";

import { DrinkMachineState } from "@/App";

import WarningSymbol from "@/assets/warning.svg";

interface OutOfOrderProps {
  reason: number;
  message: string;
}

//This view must show an awaiting screen when the UI has been inactive for a few minutes.
//It should have a taking up majority of the screen and a button at the bottum to toggle to home screen.
function OutOfOrder({ reason, message }: OutOfOrderProps): JSX.Element {
  return (
    <>
      <div className="flex flex-col  items-center h-full w-full ">
        <h1 className="scroll-m-20 text-white mt-10 text-6xl font-extrabold z-10 tracking-tight lg:text-5xl border-white">
          Drinks Machine
        </h1>
        <div className="flex flex-col flex-1 items-center justify-center">
          <img className="h-60 w-60" src={WarningSymbol} alt="OutOfOrder" />
          <div className="py-4 flex flex-col">
            <h3 className="text-xl font-semibold text-gray-300 text-center uppercase pb-4">
              Out of order
            </h3>
            <p className="text-2xl font-semibold text-white text-center">
              {message}
            </p>
            <p className="text-gray-500 text-center">Error code {reason}</p>
          </div>
        </div>
      </div>
    </>
  );
}

export default OutOfOrder;
