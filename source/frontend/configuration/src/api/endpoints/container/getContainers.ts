/** @format */

import ENV from "@/constants/env";

import { useQuery } from "@tanstack/react-query";

import { http } from "@/api/axios";
import { Fluid } from "../fluid/getFluids.ts";

if (ENV.MOCKED) {
  await import("./getContainers.mock.ts");
}

export interface FluidContainer {
  id: number;
  fluid: Fluid;
}

interface GetContainersRequest {}

export interface GetContainersResponse {
  containers: FluidContainer[];
}

const getContainers = async ({}: GetContainersRequest) => {
  const response = await http.get<GetContainersResponse>(`v1/containers`);

  if (response.status !== 200) {
    console.log(response);
    throw new Error("No data");
  }

  return response.data;
};

const useGetContainers = () => {
  const query = useQuery({
    queryKey: ["getContainers"],
    queryFn: () => getContainers({}),
  });

  return query;
};

export default useGetContainers;
