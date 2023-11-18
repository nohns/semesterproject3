/** @format */

import React from "react";
import CustomDropdown from "@/components/CustomDropdown";
// import ShowImage from "@/views/image/ShowImage";
// import useGetImages, { Image } from "@/api/endpoints/images/getImages";
// import Overblik_80_100 from "@/assets/Overblik_80_100.png";

const FluidBackdrop: React.FC = () => {
  return (
    <div className="bg-neutral-400 rounded-2xl w-56 aspect-square flex flex-col items-center gap-5 p-2 transition duration-300 hover:bg-neutral-500">
      <CustomDropdown className="bg-slate-100 w-40" />
      <img src={"src/assets/Overblik_1_black_0_20.png"} alt="test" />
    </div>
  );
};

export default FluidBackdrop;
