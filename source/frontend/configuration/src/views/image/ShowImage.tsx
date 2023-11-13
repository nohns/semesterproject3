/** @format */

import { Image } from "@/api/endpoints/images/getImages";
import React from "react";

interface ShowImageProps {
  images: Image[];
}

function ShowImage({ images }: ShowImageProps) {
  return (
    <>
      <div className="flex flex-col">
        <div className="text-white">These are the available images: </div>
        {images.map((image) => (
          <div className="flex flex-col" key={image.id}>
            <img className="h-20 w-20" src={image.path} />
          </div>
        ))}
      </div>
    </>
  );
}

export default ShowImage;
