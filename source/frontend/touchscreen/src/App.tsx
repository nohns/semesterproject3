/** @format */
import { useState } from "react";

import Waiting from "./views/Waiting";
import Selection from "./views/Selection";
import Pouring from "./views/Pouring";
import { useEffect } from "react";
import { CSSTransition, SwitchTransition } from "react-transition-group";
import useUpdate from "./api/endpoints/drinks/getUpdate";
import { Drink } from "./api/endpoints/drinks/getDrinks";

//Create typed enum for our 3 different states
export enum DrinkMachineState {
  Waiting = "Waiting",
  Selection = "Selection",
  Pouring = "Pouring",
}

function App() {
  const [view, setView] = useState<DrinkMachineState>(
    DrinkMachineState.Waiting
  );

  useEffect(() => {
    const timeout = setTimeout(() => {
      setView(DrinkMachineState.Waiting);
    }, 1200000);

    return () => clearTimeout(timeout);
  }, [view, setView]);

  //will retry every 5 seconds
  const updater = useUpdate();
  console.log("Updated?", updater.data);

  //We need to hold the state for the selected drink so we can pass it to multiple components
  const [selectedDrink, setSelectedDrink] = useState<Drink>();

  const renderView = () => {
    return (
      <SwitchTransition>
        <CSSTransition
          key={view}
          addEndListener={(node, done) => {
            node.addEventListener("transitionend", done, false);
          }}
          classNames="fade"
        >
          {() => {
            switch (view) {
              case DrinkMachineState.Selection:
                return (
                  <Selection
                    setView={setView}
                    selectedDrink={selectedDrink}
                    setSelectedDrink={setSelectedDrink}
                  />
                );
              case DrinkMachineState.Pouring:
                return (
                  <Pouring
                    setView={setView}
                    selectedDrink={selectedDrink}
                    setSelectedDrink={setSelectedDrink}
                  />
                );
              case DrinkMachineState.Waiting:
                return <Waiting setView={setView} />;
              default:
                return (
                  <Selection
                    setView={setView}
                    selectedDrink={selectedDrink}
                    setSelectedDrink={setSelectedDrink}
                  />
                );
            }
          }}
        </CSSTransition>
      </SwitchTransition>
    );
  };

  return (
    <div className="dark max-w-[480px] max-h-[800px] flex flex-col h-[800px] w-[480px]   bg-gradient-to-t from-green-400 via-red-600 to-green-400 p-1.5">
      <div className="bg-gradient-to-t w-full h-full from-[#302E37] to bg-slate-800">
        {renderView()}
      </div>
    </div>
  );
}

export default App;
