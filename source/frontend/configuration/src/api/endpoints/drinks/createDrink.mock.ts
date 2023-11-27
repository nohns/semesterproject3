/** @format */

import { mock } from "@/api/axios";
import { CreateDrinkResponse } from "./createDrink";

//Regex to match v1/drink
const url = new RegExp(/v1\/drinks/); //I hate fucking regexes
mock.onPost(url).reply(() => {
  const res: CreateDrinkResponse = {};

  return [200, res];
});
