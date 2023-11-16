import React from "react";
import CustomDropdown from "@/components/Dropdown";
import ShowImage from "@/views/image/ShowImage";
import useGetImages, { Image } from "@/api/endpoints/images/getImages";
import Overblik_80-100.png from "@/assets/Overblik_80-100.png";
const images = useGetImages();

const FluidBackdrop: React.FC = () => {
 

  return (
    <div className="bg-neutral-400 rounded-2xl w-56 aspect-square flex flex-col items-center gap-5 p-2 transition duration-300 hover:bg-neutral-500">
      <CustomDropdown className="bg-slate-100 w-40" />
      <div className="w-[40%] h-[60%] bg-white">
        <ShowImage images={images} />
        {/* Add your additional content here if needed */}
      </div>
    </div>
  );
};

export default FluidBackdrop;
