/** @format */

/** @format */

import { mock } from "@/api/axios";
import { CreateFluidResponse } from "./createFluid";

//Regex to match v1/drink
const url = new RegExp(/v1\/fluids/); //I hate fucking regexes
mock.onPost(url).reply(() => {
  const res: CreateFluidResponse = {};

  return [200, res];
});
