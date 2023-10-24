/** @format */
import { DrinkMachineState } from "@/App";
import { CountdownCircleTimer } from "react-countdown-circle-timer";
import { Button } from "@/components/ui/button";
import useCancelPourDrink from "@/api/endpoints/drinks/cancelPourDrink";
import { useState, useEffect } from "react";
import "./animation.css";

interface PouringProps {
  drinkId: number;
  setView: React.Dispatch<React.SetStateAction<DrinkMachineState>>;
}

function Pouring({ drinkId, setView }: PouringProps): JSX.Element {
  const mutate = useCancelPourDrink();

  const POUR_TIME = 3000;

  useEffect(() => {
    const pour = document.querySelector(".pour");
    const liquid = document.getElementById("liquid");
    const foam = document.querySelector(".beer-foam");

    setTimeout(() => {
      // Pour Me Another Drink, Bartender!
      pour.style.height = "360px";
    }, 500);

    setTimeout(() => {
      pour.style.height = "0";
    }, POUR_TIME + 500);

    setTimeout(() => {
      // I Said Fill 'Er Up!
      liquid.style.height = "230px";
      foam.style.bottom = "228px";
    }, 1500);
  }, []);

  const handleClick = (event: React.MouseEvent<HTMLButtonElement>) => {
    event.preventDefault();

    mutate.mutate({ id: drinkId });

    setView(DrinkMachineState.Selection);
  };

  return (
    <>
      <div className="flex flex-col items-center h-full w-full text-white justify-center ">
        <h1 className="scroll-m-20 text-white   text-5xl font-extrabold tracking-tight lg:text-5xl mt-10">
          POURING DRINK
        </h1>
        <h2 className="mr-auto ml-14 text-sm pb-4">
          Pls wait while we prepare your drink
        </h2>
        <div id="container">
          <div
            className="pour"
            style={{ height: 0, transition: "height 1.5s" }}
          ></div>
          <div id="beaker">
            <div
              className="beer-foam"
              style={{
                transitionProperty: "bottom",
                transitionDuration: `${POUR_TIME}ms`,
              }}
            >
              <div className="foam foam-1"></div>
              <div className="foam foam-1-2"></div>
              <div className="foam foam-2"></div>
              <div className="foam foam-2-3"></div>
              <div className="foam foam-3"></div>
              <div className="foam foam-3-4"></div>
              <div className="foam foam-4"></div>
              <div className="foam foam-4-5"></div>
              <div className="foam foam-5"></div>
              <div className="foam foam-5-6"></div>
              <div className="foam foam-6"></div>
              <div className="foam foam-6-7"></div>
              <div className="foam foam-7"></div>
              <div className="foam foam-7-8"></div>
              <div className="foam foam-8"></div>
            </div>

            <div
              id="liquid"
              style={{
                transitionProperty: "height",
                transitionDuration: `${POUR_TIME}ms`,
              }}
            >
              <div className="bubble bubble1"></div>
              <div className="bubble bubble2"></div>
              <div className="bubble bubble3"></div>
              <div className="bubble bubble4"></div>
              <div className="bubble bubble5"></div>
            </div>
          </div>
        </div>
        <Button
          /* onClick={() => setView(DrinkMachineState.Waiting)} */
          onClick={handleClick}
          className="mt-auto mb-8 p-8 bg-white"
        >
          <h2 className="scroll-m-20  text-3xl font-semibold tracking-tight transition-colors first:mt-0">
            Cancel
          </h2>
        </Button>
      </div>
    </>
  );
}

export default Pouring;
