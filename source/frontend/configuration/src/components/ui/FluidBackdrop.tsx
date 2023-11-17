/** @format */

import React from "react";
import CustomDropdown from "@/components/Dropdown";
import { Fluid } from "@/api/endpoints/fluid/getFluids";
// import ShowImage from "@/views/image/ShowImage";
// import useGetImages, { Image } from "@/api/endpoints/images/getImages";
// import Overblik_80_100 from "@/assets/Overblik_80_100.png";
// const images = useGetImages();

interface FLuidBackDropProps {
  container: Fluid;
  setContainer: React.Dispatch<React.SetStateAction<Fluid>>;
  fluids: Fluid[];
}

const FluidBackdrop: React.FC<FLuidBackDropProps> = ({
  container,
  setContainer,
  fluids,
}) => {
  return (
    <div className="bg-neutral-400 rounded-2xl w-56 aspect-square flex flex-col items-center gap-5 p-2 transition duration-300 hover:bg-neutral-500">
      <CustomDropdown
        container={container}
        setContainer={setContainer}
        fluids={fluids}
        className="bg-slate-100 w-40"
      />
      <div className="w-[40%] h-[60%] bg-white">
        {/* <ShowImage image={images} /> */}
        {/* Add your additional content here if needed */}
      </div>
    </div>
  );
};
("");
export default FluidBackdrop;
