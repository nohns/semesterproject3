/** @format */

import { useMutation, useQueryClient } from "@tanstack/react-query";

import http from "../../axios";
//import mocked data
import "@/api/endpoints/fluid/createFluid.mock";

export interface CreateFluidRequest {
  name: string;
}

export interface CreateFluidResponse {}

const createFluid = async ({ name }: CreateFluidRequest) => {
  const response = await http.post<CreateFluidResponse>(`v1/fluids/`, {
    name,
  });

  if (response.status !== 200) {
    console.log(response);
    throw new Error("No data");
  }

  return response.data;
};

const useCreateFluid = () => {
  const queryClient = useQueryClient();

  return useMutation({
    mutationKey: ["createFluid"],
    mutationFn: (request: CreateFluidRequest) => createFluid(request),
    onSuccess: (data) => {
      console.log(data);
      queryClient.invalidateQueries(["getFluids"]);
    },
    onError: (error) => {
      console.log(error);
    },
  });
};

export default useCreateFluid;
