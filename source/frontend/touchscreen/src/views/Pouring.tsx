/** @format */
import { DrinkMachineState } from "@/App";
import { useEffect } from "react";
import "./animation.css";
import Countdown from "@/components/Countdown";
import { Drink } from "@/api/endpoints/drinks/getDrinks";
import useCalculateDrinks from "@/hooks/useCalculateDrinks";

interface PouringProps {
  /* drinkId: number; */
  setView: React.Dispatch<React.SetStateAction<DrinkMachineState>>;
  selectedDrink: Drink | undefined;
  setSelectedDrink: React.Dispatch<React.SetStateAction<Drink | undefined>>;
}

function Pouring({
  setView,
  selectedDrink,
  setSelectedDrink,
}: PouringProps): JSX.Element {
  //We need to perform some sort of calculation to determine how long the pour should take
  //We can determine this based on the amount of ingredients in the drink

  const calc = useCalculateDrinks();
  const POUR_TIME = calc.calcPourTime(selectedDrink!);
  console.log(POUR_TIME);

  let beat = new Audio("/assets/elevator.mp3");
  beat.volume = 0.2;

  //Timeout function which will change the view back to the selection screen
  useEffect(() => {
    const liquid = document.getElementById("liquid") as HTMLDivElement | null;
    const foam = document.querySelector(".beer-foam") as HTMLDivElement | null;
    
    let beat = new Audio("/assets/elevator.mp3");
    beat.volume = 0.2;
    beat.play();
  
    setTimeout(() => {
      if (liquid) liquid.style.height = "230px";
      if (foam) foam.style.bottom = "228px";
    }, 1500);
  
    const pourTimeout = setTimeout(() => {
      setSelectedDrink(undefined);
      setView(DrinkMachineState.Waiting);
      beat.pause();
      beat.currentTime = 0; // Resetting the audio to the start
    }, POUR_TIME + 2000);
  
    // Cleanup function
    return () => {
      clearTimeout(pourTimeout);
      beat.pause();
      beat.currentTime = 0;
    };
  }, [POUR_TIME, setSelectedDrink, setView]);
  

  return (
    <>
      <div className="flex flex-col items-center h-full w-full text-white">
        <h1 className="scroll-m-20 text-white text-5xl font-extrabold tracking-tight lg:text-5xl mt-10 mb-4">
          POURING DRINK
        </h1>
        <h2 className="scroll-m-20 text-white text-3xl font-medium tracking-tight lg:text-5xl mb-4">
          {selectedDrink?.name}
        </h2>
        <div className=" w-[70%] h-[70%]  flex flex-col rounded-xl mt-auto mb-10">
          <div className="mx-auto">
            <Countdown time={POUR_TIME} />
          </div>

          <div id="container" className="">
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
                {/* <div className="foam foam-8"></div> */}
              </div>

              <div
                id="liquid"
                style={{
                  transitionProperty: "height",
                  transitionDuration: `${POUR_TIME}ms`,
                }}
              >
                <div
                  className="bubble bubble1"
                  style={{ animation: "bubbleUp 1.5s linear infinite 0.2s" }}
                ></div>
                <div
                  className="bubble bubble2"
                  style={{ animation: "bubbleUp 1.6s linear infinite 0.4s" }}
                ></div>
                <div
                  className="bubble bubble3"
                  style={{ animation: "bubbleUp 1.7s linear infinite 0.6s" }}
                ></div>
                <div
                  className="bubble bubble4"
                  style={{ animation: "bubbleUp 1.5s linear infinite 0.8s" }}
                ></div>
                <div
                  className="bubble bubble5"
                  style={{ animation: "bubbleUp 2.1s linear infinite 1.0s" }}
                ></div>
              </div>
            </div>
          </div>
          {/*  <div className=" absolute bottom-1.5  w-[21rem] h-16 rounded-t-3xl  bg-white border  border-zinc-600   flex flex-col justify-center">
            <div className="text-center text-black font-semibold text-xl ">
              Dispensing {20} cl
            </div>
          </div> */}
        </div>
      </div>
    </>
  );
}

export default Pouring;
