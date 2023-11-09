/** @format */

import { Fluid } from "@/api/endpoints/fluid/getFluids";
import React from "react";

interface ShowFluidProps {
  fluids: Fluid[];
}

function ShowFluid({ fluids }: ShowFluidProps): JSX.Element {
  return (
    <>
      <div className="flex flex-col">
        <div className="text-white">These are the available fluids: </div>
        <div className="flex flex-col">
          {fluids.map((fluid) => (
            <div className="flex flex-row" key={fluid.id}>
              <div className="text-white mx-4">{fluid.name}</div>
            </div>
          ))}
        </div>
      </div>
    </>
  );
}

export default ShowFluid;
