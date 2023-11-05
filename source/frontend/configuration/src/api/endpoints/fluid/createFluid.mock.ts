/** @format */

/** @format */

import httpMock from "@/api/axios.mock";
import { CreateFluidResponse } from "./createFluid";

//Regex to match v1/drink
const url = new RegExp(/v1\/fluids/); //I hate fucking regexes
httpMock.onPost(url).reply(() => {
  const res: CreateFluidResponse = {};

  return [200, res];
});
