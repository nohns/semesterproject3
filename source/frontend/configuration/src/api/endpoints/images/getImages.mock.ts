/** @format */

import { mock } from "@/api/axios";

import { GetImagesResponse } from "./getImages";

//Regex to match v1/drinks/pour
const url = new RegExp(/v1\/images/); //I hate fucking regexes
mock.onGet(url).reply(() => {
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
      {
        id: 4,
        path: "src/assets/Overblik_1_black_0_20.png",
      },
      {
        id: 5,
        path: "src/assets/Overblik_1_black_20_40.png",
      },
      {
        id: 6,
        path: "src/assets/Overblik_1_black_40_60.png",
      },
      {
        id: 7,
        path: "src/assets/Overblik_1_black_60_80.png",
      },
      {
        id: 8,
        path: "src/assets/Overblik_1_black_80_100.png",
      },
    ],
  };

  return [200, res];
});
