/** @format */

import { useQuery } from "@tanstack/react-query";
import { Fluid } from "@/api/endpoints/drinks/getDrinks";

import http from "../../axios";
//import mocked data
import "@/api/endpoints/container/getContainers.mock";

export interface FluidContainer {
  id: number;
  fluid: Fluid;
  fluidAmountInCl: number;
}

interface GetContainersRequest {}

export interface GetContainersResponse {
  containers: FluidContainer[];
}

const getContainers = async ({}: GetContainersRequest) => {
  const response = await http.get<GetContainersResponse>(`v1/containers/`);

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
