/** @format */

import ENV from "@/constants/env";

import { useMutation, useQueryClient } from "@tanstack/react-query";

import { http } from "@/api/axios";

if (ENV.MOCKED) {
  await import("./createFluid.mock.ts");
}

interface CreateFluidRequest {
  name: string;
}

export interface CreateFluidResponse {}

const createFluid = async ({ name }: CreateFluidRequest) => {
  const response = await http.post<CreateFluidResponse>(`v1/fluid`, {
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
    onSuccess: () => {
      queryClient.invalidateQueries(["getFluids"]);
    },
  });
};

export default useCreateFluid;