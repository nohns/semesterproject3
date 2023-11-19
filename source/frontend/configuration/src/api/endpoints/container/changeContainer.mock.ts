/** @format */

import httpMock from "@/api/axios.mock";

import { ChangeContainerResponse } from "./changeContainer";

//Regex to match v1/container/{id}
const url = new RegExp(/^v1\/containers\/\d+$/); //I hate fucking regexes
httpMock.onPatch(url).reply(() => {
  const res: ChangeContainerResponse = {};

  return [200, res];
});
