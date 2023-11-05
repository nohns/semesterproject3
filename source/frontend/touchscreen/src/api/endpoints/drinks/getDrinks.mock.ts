/** @format */

import httpMock from "@/api/axios.mock";
import { GetDrinksResponse } from "./getDrinks";

const url = new RegExp(/v1\/drinks/); //I hate fucking regexes
httpMock.onGet(url).reply(() => {
  const res: GetDrinksResponse = {
    drinks: [
      {
        id: 1,
        image: {
          id: 1,
          path: "src/assets/HotPot1.png",
        },
        name: "Blå vand",
        amountInCl: 10,
        remainingFluid: 10,
      },
      {
        id: 2,
        image: {
          id: 1,
          path: "src/assets/HotPot2.png",
        },
        name: "Snapse Kondi",
        amountInCl: 10,
        remainingFluid: 100,
      },
      {
        id: 3,
        image: {
          id: 1,
          path: "src/assets/HotPot3.png",
        },
        name: "Vodka vand",
        amountInCl: 10,
        remainingFluid: 70,
      },
    ],
  };

  return [200, res];
});
