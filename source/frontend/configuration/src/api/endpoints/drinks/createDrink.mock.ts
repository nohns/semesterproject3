/** @format */

import httpMock from "@/api/axios.mock";
import { CreateDrinkResponse } from "./createDrink";

//Regex to match v1/drink
const url = new RegExp(/v1\/drink/); //I hate fucking regexes
httpMock.onPost(url).reply(() => {
  const res: CreateDrinkResponse = {};

  return [200, res];
});
