/** @format */

import { mock } from "@/api/axios";
import { GetFluidsResponse } from "./getFluids";

const url = new RegExp(/v1\/fluids/); // I hate fucking regexes
mock.onGet(url).reply(() => {
  const res: GetFluidsResponse = {
    fluids: [
      { id: 1, name: "Vodka" },
      { id: 2, name: "Blå booster" },
      { id: 3, name: "Vand" },
      { id: 4, name: "Juice" },
      { id: 5, name: "Snaps" },
    ],
  };

  return [200, res];
});
