/** @format */
import { DrinkMachineState } from "@/App";
import { CountdownCircleTimer } from "react-countdown-circle-timer";
import { Button } from "@/components/ui/button";
import useCancelPourDrink from "@/api/endpoints/drinks/cancelPourDrink";

interface PouringProps {
  drinkId: number;
  setView: React.Dispatch<React.SetStateAction<DrinkMachineState>>;
}

function Pouring({ drinkId, setView }: PouringProps): JSX.Element {
  const mutate = useCancelPourDrink();

  const handleClick = (event: React.MouseEvent<HTMLButtonElement>) => {
    event.preventDefault();

    mutate.mutate({ id: drinkId });

    setView(DrinkMachineState.Selection);
  };

  return (
    <>
      <div className="flex flex-col items-center h-screen w-screen text-white justify-center">
        <h1 className="scroll-m-20 text-white mt-10 text-6xl font-extrabold tracking-tight lg:text-5xl border-b border-white">
          Pouring drink
        </h1>
        <div className="fill flex flex-col justify-center items-center p-8 shadow-2xl">
          <CountdownCircleTimer
            size={500}
            strokeWidth={30}
            strokeLinecap="butt"
            isPlaying
            duration={60}
            colors={["#004777", "#F7B801", "#A30000", "#A30000"]}
            colorsTime={[7, 5, 2, 0]}
          >
            {({ remainingTime }) => (
              <div className="font-extrabold text-white text-6xl">
                {remainingTime}
              </div>
            )}
          </CountdownCircleTimer>
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
