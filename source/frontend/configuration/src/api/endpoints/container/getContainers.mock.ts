/** @format */

import httpMock from "@/api/axios.mock";
import { GetContainersResponse } from "./getContainers";

//Url to match v1/containers
const url = new RegExp(/v1\/containers/); //I hate fucking regexes
httpMock.onGet(url).reply(() => {
  const res: GetContainersResponse = {
    containers: [
      {
        id: 1,
        fluid: {
          id: 1,
          name: "Vodka",
        },
        fluidAmountInCl: 10,
      },
      {
        id: 2,
        fluid: {
          id: 2,
          name: "Blå booster",
        },
        fluidAmountInCl: 50,
      },
      {
        id: 3,
        fluid: {
          id: 3,
          name: "Vand",
        },
        fluidAmountInCl: 80,
      },
    ],
  };

  return [200, res];
});
