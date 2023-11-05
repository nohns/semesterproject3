/** @format */

import httpMock from "@/api/axios.mock";

import { DeleteFluidResponse } from "./deleteFluid";

//Regex to match v1/fluid/{id}
const url = new RegExp(/v1\/fluids\/d+/); //I hate fucking regexes
httpMock.onDelete(url).reply(() => {
  const res: DeleteFluidResponse = {};

  return [200, res];
});
