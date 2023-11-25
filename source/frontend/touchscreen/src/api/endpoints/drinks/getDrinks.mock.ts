/** @format */

import httpMock from "@/api/axios.mock";
import { GetDrinksResponse } from "./getDrinks";

// Url to match v1/drinks
const url = new RegExp(/v1\/drinks/);
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
        ingredients: [
          {
            id: 1,
            fluid: {
              id: 1,
              name: "Vodka",
            },
            amountInCl: 5,
          },
          {
            id: 2,
            fluid: {
              id: 2,
              name: "Blå booster",
            },
            amountInCl: 5,
          },
        ],
      },
      {
        id: 2,
        image: {
          id: 1,
          path: "src/assets/HotPot1.png",
        },
        name: "Double blå vand",
        ingredients: [
          {
            id: 1,
            fluid: {
              id: 1,
              name: "Vodka",
            },
            amountInCl: 5,
          },
          {
            id: 2,
            fluid: {
              id: 2,
              name: "Blå booster",
            },
            amountInCl: 5,
          },
        ],
      },
      {
        id: 3,
        image: {
          id: 1,
          path: "src/assets/HotPot1.png",
        },
        name: "Vand",
        ingredients: [
          {
            id: 3,
            fluid: {
              id: 3,
              name: "Vand",
            },
            amountInCl: 20,
          },
        ],
      },
      {
        id: 4,
        image: {
          id: 1,
          path: "src/assets/HotPot2.png",
        },
        name: "Snapse Vand",
        ingredients: [
          {
            id: 1,
            fluid: {
              id: 3,
              name: "Vand",
            },
            amountInCl: 5,
          },
          {
            id: 2,
            fluid: {
              id: 5,
              name: "Snaps",
            },
            amountInCl: 5,
          },
        ],
      },
      {
        id: 5,
        image: {
          id: 1,
          path: "src/assets/HotPot2.png",
        },
        name: "Vodka Juice",
        ingredients: [
          {
            id: 1,
            fluid: {
              id: 1,
              name: "Vodka",
            },
            amountInCl: 5,
          },
          {
            id: 2,
            fluid: {
              id: 4,
              name: "Juice",
            },
            amountInCl: 5,
          },
        ],
      },
    ],
  };

  return [200, res];
});
