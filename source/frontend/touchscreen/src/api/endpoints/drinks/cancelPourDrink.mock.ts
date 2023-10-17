/** @format */

import httpMock from "@/api/axios.mock";
import { CancelPourDrinkResponse } from "./cancelPourDrink";

//Regex to match v1/drinks/pour
const url = new RegExp(/v1\/drinks\/cancel/); //I hate fucking regexes
httpMock.onPost(url).reply(() => {
  const res: CancelPourDrinkResponse = {};

  return [200, res];
});
