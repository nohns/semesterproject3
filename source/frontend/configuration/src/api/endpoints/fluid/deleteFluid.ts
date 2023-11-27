/** @format */

import ENV from "@/constants/env";

import { useMutation, useQueryClient } from "@tanstack/react-query";

import http from "../../axios";
//import mocked data
import "@/api/endpoints/fluid/deleteFluid.mock";

interface DeleteFluidRequest {
  id: number;
}

export interface DeleteFluidResponse {}

const deleteFluid = async ({ id }: DeleteFluidRequest) => {
  const response = await http.delete<DeleteFluidResponse>(`v1/fluids/${id}`);

  if (response.status !== 200) {
    console.log(response);
    throw new Error("No data");
  }

  return response.data;
};

const useDeleteFluid = () => {
  const queryClient = useQueryClient();

  return useMutation({
    mutationKey: ["deleteFluid"],
    mutationFn: (request: DeleteFluidRequest) => deleteFluid(request),
    onSuccess: () => {
      queryClient.invalidateQueries(["getFluids"]);
    },
  });
};

export default useDeleteFluid;
