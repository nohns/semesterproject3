/** @format */

import ENV from "@/constants/env";
import axios from "axios";

export const http = axios.create({
  baseURL: ENV.API_URL || "http://localhost:9000",
  timeout: 20000,
  headers: {
    "Content-Type": "application/json",
  },
});
