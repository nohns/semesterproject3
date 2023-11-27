/** @format */
import axios from "axios";
import AxiosMockAdapter from "axios-mock-adapter";
import ENV from "@/constants/env";

console.log(ENV);

export const mockInstance = axios.create();

export const mock = new AxiosMockAdapter(mockInstance, {
  delayResponse: 200,
});

const realInstance = axios.create();

export default ENV.MOCKED ? mockInstance : realInstance;
