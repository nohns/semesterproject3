/** @format */

import { mock } from "@/api/axios";
import { DeleteDrinkResponse } from "./deleteDrink";

//Regex to match v1/drink
const url = new RegExp(/v1\/drinks/); //I hate fucking regexes
mock.onDelete(url).reply(() => {
  const res: DeleteDrinkResponse = {};

  return [200, res];
});
