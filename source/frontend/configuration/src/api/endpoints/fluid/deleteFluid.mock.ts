/** @format */

import { mock } from "@/api/axios";

import { DeleteFluidResponse } from "./deleteFluid";

//Regex to match v1/fluid/{id}
const url = new RegExp(/v1\/fluids\/d+/); //I hate fucking regexes
mock.onDelete(url).reply(() => {
  const res: DeleteFluidResponse = {};

  return [200, res];
});
