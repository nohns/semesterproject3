/** @format */

import httpMock from "@/api/axios.mock";
import { Drink } from "./getDrinks";

//sconst url = new RegExp(/v1\/event\/\d+$/);
const url = new RegExp(/v1\/drinks/); //I hate fucking regexes
httpMock.onGet(url).reply(() => {
  //Date time as string in rfc3339 format 30min from now

  const res: Drink[] = [
    {
      id: "1",
      name: "Blå vand",
      remainingFluid: 10,
    },
    {
      id: "2",
      name: "Snapse Kondi",
      remainingFluid: 100,
    },
    {
      id: "3",
      name: "Vodka vand",
      remainingFluid: 70,
    },
  ];

  return [200, res];
});
