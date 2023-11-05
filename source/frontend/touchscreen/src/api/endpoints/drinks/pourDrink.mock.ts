/** @format */

import httpMock from "@/api/axios.mock";

import { PourDrinkResponse } from "./pourDrink";

//Regex to match v1/drinks/pour
const url = new RegExp(/v1\/drinks\/pour/); //I hate fucking regexes
httpMock.onPost(url).reply(() => {
  const res: PourDrinkResponse = {};

  return [200, res];
});
