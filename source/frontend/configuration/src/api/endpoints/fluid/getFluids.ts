/** @format */

import ENV from "@/constants/env";

import { useQuery } from "@tanstack/react-query";

import http from "../../axios";
//import mocked data
import "@/api/endpoints/fluid/getFluids.mock";

export interface Fluid {
  id?: number;
  name: string;
}

interface GetFluidsRequest {}

export interface GetFluidsResponse {
  fluids: Fluid[];
}

const getFluids = async ({}: GetFluidsRequest) => {
  const response = await http.get<GetFluidsResponse>(`v1/fluids`);

  if (response.status !== 200) {
    console.log(response);
    throw new Error("No data");
  }

  return response.data;
};

const useGetFluids = () => {
  const query = useQuery({
    queryKey: ["getFluids"],
    queryFn: () => getFluids({}),
  });

  return query;
};

export default useGetFluids;
