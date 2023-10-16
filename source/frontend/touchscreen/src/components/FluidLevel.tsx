/** @format */

import React from "react";
import WaterDropSvg from "./WaterDropSvg";

interface FluidLevelProps {
  level: number; // Fluid level from 0 to 100
}

const FluidLevel: React.FC<FluidLevelProps> = ({ level }) => {
  const raindropCount = Math.ceil(level / 20); // Calculate the number of raindrops to show

  return (
    <div className="">
      {Array.from({ length: raindropCount }).map((_, index) => (
        <WaterDropSvg key={index} />
      ))}
    </div>
  );
};

export default FluidLevel;
