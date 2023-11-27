/** @format */
import axios from "axios";
import AxiosMockAdapter from "axios-mock-adapter";
import ENV from "@/constants/env";

console.log(ENV);

export const mockInstance = axios.create();

export const mock = new AxiosMockAdapter(mockInstance, {
  delayResponse: 200,
});

// Real axios instance

const realInstance = axios.create();

if (ENV.MOCKED) {
  console.debug("Using mocked axios client");
}

export default ENV.MOCKED ? mockInstance : realInstance;
