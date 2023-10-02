/** @format */

import MockAdapter from "axios-mock-adapter";
import { http } from "./axios";

const httpMock = new MockAdapter(http, {
  delayResponse: 400,
  onNoMatch: "throwException",
});

export default httpMock;
