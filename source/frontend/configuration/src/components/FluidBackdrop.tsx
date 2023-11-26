/** @format */

import React from "react";
import CustomDropdown from "@/components/CustomDropdown";
import { Fluid } from "@/api/endpoints/fluid/getFluids";
import ShowContainer from "./ShowContainer";
import { FluidContainer } from "@/api/endpoints/container/getContainers";
// import ShowImage from "@/views/image/ShowImage";
// import useGetImages, { Image } from "@/api/endpoints/images/getImages";
// import Overblik_80_100 from "@/assets/Overblik_80_100.png";
// const images = useGetImages();

interface FLuidBackDropProps {
  container: FluidContainer;
  setContainer: React.Dispatch<React.SetStateAction<FluidContainer>>;
  fluids: Fluid[];
}

const FluidBackdrop: React.FC<FLuidBackDropProps> = ({
  container,
  setContainer,
  fluids,
}) => {
  return (
    <div className="bg-zinc-700 rounded-2xl w-56 aspect-square flex flex-col items-center gap-5 p-2 transition duration-300 hover:bg-neutral-500">
      <CustomDropdown
        container={container}
        setContainer={setContainer}
        fluids={fluids}
        className="bg-gray-200 w-40 border-black border-2 rounded-xl"
      />
      <ShowContainer fluidAmountInCl={container.fluidAmountInCl} />
      {/* <div className="text-black font-mono">current drink vodka</div> */}
    </div>
  );
};
("");
export default FluidBackdrop;
