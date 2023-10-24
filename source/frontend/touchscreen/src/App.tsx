/** @format */
import { useState } from "react";

import Waiting from "./views/Waiting";
import Selection from "./views/Selection";
import Pouring from "./views/Pouring";
import { useEffect } from "react";
import { CSSTransition, SwitchTransition } from "react-transition-group";

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
    }, 120000);

    return () => clearTimeout(timeout);
  }, [view, setView]);

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
                return <Selection setView={setView} />;
              case DrinkMachineState.Pouring:
                return <Pouring setView={setView} />;
              case DrinkMachineState.Waiting:
                return <Waiting setView={setView} />;
              default:
                return <Selection setView={setView} />;
            }
          }}
        </CSSTransition>
      </SwitchTransition>
    );
  };

  return (
    <div className="dark max-w-[480px] max-h-[800px] flex flex-col h-[800px] w-[480px]   bg-gradient-to-t from-yellow-500 via-gray-700 to-gray-500 p-1.5">
      <div className="bg-gradient-to-t w-full h-full from-[#302E37] to bg-slate-800">
        {renderView()}
      </div>
    </div>
  );
}

export default App;
