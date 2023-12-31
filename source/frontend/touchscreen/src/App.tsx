/** @format */
import { useState } from "react";

import Waiting from "./views/Waiting";
import Selection from "./views/Selection";
import Pouring from "./views/Pouring";
import { useEffect } from "react";
import { CSSTransition, SwitchTransition } from "react-transition-group";
import { Drink } from "./api/endpoints/drinks/getDrinks";
import { Toaster } from "./components/ui/toaster";
import useGetState from "./api/endpoints/state/getState";
import OutOfOrder from "./views/OutOfOrder";

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

  //will retry every 5 seconds, but only rerender when new data is available
  const state = useGetState();

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
            if (state.data?.out_of_order) {
              return (
                <OutOfOrder
                  message={state.data.out_of_order_message}
                  reason={state.data.out_of_order_reason}
                />
              );
            }

            switch (view) {
              case DrinkMachineState.Selection:
                return (
                  <Selection
                    view={view}
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
                    view={view}
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
    <div className="dark max-w-[480px] max-h-[800px] flex flex-col h-[800px] w-[480px] overflow-hidden  bg-gradient-to-t from-green-400 via-red-600 to-green-400 p-1.5">
      <div className="bg-gradient-to-t w-full h-full from-[#302E37] to bg-slate-800">
        <Toaster />
        {renderView()}
      </div>
    </div>
  );
}

export default App;
