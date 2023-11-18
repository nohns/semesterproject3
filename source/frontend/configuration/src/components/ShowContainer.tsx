/** @format */

import React from "react";

interface ShowContainerProps {}

function ShowContainer({}: React.PropsWithChildren<ShowContainerProps>) {
  const fluidAmountInCl = 81;
  //We need to do some switch logic here to determine which image to show
  let image = "src/assets/Overblik_1_black_0_20.png";

  if (fluidAmountInCl >= 20) {
    image = "src/assets/Overblik_1_black_0_20.png";
  }

  if (fluidAmountInCl >= 40) {
    image = "src/assets/Overblik_1_black_20_40.png";
  }

  if (fluidAmountInCl >= 60) {
    image = "src/assets/Overblik_1_black_40_60.png";
  }

  if (fluidAmountInCl >= 80) {
    image = "src/assets/Overblik_1_black_60_80.png";
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
