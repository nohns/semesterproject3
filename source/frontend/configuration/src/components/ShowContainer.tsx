/** @format */

import React from "react";

interface ShowContainerProps {
  fluidAmountInCl: number;
}

function ShowContainer({
  fluidAmountInCl,
}: React.PropsWithChildren<ShowContainerProps>) {
  //We need to do some switch logic here to determine which image to show
  let image = "/assets/Overblik_1_black_0_20.png";

  if (fluidAmountInCl >= 20) {
    image = "/assets/Overblik_1_black_0_20.png";
  }

  if (fluidAmountInCl >= 40) {
    image = "/assets/Overblik_1_black_20_40.png";
  }

  if (fluidAmountInCl >= 60) {
    image = "/assets/Overblik_1_black_40_60.png";
  }

  if (fluidAmountInCl >= 80) {
    image = "/assets/Overblik_1_black_60_80.png";
  }

  return (
    <>
      <div className="text-black">
        <img src={image} />
      </div>
    </>
  );
}

export default ShowContainer;
