/** @format */

import httpMock from "@/api/axios.mock";

import { GetImagesResponse } from "./getImages";

//Regex to match v1/drinks/pour
const url = new RegExp(/v1\/images/); //I hate fucking regexes
httpMock.onGet(url).reply(() => {
  const res: GetImagesResponse = {
    images: [
      {
        id: 1,
        path: "src/assets/HotPot1.png",
      },
      {
        id: 2,
        path: "src/assets/HotPot2.png",
      },
      {
        id: 3,
        path: "src/assets/HotPot3.png",
      },
    ],
  };

  return [200, res];
});
