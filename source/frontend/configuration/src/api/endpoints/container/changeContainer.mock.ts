/** @format */

import { mock } from "@/api/axios";

import { ChangeContainerResponse } from "./changeContainer";

//Regex to match v1/container/{id}
const url = new RegExp(/^v1\/containers\/\d+$/); //I hate fucking regexes
mock.onPatch(url).reply(() => {
  const res: ChangeContainerResponse = {};

  return [200, res];
});
