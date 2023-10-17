/** @format */

import httpMock from "@/api/axios.mock";

import { GetFluidsResponse } from "./getFluids";

const url = new RegExp(/v1\/fluids/); // I hate fucking regexes
httpMock.onGet(url).reply(() => {
  const res: GetFluidsResponse = {
    fluids: [
      { id: 1, name: "Vodka" },
      { id: 2, name: "Blå booster" },
      { id: 3, name: "Vand" },
    ],
  };

  return [200, res];
});
